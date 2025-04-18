#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

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
    //关闭按钮
    void on_pushButton_clicked();
    //监听按钮
    void on_pushButton_listen_clicked();
    //新用户接收端口槽函数
    void newconnectslot();
    //读取用户信息槽函数
    void readyreadslot();
    //用户离开槽函数
    void disconnectslot();
    void on_pushButton_send_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer* tcpSever;
    QList<QTcpSocket*> tcpScoketList;
};

#endif // MAINWINDOW_H
