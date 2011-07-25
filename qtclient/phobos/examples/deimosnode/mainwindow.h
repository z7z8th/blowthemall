#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "phobos/httphelper.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onReadyResponse(const QVariant &result, const QVariant &id);
    void onRequestError(int code, const QString &message,
                        const QVariant &data, const QVariant &id);

    void on_newButton_clicked();

    void on_deleteButton_clicked();

    void on_callButton_clicked();

private:
    Ui::MainWindow *ui;
    Phobos::HttpHelper *peer;
};

#endif // MAINWINDOW_H
