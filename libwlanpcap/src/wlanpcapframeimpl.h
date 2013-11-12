/*
* Copyright 2013 Vincent De Maertelaere
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
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
