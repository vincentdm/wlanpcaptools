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

#ifndef __WLAN_PCAP_H
#define __WLAN_PCAP_H

#include <pcap.h>
//for pcap functions and pcap_pkthdr

#include "visibilityhelper.h"


#ifdef __cplusplus

class wlanpcap;
class wlanpcap_frame;

/**
 * C interface
 */

extern "C" {
#endif

#ifndef __cplusplus
typedef void * wlanpcap_t;
typedef void * wlanpcap_frame_t;
#else
typedef wlanpcap * wlanpcap_t;
typedef wlanpcap_frame * wlanpcap_frame_t;
#endif


struct wlan_linktype_function_set;
/**
 * Function Pointer definitions for PCAP_LINKTYPE specific functions
 * e.g. strip
 */
typedef const unsigned char * (*frame_captureheader_strip_func)(const unsigned char *);
typedef unsigned short (*frame_captureheader_getlength_func)(const unsigned char *);
typedef void (*linktype_dealloc_func)(struct wlan_linktype_function_set *);

struct wlan_linktype_function_set {
	frame_captureheader_strip_func strip;
	frame_captureheader_getlength_func  getheaderlength;
	linktype_dealloc_func dealloc;

};

WLAN_API void wlanpcap_init();
WLAN_API void wlanpcap_destroy();

WLAN_API wlanpcap_t wlanpcap_open(const char * filename);
WLAN_API void wlanpcap_delete(wlanpcap_t handle);


#ifdef __cplusplus
}// end extern "C"

/**
 * C++ interface
 */

#include <string>

class wlanpcap_frame {
public:

	static wlanpcap_frame * wlanpcap_frame_copy(const wlanpcap_frame *);//copy constructor from pointer
	virtual ~wlanpcap_frame(){};


	virtual const unsigned char * getframebytes()=0;
	virtual const unsigned char * getframepayload()=0;
	virtual const unsigned int getframepayloadlength()=0;
	virtual pcap_pkthdr * getpcapheader()=0;
	virtual const timeval getpcaptimestamp()=0;
	virtual bool equals(wlanpcap_frame * frame)=0;
	virtual wlanpcap_t getsource()=0;

protected:
	wlanpcap_frame(){};

private:


};

class wlanpcap {
public:


	static wlanpcap_t create_wlanpcap(const std::string & filename);
	static void delete_wlanpcap(wlanpcap_t pcap);

	virtual void open()=0;
	virtual void close()=0;
	virtual void rewind()=0;
	virtual int getdatalinktype()=0;
	virtual wlanpcap_frame_t  get_frame()=0;
	virtual bool next_frame()=0;

	virtual ~wlanpcap(){};

	virtual wlan_linktype_function_set * get_functions()=0;
protected:


	wlanpcap(){};
};


#endif


#endif // __WLAN_PCAP_H
