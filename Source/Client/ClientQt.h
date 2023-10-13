#ifndef CLIENTQT_H
#define CLIENTQT_H

#include <QMainWindow>

#include <qtcpsocket.h>

QT_BEGIN_NAMESPACE
namespace Ui { class ClientQt; }
QT_END_NAMESPACE

class ClientQt : public QMainWindow
{
    Q_OBJECT

public:
    ClientQt(QWidget *parent = nullptr);
    ~ClientQt();

private:
    Ui::ClientQt *ui;
    QTcpSocket * socket;

public slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSendMessageButtonClicked();
    void onSocketReadyRead();


};
#endif // CLIENTQT_H
