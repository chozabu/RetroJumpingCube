/* this describes the datatypes sent over the network, and how to (de)serialise them */
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

/*
 * libretroshare/src/serialiser: rsJumpingCube2Items.h
 *
 * RetroShare Serialiser.
 *
 * Copyright 2011 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */

#include <map>

#include "serialiser/rsserviceids.h"
#include "serialiser/rsserial.h"

/**************************************************************************/

const uint16_t RS_SERVICE_TYPE_JumpingCube2_PLUGIN = 0x010101;

const uint8_t RS_PKT_SUBTYPE_JumpingCube2_DATA 	   = 0x01;

const uint8_t QOS_PRIORITY_RS_JumpingCube2 = 9 ;


class RsJumpingCube2Item: public RsItem
{
	public:
		RsJumpingCube2Item(uint8_t JumpingCube2_subtype)
			: RsItem(RS_PKT_VERSION_SERVICE,RS_SERVICE_TYPE_JumpingCube2_PLUGIN,JumpingCube2_subtype)
		{ 
			setPriorityLevel(QOS_PRIORITY_RS_JumpingCube2) ;
		}	

		virtual ~RsJumpingCube2Item() {};
		virtual void clear() {};
		virtual std::ostream& print(std::ostream &out, uint16_t indent = 0) = 0 ;

		virtual bool serialise(void *data,uint32_t& size) = 0 ;	// Isn't it better that items can serialise themselves ?
		virtual uint32_t serial_size() const = 0 ; 							// deserialise is handled using a constructor
};


class RsJumpingCube2DataItem: public RsJumpingCube2Item
{
	public:
		RsJumpingCube2DataItem() :RsJumpingCube2Item(RS_PKT_SUBTYPE_JumpingCube2_DATA) {}
		RsJumpingCube2DataItem(void *data,uint32_t size) ; // de-serialization

		virtual bool serialise(void *data,uint32_t& size) ;
		virtual uint32_t serial_size() const ; 							

		virtual ~RsJumpingCube2DataItem()
		{
		}
		virtual std::ostream& print(std::ostream &out, uint16_t indent = 0);

		uint32_t flags ;
		uint32_t data_size ;
		std::string m_msg;
};


class RsJumpingCube2Serialiser: public RsSerialType
{
	public:
		RsJumpingCube2Serialiser()
			:RsSerialType(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_JumpingCube2_PLUGIN)
		{ 
		}
		virtual ~RsJumpingCube2Serialiser() {}

		virtual uint32_t 	size (RsItem *item) 
		{ 
			return dynamic_cast<RsJumpingCube2Item *>(item)->serial_size() ;
		}

		virtual	bool serialise  (RsItem *item, void *data, uint32_t *size)
		{ 
			return dynamic_cast<RsJumpingCube2Item *>(item)->serialise(data,*size) ;
		}
		virtual	RsItem *deserialise(void *data, uint32_t *size);
};

/**************************************************************************/
