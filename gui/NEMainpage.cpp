#include "NEMainpage.h"
#include "ui_NEMainpage.h"
//#include "services/p3JumpingCube2.h"
#include "interface/rsJumpingCube2.h"
#include<qjsondocument.h>



NEMainpage::NEMainpage(QWidget *parent, JumpingCube2Notify *notify) :
	MainPage(parent),
	mNotify(notify),
	ui(new Ui::NEMainpage)
{
	ui->setupUi(this);

	connect(mNotify, SIGNAL(NeMsgArrived(RsPeerId,QString)), this , SLOT(NeMsgArrived(RsPeerId,QString)));
	//ui->listWidget->addItem("str");
	ui->widget->setModus(FriendSelectionWidget::MODUS_SINGLE);
	ui->widget->start();

}

NEMainpage::~NEMainpage()
{
	delete ui;
}

void NEMainpage::mmEvent(int x, int y)
{
	rsJumpingCube2->broadcast_paint(x,y);
}

void NEMainpage::on_pingAllButton_clicked()
{
	rsJumpingCube2->ping_all();
	NeMsgArrived(rsPeers->getOwnId(),"ping");
}


void NEMainpage::NeMsgArrived(const RsPeerId &peer_id, QString str)
{
	QJsonDocument jdoc = QJsonDocument::fromJson(str.toUtf8());
	QVariantMap vmap = jdoc.toVariant().toMap();
	std::cout << "GUI got Packet from: " << peer_id;
	std::cout << " saying " << str.toStdString();
	std::cout << std::endl;
	QString type = vmap.value("type").toString();
	if (type == "chat"){
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=vmap.value("message").toString();
		ui->listWidget->addItem(output);
	}else if (type == "new_jc_game"){
		JumpingCubeWindow* jc = new JumpingCubeWindow(this);
		jc->myid = 0;
		std::string peerid = peer_id.toStdString();
		jc->peerid = peerid;
		jc->show();
		jcGames.insert(peer_id, jc);
		//jcw = jc;
		connect(jc, SIGNAL(mClick(std::string , int, int)), this, SLOT(sendMClick(std::string, int, int)));
	}else if (type == "jc_click"){
		int x =vmap.value("x").toInt();
		int y =vmap.value("y").toInt();
		std::cout << "remote_jc_click: " << x << y << std::endl;
		JumpingCubeWindow* jcw = jcGames.value(peer_id);
		jcw->remoteClick(x,y);
		//emit incomingRemoteClick(2,2);
	}else{
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=str;
		ui->listWidget->addItem(output);
	}

	{
		QString output = QString::fromStdString(rsPeers->getPeerName(peer_id));
		output+=": ";
		output+=str;
		ui->netLogWidget->addItem(output);
	}
}
void NEMainpage::sendMClick(std::string peerid, int x, int y){
    std::cerr << "SENDING MESSAGE FROM CLICK";
    //TODO send mouse click!
    //std::string peerid = jcw->peerid;//#ui->onlinePeerView->currentItem()->text().toStdString();
    //p3service->msgPeerXYT(peerid, x,y,"JCPR");
    QVariantMap data;
    data.insert("type","jc_click");
    data.insert("x",x);
    data.insert("y",y);

    rsJumpingCube2->qvm_msg_peer(RsPeerId(peerid), data);
}
void NEMainpage::NePaintArrived(const RsPeerId &peer_id, int x, int y)
{

	std::cout << "GUI got Paint from: " << peer_id;
	std::cout << std::endl;

}

void NEMainpage::on_broadcastButton_clicked()
{
	rsJumpingCube2->msg_all(ui->msgInput->text().toStdString());
	NeMsgArrived(rsPeers->getOwnId(),ui->msgInput->text());
	ui->msgInput->clear();
}

void NEMainpage::on_playButton_clicked()
{

    JumpingCubeWindow* jc = new JumpingCubeWindow(this);
    jc->myid = 1;

	FriendSelectionWidget::IdType idType;
	std::string peerid = ui->widget->selectedId(idType);
	jc->peerid = peerid;
	jc->show();

	jcGames.insert(RsPeerId(peerid), jc);

	connect(jc, SIGNAL(mClick(std::string, int, int)), this, SLOT(sendMClick(std::string, int, int)));

	QVariantMap data;
	data.insert("type","new_jc_game");

	rsJumpingCube2->qvm_msg_peer(RsPeerId(peerid), data);
}
