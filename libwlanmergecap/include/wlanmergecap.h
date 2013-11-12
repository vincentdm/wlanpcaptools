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


#ifndef WLANMERGECAP_H_
#define WLANMERGECAP_H_

#ifdef __cplusplus

class wlanmergecap;

extern "C" {
#endif

#ifndef __cplusplus
	typedef void * wlanmergecap_t;
#else
	typedef wlanmergecap * wlanmergecap_t;
#endif




#ifdef __cplusplus
}//end if extern "C"

#include <vector>
#include <string>

class wlanmergecap {

public:
	static wlanmergecap_t create_wlanmergecap(const std::vector<std::string> & files);
	static void delete_wlanmergecap(wlanmergecap_t mergecap);


	virtual ~wlanmergecap(){};

	virtual void merge(const std::string & outputFileName)=0;

	virtual bool removeduplicates()=0;
	virtual void removeduplicates(bool)=0;



protected:
	wlanmergecap() {};




};
#endif

#endif /* WLANMERGECAP_H_ */
