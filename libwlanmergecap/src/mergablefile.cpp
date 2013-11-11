/*
 * mergablefile.cpp
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
 */

#include "mergablefile.h"




mergablefile::mergablefile(const std::string & filename):
handle(wlanpcap::create_wlanpcap(filename)){

	this->offset=0;

}

mergablefile::~mergablefile() {
	if(handle !=NULL)
		wlanpcap::delete_wlanpcap(handle);
}

void mergablefile::index() {
	this->handle->rewind();

	while(this->handle->next_frame()) {

		wlanpcap_frame * currentFrame = this->handle->get_frame();
		const unsigned char * bytes = currentFrame->getframepayload();
		if(*bytes==0x80) {
			//frame is a beacon

			//timestamp in the pcap file
			timeval pcap_timestamp=currentFrame->getpcaptimestamp();
			unsigned long  pcap_timestamp_micro_seconds=pcap_timestamp.tv_sec*1000000 /*no of usec per sec*/ + pcap_timestamp.tv_usec;

			//timestamp in the beacon frame
			ieee80211_beacon_header * beacon = (ieee80211_beacon_header*)(bytes+sizeof(ieee80211_management_header));
			unsigned long beacon_timestamp = beacon->timestamp;

			//SSID
			std::string ssid="";
			unsigned int currentIndex=sizeof(ieee80211_beacon_header);
			unsigned int maxIndex = currentFrame->getframepayloadlength();
			for(;currentIndex<maxIndex;currentIndex++) {

				u_int8_t type = *(u_int8_t*)(beacon+currentIndex);
				currentIndex++;
				u_int8_t length = *(u_int8_t*)(beacon+currentIndex);
				currentIndex++;
				if(type==0) {//SSID!
					ssid=std::string((char *)beacon+currentIndex,length);
					break;
				}
				currentIndex+=length;
			}



			//broadcast/anonymous ssids consists of NULL values so skip these
			if(*(ssid.c_str()) != '\0') {
				std::map<std::string,std::map<unsigned long, unsigned long > >::iterator ssidIt= this->ssidindex.find(ssid);

				std::map<unsigned long,unsigned long> ssidMap;
				if(ssidIt != this->ssidindex.end())
					ssidMap = ssidIt->second;

				ssidMap[beacon_timestamp]=pcap_timestamp_micro_seconds;
				this->ssidindex[ssid]=ssidMap;
			}


		}


	}

	this->handle->rewind();
}

bool mergablefile::match(mergablefile* reference) {
	std::map<std::string,std::map<unsigned long, unsigned long> >::iterator ssidIt;
	for(ssidIt=this->ssidindex.begin();ssidIt!=this->ssidindex.end();ssidIt++) {
		std::map<std::string,std::map<unsigned long, unsigned long> >::iterator ssidItRef;
		ssidItRef=reference->ssidindex.find(ssidIt->first);
		if(ssidItRef!=reference->ssidindex.end()) {
			//SSID match
			std::map<unsigned long,unsigned long>::iterator tsIt;
			for(tsIt=ssidIt->second.begin();tsIt!=ssidIt->second.end();tsIt++) {
				std::map<unsigned long,unsigned long>::iterator tsItRef=ssidItRef->second.find(tsIt->first);
				if(tsItRef!=ssidItRef->second.end()) {
					//TS match
					this->offset=reference->offset + (tsIt->second-tsItRef->second);//usec
					return true;
				}
			}
		}
	}
	return false;

}

void mergablefile::setOffset(unsigned long offset) {
	this->offset=offset;
}

unsigned long mergablefile::getOffset() {
	return this->offset;
}

