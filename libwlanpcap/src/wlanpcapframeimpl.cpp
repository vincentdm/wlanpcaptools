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


#include "wlanpcapframeimpl.h"
#include <string.h>

#ifndef NDEBUG
#include <iostream>
#endif

wlanpcap_frame * wlanpcap_frame::wlanpcap_frame_copy(const wlanpcap_frame* original) {
	return new wlanpcap_frame_impl(original);
}

bool wlanpcap_frame_impl::equals(wlanpcap_frame * frame) {
	unsigned length=frame->getframepayloadlength();
#ifndef NDEBUG
	std::cout << "comparing this ("<<(void*)this<<", " << this->getframepayloadlength() <<  " bytes) to frame " << (void*)frame << " ( " << frame->getframepayloadlength() << " bytes) for a length of " << length << " bytes" << std::endl;
#endif
	if(this->getframepayloadlength() < length)
		length=this->getframepayloadlength();

	if(memcmp((const char *)this->getframepayload(),(const char *)frame->getframepayload(),length)==0) {
		return true;
	}
	return false;
}

wlanpcap_frame_impl::wlanpcap_frame_impl(wlanpcap_t source, pcap_pkthdr *& header,const u_char *& frame):
source(source) {
	pcap_header = new pcap_pkthdr();
	memcpy(pcap_header,header,sizeof(pcap_pkthdr));

	this->frame_bytes=new unsigned char[header->caplen];
	memcpy((unsigned char *)frame_bytes,frame,(unsigned long)header->caplen);

}

wlanpcap_frame_impl::wlanpcap_frame_impl(const wlanpcap_frame* original) {
//copy constructor from pointer
	const wlanpcap_frame_impl * orig = dynamic_cast<const wlanpcap_frame_impl *>(original);
	this->source=orig->source;
	this->pcap_header=new pcap_pkthdr();
	memcpy(this->pcap_header,orig->pcap_header,sizeof(pcap_pkthdr));

	this->frame_bytes=new unsigned char[orig->pcap_header->caplen];
	memcpy((unsigned char*)this->frame_bytes,(unsigned char *)orig->frame_bytes,orig->pcap_header->caplen);
}


wlanpcap_frame_impl::~wlanpcap_frame_impl() {
	if(pcap_header!=NULL)
		delete(pcap_header);

	if(frame_bytes!=NULL)
		delete[] frame_bytes;
}

const unsigned char* wlanpcap_frame_impl::getframebytes() {
	return this->frame_bytes;
}

const unsigned char* wlanpcap_frame_impl::getframepayload() {
	return (*this->source->get_functions()->strip)(this->frame_bytes);
}

const unsigned int wlanpcap_frame_impl::getframepayloadlength() {
	return (this->pcap_header->caplen- this->source->get_functions()->getheaderlength(this->frame_bytes));
}


pcap_pkthdr* wlanpcap_frame_impl::getpcapheader() {
	return this->pcap_header;
}

const timeval wlanpcap_frame_impl::getpcaptimestamp() {
	return this->pcap_header->ts;
}
