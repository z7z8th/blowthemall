#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>

inline QString variantToDebugString(const QVariant &variant)
{
    QString string;
    QDebug dbg(&string);
    dbg << variant;
    return string;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    peer(new Phobos::HttpHelper(this))
{
    ui->setupUi(this);

    connect(peer, SIGNAL(readyResponse(QVariant,QVariant)),
            this, SLOT(onReadyResponse(QVariant,QVariant)));
    connect(peer, SIGNAL(requestError(int,QString,QVariant,QVariant)),
            this, SLOT(onRequestError(int,QString,QVariant,QVariant)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyResponse(const QVariant &result, const QVariant &id)
{
    QTableWidgetItem *resultItem = new QTableWidgetItem(variantToDebugString(result));
    QTableWidgetItem *idItem = new QTableWidgetItem(variantToDebugString(id));
    const int row = ui->responsesTableWidget->rowCount();
    ui->responsesTableWidget->setRowCount(row + 1);
    ui->responsesTableWidget->setItem(row, 0, resultItem);
    ui->responsesTableWidget->setItem(row, 1, idItem);
}

void MainWindow::onRequestError(int code, const QString &message,
                                const QVariant &data, const QVariant &id)
{
    QTableWidgetItem *codetItem = new QTableWidgetItem(QString::number(code));
    QTableWidgetItem *messageItem = new QTableWidgetItem(message);
    QTableWidgetItem *dataItem = new QTableWidgetItem(variantToDebugString(data));
    QTableWidgetItem *idItem = new QTableWidgetItem(variantToDebugString(id));
    const int row = ui->errorsTableWidget->rowCount();
    ui->errorsTableWidget->setRowCount(row + 1);
    ui->errorsTableWidget->setItem(row, 0, codetItem);
    ui->errorsTableWidget->setItem(row, 1, messageItem);
    ui->errorsTableWidget->setItem(row, 2, dataItem);
    ui->errorsTableWidget->setItem(row, 3, idItem);
}

void MainWindow::on_newButton_clicked()
{
    const int row = ui->paramsTableWidget->rowCount();
    ui->paramsTableWidget->setRowCount(row + 1);
    ui->paramsTableWidget->setItem(row, 0, new QTableWidgetItem);
    ui->paramsTableWidget->setItem(row, 1, new QTableWidgetItem);
}

void MainWindow::on_deleteButton_clicked()
{
    ui->paramsTableWidget->removeRow(ui->paramsTableWidget->currentRow());
}

void MainWindow::on_callButton_clicked()
{
    {
        QString defaultUrl("http://localhost/");
        QUrl url(QInputDialog::getText(this, "Host", "Host:",
                                       QLineEdit::Normal, defaultUrl));
        peer->setUrl(url);
    }

    QString method = ui->methodLineEdit->text();
    QVariant params;
    QVariant id = ui->idLineEdit->text();

    if (ui->positionalRadioButton->isChecked()) {
        if (ui->paramsTableWidget->rowCount()) {
            QVariantList paramsList;

            for (int i = 0;i != ui->paramsTableWidget->rowCount();++i) {
                paramsList.push_back(ui->paramsTableWidget->item(i, 1)->text());
            }

            params = paramsList;
        }
    } else {
        if (ui->paramsTableWidget->rowCount()) {
            QVariantMap paramsMap;

            for (int i = 0;i != ui->paramsTableWidget->rowCount();++i) {
                paramsMap[ui->paramsTableWidget->item(i, 0)->text()]
                        = ui->paramsTableWidget->item(i, 1)->text();
            }

            params = paramsMap;
        }
    }

    peer->call(method, params, id);
}
