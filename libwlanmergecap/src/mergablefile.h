/*
 * mergablefile.h
 *
 *  Created on: 9-nov.-2013
 *      Author: vincent
 */

#ifndef MERGABLEFILE_H_
#define MERGABLEFILE_H_


#include <map>
#include <string>
#include "wlanpcap.h"
#include "compat.h"
#include "ieee80211.h"

class mergablefile {
public:
	mergablefile(const std::string & filename);
	virtual ~mergablefile();

	void index();

	void setOffset(unsigned long offset);
	unsigned long getOffset();

	bool match(mergablefile*);

	inline bool next() {
		return this->handle->next_frame();
	}

	inline wlanpcap_frame_t getframe() {
		if(this->handle->get_frame()==NULL)
			this->handle->next_frame();
		return this->handle->get_frame();
	}

private:
	wlanpcap * handle;

	unsigned long offset;
	std::map<std::string,std::map<unsigned long,unsigned long> > ssidindex;
};

#endif /* MERGABLEFILE_H_ */
