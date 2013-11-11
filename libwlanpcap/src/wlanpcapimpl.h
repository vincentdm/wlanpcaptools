/*
 * wlanpcapimpl.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
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
