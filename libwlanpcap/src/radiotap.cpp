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
