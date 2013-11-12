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


