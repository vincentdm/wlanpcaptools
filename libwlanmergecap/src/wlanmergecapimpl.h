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

#ifndef WLANMERGECAPIMPL_H_
#define WLANMERGECAPIMPL_H_

#include "wlanmergecap.h"
#include "wlanpcap.h"
#include "mergablefile.h"


class wlanmergecapimpl: public wlanmergecap {
public:
	wlanmergecapimpl(const std::vector<std::string> & filenames);
	virtual ~wlanmergecapimpl();

	virtual void merge(const std::string & outputFileName);
	virtual bool removeduplicates() {
		return removeDuplicates;
	}
	virtual void removeduplicates(bool newVal) {
		this->removeDuplicates=newVal;
	}
private:

	void match(std::vector<mergablefile*>  files);
	mergablefile * getnextframe(std::vector<mergablefile*> files);


	bool removeDuplicates;
	std::vector<std::string> inputFileNames;

};

#endif /* WLANMERGECAPIMPL_H_ */
