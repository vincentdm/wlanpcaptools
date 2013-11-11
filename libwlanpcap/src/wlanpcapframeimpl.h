/*
 * wlanpcapframeimpl.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
 */

#ifndef WLANPCAPFRAMEIMPL_H_
#define WLANPCAPFRAMEIMPL_H_

#include "wlanpcap.h"

#include <pcap.h>

class wlanpcap_frame_impl: public wlanpcap_frame {
public:
	wlanpcap_frame_impl(wlanpcap_t source , pcap_pkthdr *& header,const u_char *& frame);
	wlanpcap_frame_impl(const wlanpcap_frame *);//copy constructor from pointer
	virtual ~wlanpcap_frame_impl();

	virtual const unsigned char * getframebytes();
	virtual const unsigned char * getframepayload();
	virtual const unsigned int getframepayloadlength();
	virtual pcap_pkthdr * getpcapheader();
	virtual const timeval getpcaptimestamp();
	virtual bool equals(wlanpcap_frame * frame);
	virtual wlanpcap_t getsource() {
		return source;
	}

private:
	wlanpcap_t source;
	pcap_pkthdr * pcap_header;
	const u_char * frame_bytes;
};

#endif /* WLANPCAPFRAMEIMPL_H_ */
