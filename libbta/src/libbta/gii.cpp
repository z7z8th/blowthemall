/*
  Copyright © 2012  Vinícius dos Santos Oliveira

  This file is part of libbta.

  libbta is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "priv/gii.h"
#include "priv/rcc.h"

#include <QtCore/QResource>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtCore/QTemporaryFile>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QSharedPointer>

namespace libbta {
namespace Gii {

Gii::Gii(QObject *parent) :
    QObject(parent),
    priv(new Priv)
{
}

Gii::~Gii()
{
    delete priv;
}

QString Gii::defaultState()
{
    return priv->defaultState;
}

void Gii::setDefaultState(const QString &state)
{
    if (state == priv->defaultState || !priv->states.contains(state))
        return;

    priv->defaultState = state;
    emit defaultStateChanged();
}

States Gii::states()
{
    return priv->states;
}

void Gii::setStates(const States &states)
{
    if (states == priv->states)
        return;

    for (QObject *o: states)
        o->setParent(this);

    priv->states = states;
    emit statesChanged();
}

State *Gii::currentState()
{
    if (priv->currentState.isEmpty())
        return NULL;

    return priv->states[priv->currentState];
}

QString Gii::currentStateString()
{
    return priv->currentState;
}

bool Gii::save(const QString &file)
{
    if (!Rcc::hasCompiler())
        return false;

    QTemporaryFile metaDataFile;
    QStringList resources;
    if (!metaDataFile.open())
        return false;

    {
        QSettings settings(metaDataFile.fileName(), QSettings::IniFormat);

        settings.setValue("version", "1.0");
        settings.setValue("defaultState", defaultState());

        for (States::iterator i = priv->states.begin()
             ;i != priv->states.end();++i) {
            QString state = "state." + i.key();

            settings.beginGroup(state);
            {
                QStringList seq = i.value()->seq();
                for (QString &r: seq) {
                    if (!resources.contains(r))
                        resources.append(r);

                    r = QFileInfo(r).fileName();
                }

                settings.setValue("period", i.value()->period());
                settings.setValue("seq", i.value()->seq());
                settings.setValue("onFinished", i.value()->onFinished());
            }
            settings.endGroup(); // state
        }
    }

    QTemporaryFile qrcFile;
    QList<QSharedPointer<QTemporaryFile>> copies;
    if (!qrcFile.open())
        return false;

    {
        QXmlStreamWriter xml(&qrcFile);
        xml.writeDTD("<!DOCTYPE RCC>");
        xml.writeStartElement("RCC");
        xml.writeAttribute("version", "1.0");
        xml.writeStartElement("qresource");

        xml.writeStartElement("file");
        xml.writeAttribute("alias", "index.ini");
        xml.writeCharacters(metaDataFile.fileName());
        xml.writeEndElement(); // "file"

        for (QString r: resources) {
            xml.writeStartElement("file");
            xml.writeAttribute("alias", QFileInfo(r).fileName());

            if (r.startsWith(":/")) {
                copies.push_back(QSharedPointer<QTemporaryFile>
                                 (new QTemporaryFile));
                if (!copies.back()->open())
                    return false;

                QFile::copy(r, copies.back()->fileName());

                xml.writeCharacters(copies.back()->fileName());
                xml.writeEndElement(); // "file"
                continue;
            }

            xml.writeCharacters(r);
            xml.writeEndElement(); // "file"
        }

        xml.writeEndElement(); // "qresource"
        xml.writeEndElement(); // "RCC"
    }

    if (!qrcFile.flush())
        return false;

    if (!Rcc::compile(qrcFile.fileName(), file))
        return false;

    return true;
}

bool Gii::load(const QString &file)
{
    QString fileBaseName = QFileInfo(file).baseName();
    QString prefix = ":/" + fileBaseName + "/";
    if (!QResource::registerResource(file, "/" + fileBaseName))
        return false;

    QSettings settings(prefix + "index.ini", QSettings::IniFormat);
    if (settings.value("version").toString() != "1.0")
        return false;

    States states;
    for (QString state: settings.childGroups()) {
        static const QString stateGroupId = "state.";
        if (!state.startsWith(stateGroupId))
            continue;

        QString stateName = state.mid(stateGroupId.size());
        if (stateName.isEmpty())
            continue;

        settings.beginGroup(state);
        {
            State *state = new State(this);

            state->setPeriod(settings.value("period").toInt());
            state->setOnFinished(settings.value("onFinished").toString());

            QStringList seq = settings.value("seq").toStringList();
            for (QString &i: seq)
                i.push_front(prefix);
            state->setSeq(seq);

            states[stateName] = state;
        }
        settings.endGroup(); // state
    }

    setStates(states);
    setDefaultState(settings.value("defaultState").toString());
    loadState(defaultState());
    return true;
}

void Gii::loadState(const QString &state)
{
    if (!priv->states.contains(state) && !state.isEmpty())
        return;

    if (!priv->currentState.isEmpty()) {
        priv->states[priv->currentState]->stop();
        disconnect(priv->states[priv->currentState], SIGNAL(finished()),
                   this, SLOT(onStateFinished()));
    }

    bool stateChanged = state == priv->currentState ? false : true;
    priv->currentState = state;

    if (!state.isEmpty()) {
        connect(priv->states[state], SIGNAL(finished()),
                this, SLOT(onStateFinished()));
        priv->states[state]->start();
    }

    if (stateChanged)
        emit currentStateChanged();
}

void Gii::onStateFinished()
{
    loadState(priv->states[priv->currentState]->onFinished());
}

} // namespace Gii
} // namespace libbta
