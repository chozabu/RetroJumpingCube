/* this handles the networking service of this plugin */
/****************************************************************
 *  RetroShare is distributed under the following license:
 *
 *  Copyright (C) 2015
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/

#pragma once

#include <list>
#include <string>
#include <QVariantMap>

#include "services/rsJumpingCube2Items.h"
#include "services/p3service.h"
#include "serialiser/rstlvbase.h"
#include "serialiser/rsconfigitems.h"
#include "plugins/rspqiservice.h"
#include <interface/rsJumpingCube2.h>

class p3LinkMgr;
class JumpingCube2Notify ;



//!The RS VoIP Test service.
 /**
  *
  * This is only used to test Latency for the moment.
  */

class p3JumpingCube2: public RsPQIService, public RsJumpingCube2
// Maybe we inherit from these later - but not needed for now.
//, public p3Config, public pqiMonitor
{
	public:
		p3JumpingCube2(RsPluginHandler *cm,JumpingCube2Notify *);

		/***** overloaded from rsJumpingCube2 *****/


		/***** overloaded from p3Service *****/
		/*!
		 * This retrieves all chat msg items and also (important!)
		 * processes chat-status items that are in service item queue. chat msg item requests are also processed and not returned
		 * (important! also) notifications sent to notify base  on receipt avatar, immediate status and custom status
		 * : notifyCustomState, notifyChatStatus, notifyPeerHasNewAvatar
		 * @see NotifyBase
		 */
		virtual int   tick();
		virtual int   status();
		virtual bool  recvItem(RsItem *item);

		/*************** pqiMonitor callback ***********************/
		//virtual void statusChange(const std::list<pqipeer> &plist);


		/************* from p3Config *******************/
		virtual RsSerialiser *setupSerialiser() ;

		/*!
		 * chat msg items and custom status are saved
		 */
		virtual bool saveList(bool& cleanup, std::list<RsItem*>&) ;
		virtual bool loadList(std::list<RsItem*>& load) ;
		virtual std::string configurationFileName() const { return "JumpingCube2.cfg" ; }

		virtual RsServiceInfo getServiceInfo() ;

		void 	ping_all();

		void broadcast_paint(int x, int y);
		void 	msg_all(std::string msg);
		void str_msg_peer(RsPeerId peerID, QString strdata);
		void raw_msg_peer(RsPeerId peerID, std::string msg);
		void 	qvm_msg_peer(RsPeerId peerID, QVariantMap data);
private:



		void handleData(RsJumpingCube2DataItem*) ;

		RsMutex mJumpingCube2Mtx;


		static RsTlvKeyValue push_int_value(const std::string& key,int value) ;
		static int pop_int_value(const std::string& s) ;


		RsServiceControl *mServiceControl;
		JumpingCube2Notify *mNotify ;

};
