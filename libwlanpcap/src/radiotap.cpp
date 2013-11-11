/*
 * radiotap.c
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
 */

#include "radiotap.h"
struct wlan_linktype_function_set * radiotap_init() {
	struct wlan_linktype_function_set * radiotap_set = new wlan_linktype_function_set();
	radiotap_set->strip=&radiotap_strip;
	radiotap_set->getheaderlength=&radiotap_getheaderlength;
	radiotap_set->dealloc=&radiotap_dealloc;


	return radiotap_set;
}


void radiotap_dealloc(struct wlan_linktype_function_set * set) {
	delete set;
}

const u_char * radiotap_strip(const u_char * frame) {
	return frame+radiotap_getheaderlength(frame);
}

unsigned short radiotap_getheaderlength(const u_char * frame) {
	return ((ieee80211_radiotap_header *)frame)->it_len;
}
