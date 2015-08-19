/* This is the main page displayed by the plugin */
#ifndef NEMAINPAGE_H
#define NEMAINPAGE_H

#include <retroshare-gui/mainpage.h>
#include <retroshare/rsfiles.h>
#include <retroshare/rspeers.h>
#include "gui/JumpingCube2Notify.h"

#include "jumpingcubewindow.h"



#include <QWidget>

namespace Ui {
class NEMainpage;
}

class NEMainpage : public MainPage
{
	Q_OBJECT

public:
	explicit NEMainpage(QWidget *parent, JumpingCube2Notify *notify);
	~NEMainpage();

public slots:
	void sendMClick(std::string peerid, int x, int y);
private slots:
	void mmEvent(int x, int y);
	void on_pingAllButton_clicked();
	void NeMsgArrived(const RsPeerId &peer_id, QString str);

	void on_broadcastButton_clicked();

	void NePaintArrived(const RsPeerId &peer_id, int x, int y);
	void on_playButton_clicked();

private:
	Ui::NEMainpage *ui;
	JumpingCube2Notify *mNotify;
	QMap <RsPeerId, JumpingCubeWindow*> jcGames;
};

#endif // NEMAINPAGE_H
