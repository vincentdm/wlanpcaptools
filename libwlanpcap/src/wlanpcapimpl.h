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


#ifndef WLANPCAPIMPL_H_
#define WLANPCAPIMPL_H_



#include "wlanpcap.h"
#include <pcap.h>

#pragma GCC visibility push(hidden)
#include <map>


class wlanpcap_impl: public wlanpcap {
public:
	static std::map<int,wlan_linktype_function_set*> linktype_functions;

	wlanpcap_impl(const std::string & filename);
	virtual ~wlanpcap_impl();

	virtual void open();
	virtual void close();
	virtual void rewind();

	virtual int getdatalinktype();

	virtual wlanpcap_frame_t get_frame();
	virtual bool next_frame();


	virtual wlan_linktype_function_set * get_functions();
private:

	const std::string filename;
	pcap_t * handle;

	wlanpcap_frame * current_frame;
};
#pragma GCC visibility pop


#endif /* WLANPCAPIMPL_H_ */
