/*
 * wlanpcap_c.cpp
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
 */

#include "wlanpcapimpl.h"

#include "radiotap.h"
#include "prism.h"

void wlanpcap_init() {
	wlan_linktype_function_set * set;

	set  = radiotap_init();
	wlanpcap_impl::linktype_functions[DLT_IEEE802_11_RADIO]=set;

	set = prism_init();
	wlanpcap_impl::linktype_functions[DLT_PRISM_HEADER]=set;

}

void wlanpcap_destroy() {
	std::map<int,wlan_linktype_function_set *>::iterator wltfsIt;
	for(wltfsIt=wlanpcap_impl::linktype_functions.begin();wltfsIt!=wlanpcap_impl::linktype_functions.end();wltfsIt++) {
		wlan_linktype_function_set * set = wltfsIt->second;
		if(set->dealloc!=NULL) {
			linktype_dealloc_func cDealloc =set->dealloc;
			cDealloc(set);
		}
	}

	wlanpcap_impl::linktype_functions.clear();
}

wlanpcap_t wlanpcap_open(const char * filename) {
	std::string strFileName=filename;
	wlanpcap_t handle = wlanpcap::create_wlanpcap(strFileName);
	handle->open();

	return handle;
}

void wlanpcap_delete(wlanpcap_t handle) {
	wlanpcap::delete_wlanpcap(handle);
}



