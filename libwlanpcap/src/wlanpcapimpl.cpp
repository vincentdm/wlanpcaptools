/*
 * wlanpcapimpl.cpp
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
 */

#include "wlanpcapimpl.h"
#include "wlanpcapframeimpl.h"

std::map<int,wlan_linktype_function_set*> wlanpcap_impl::linktype_functions;

wlanpcap_t wlanpcap::create_wlanpcap(const std::string &filename) {
	return new wlanpcap_impl(filename);
}

void wlanpcap::delete_wlanpcap(wlanpcap_t pcap) {
	delete pcap;
}


wlanpcap_impl::wlanpcap_impl(const std::string & filename):
		filename(filename) {
	this->handle=NULL;
	this->current_frame=NULL;

}

wlanpcap_impl::~wlanpcap_impl() {
	if(this->handle!=NULL) {
		pcap_close(this->handle);
		this->handle=NULL;
	}

	if(current_frame!=NULL) {
		delete this->current_frame;
	}
}

void wlanpcap_impl::open() {

	if(this->handle != NULL) {
		this->close();
	}

	char * error=NULL;
	this->handle=pcap_open_offline(this->filename.c_str(),error);
	if(this->handle==NULL && error !=NULL ) {
		throw std::string(error);
	}


	this->next_frame();
}


void wlanpcap_impl::close() {
	if(this->handle != NULL) {
		pcap_close(this->handle);
		this->handle=NULL;
	}

}

void wlanpcap_impl::rewind() {
	this->close();
	this->open();
}


int wlanpcap_impl::getdatalinktype() {
	return pcap_datalink(this->handle);
}

wlan_linktype_function_set * wlanpcap_impl::get_functions() {
	int datalink = this->getdatalinktype();
	if(wlanpcap_impl::linktype_functions.find(datalink)!=wlanpcap_impl::linktype_functions.end())
		return wlanpcap_impl::linktype_functions[datalink];
	return NULL;
}

wlanpcap_frame_t  wlanpcap_impl::get_frame() {
	return this->current_frame;
}


bool wlanpcap_impl::next_frame() {
	const u_char * bytes;
	pcap_pkthdr * header;

	wlanpcap_frame_t frame = NULL;
	bool response=false;
	if(pcap_next_ex(this->handle,&header,&bytes)==1) {
		frame=new wlanpcap_frame_impl(this,header,bytes);
		response = true;
	}


	if(this->current_frame!=NULL)
				delete this->current_frame;

	this->current_frame=frame;

	return response;


}

