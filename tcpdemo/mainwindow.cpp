#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSever = new QTcpServer(this);
    connect(tcpSever,SIGNAL(newConnection()),this,SLOT(newconnectslot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    close();
}

void MainWindow::on_pushButton_listen_clicked()
{
    QString ip= ui->lineEdit_ip->text();
    quint16 port = ui->lineEdit_port->text().toInt();

    if(!tcpSever->isListening())//判断有没有在监听，如果为假，也就是没有监听，进入该句
    {
       if(!tcpSever->listen(QHostAddress(ip),port))
       {
           qDebug()<<tcpSever->errorString();//提示错误信息
           return;
       }
       else
       {
           ui->pushButton_listen->setText("停止监听");
       }
    }
    else
    {
        tcpSever->close();
        ui->pushButton_listen->setText("开始监听");
    }
}

void MainWindow::newconnectslot()
{
    QTcpSocket *socket = tcpSever->nextPendingConnection();//链接进来的客人
    tcpScoketList.append(socket);
    //获取新链接进来的用户ip和端口号
    QString str;
    str += "IP:"+socket->peerAddress().toString()+" PORT:" + QString::number(socket->peerPort());
    ui->listWidget->addItem(str);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyreadslot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnectslot()));
}

void MainWindow::readyreadslot()
{
    //得到发送信号的对象
    auto *socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    QString str;
    str = QString::fromLocal8Bit(data);
    ui->textBrowser->append(str);

    //给所有客户端发送数据
    foreach(QTcpSocket* s,tcpScoketList)
    {
        s->write(data);
    }
}

void MainWindow::disconnectslot()
{
    auto *socket = qobject_cast<QTcpSocket*>(sender());
    QString str;
    str += "IP:"+socket->peerAddress().toString()+" PORT:" + QString::number(socket->peerPort());
    qDebug()<<str+"离开了";
    tcpScoketList.removeOne(socket);
        socket->deleteLater(); // 释放内存
}



void MainWindow::on_pushButton_send_clicked()
{
    QString str;
    str = ui->textEdit_send->toPlainText();
    QByteArray data = str.toLocal8Bit();
    //给所有客户端发送数据
    foreach(QTcpSocket* s,tcpScoketList)
    {
        s->write(data);
    }
}
