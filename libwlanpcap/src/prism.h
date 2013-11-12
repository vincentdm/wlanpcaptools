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

#ifndef PRISM_H_
#define PRISM_H_

#include "wlanpcap.h"
#include "compat.h"

WLAN_LOCAL struct wlan_linktype_function_set * prism_init();
WLAN_LOCAL void prism_dealloc(struct wlan_linktype_function_set* set);

WLAN_LOCAL const u_char * prism_strip(const u_char * frame);
WLAN_LOCAL unsigned short prism_getheaderlength(const u_char * frame);


#endif /* PRISM_H_ */
