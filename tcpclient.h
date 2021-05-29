#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPClient; }
QT_END_NAMESPACE

class TCPClient : public QWidget
{
    Q_OBJECT

public:
    TCPClient(QWidget *parent = nullptr);
    ~TCPClient();

private:
    Ui::TCPClient *ui;
    QTcpSocket *qTcpSocket = nullptr;
    QDataStream in;
    QString receivedMessage;

private slots:
    void requestMessage();
    void readMessage();
    void showError(QAbstractSocket::SocketError socketError);

};
#endif // TCPCLIENT_H
