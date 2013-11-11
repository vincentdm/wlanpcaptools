/*
 * prism.cpp
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
 */

#include "prism.h"
struct wlan_linktype_function_set * prism_init() {
	struct wlan_linktype_function_set * prism_set = new wlan_linktype_function_set();
	prism_set->strip=&prism_strip;
	prism_set->getheaderlength=&prism_getheaderlength;
	prism_set->dealloc=&prism_dealloc;


	return prism_set;
}

void prism_dealloc(wlan_linktype_function_set * set) {
	delete set;
}

const u_char * prism_strip(const u_char * frame) {
	return NULL;
}

unsigned short prism_getheaderlength(const u_char * frame) {
	return 0;
}


