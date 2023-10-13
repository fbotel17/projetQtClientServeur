#include "Server.h"

Server::Server(QObject* parent)
	: QObject(parent)
{
	server = new QTcpServer(this);
	QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
	server->listen(QHostAddress::AnyIPv4,6969);
	
}

void Server::onServerNewConnection() 
{
	qDebug() << "Un client s'est connecte !";
	QTcpSocket * client = server->nextPendingConnection();
	QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onClientDisconnected()
{
	QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());
	QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
	QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
	obj->deleteLater();
}

void Server::onClientReadyRead()
{
	QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());

}

Server::~Server() {
	delete(server);
}
