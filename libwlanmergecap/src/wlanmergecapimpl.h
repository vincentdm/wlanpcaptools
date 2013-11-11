/*
 * wlanmergecapimpl.h
 *
 *  Created on: 5-nov.-2013
 *      Author: vincent
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
