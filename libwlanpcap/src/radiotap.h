/*
 * radiotap.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
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
