#pragma once

#include <qtcpsocket.h>
#include <qtcpserver.h>
#include <qobject.h>
#include <qDebug>
#include <QRegularExpression>
#include <time.h>

class Server : public QObject
{
	Q_OBJECT

public:
	Server(QObject* parent = Q_NULLPTR);
	~Server();

private:
	QTcpServer* server;

public slots:
	void onServerNewConnection();
	void onClientDisconnected();
	void onClientReadyRead();

};



