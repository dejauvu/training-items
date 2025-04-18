#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

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
    void on_pushButton_send_clicked();
    void readyreadslot();
    void disconnectslot();

    void on_pushButton_listen_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    bool socketState;
};

#endif // MAINWINDOW_H
