/*
 * wlanmergecap.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
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
