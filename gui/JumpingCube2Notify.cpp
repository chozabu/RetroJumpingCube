#include "JumpingCube2Notify.h"

JumpingCube2Notify::JumpingCube2Notify(QObject *parent) : QObject(parent)
{

}

void JumpingCube2Notify::notifyReceivedPaint(const RsPeerId &peer_id, int x, int y)
{
	std::cout << "pNotify Recvd paint from: " << peer_id;
	std::cout << " at " << x << " , " << y;
	std::cout << std::endl;
	emit NePaintArrived(peer_id, x, y);
}


void JumpingCube2Notify::notifyReceivedMsg(const RsPeerId& peer_id, QString str)
{
	std::cout << "pNotify Recvd Packet from: " << peer_id;
	std::cout << " saying " << str.toStdString();
	std::cout << std::endl;
	emit NeMsgArrived(peer_id, str) ;
}
