/*
 * prism.h
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
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
