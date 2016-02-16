
#ifndef __GENERICPACKET_H__
#  include "GenericPacket.h"
#endif

GenericPacket::GenericPacket()
	       :mTimeStamp(0),
		mPeerAddress(0),
		Next(0L)
{
  mTimeStamp = time(0);
}


GenericPacket::~GenericPacket()
{

}

