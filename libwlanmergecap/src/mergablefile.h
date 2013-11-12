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
