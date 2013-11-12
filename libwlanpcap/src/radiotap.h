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

#ifndef RADIOTAP_H_
#define RADIOTAP_H_

#include "wlanpcap.h"
#include "compat.h"

struct ieee80211_radiotap_header {
        u_int8_t        it_version;     /* set to 0 */
        u_int8_t        it_pad;
        u_int16_t       it_len;         /* entire length */
        u_int32_t       it_present;     /* fields present */
} __attribute__((__packed__));

WLAN_LOCAL struct wlan_linktype_function_set * radiotap_init();
WLAN_LOCAL void radiotap_dealloc(wlan_linktype_function_set*);

WLAN_LOCAL const u_char * radiotap_strip(const u_char * frame);
WLAN_LOCAL unsigned short radiotap_getheaderlength(const u_char * frame);



#endif /* RADIOTAP_H_ */
