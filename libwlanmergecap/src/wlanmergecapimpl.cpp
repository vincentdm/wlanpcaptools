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


#include "wlanmergecapimpl.h"
#include <pcap.h>

#ifndef NDEBUG
#include <iostream>
#endif

wlanmergecap * wlanmergecap::create_wlanmergecap(const std::vector<std::string> & filenames) {
	return new wlanmergecapimpl(filenames);
}

void wlanmergecap::delete_wlanmergecap(wlanmergecap_t mergecap) {
	delete (mergecap);
}



wlanmergecapimpl::wlanmergecapimpl(const std::vector<std::string> & filenames):
			wlanmergecap(),
			inputFileNames(filenames),
			removeDuplicates(false) {

}

wlanmergecapimpl::~wlanmergecapimpl() {

}

void wlanmergecapimpl::match(std::vector<mergablefile*>  files) {

	std::vector<mergablefile*>::iterator ffIt,sfIt;

	for(ffIt=(++files.begin());ffIt!=files.end();ffIt++) {
		bool match=false;
		for(sfIt=files.begin();sfIt!=files.end() &&  match==false;sfIt++) {
			if(*sfIt!=*ffIt )
				continue;
			match=(*ffIt)->match(*sfIt);
		}
	}

}

mergablefile * wlanmergecapimpl::getnextframe(std::vector<mergablefile*> files) {
	unsigned long bestTimestamp=0xFFFFFFFFFFFFFFFF;
	mergablefile * candidate=NULL;
	for(std::vector<mergablefile*>::iterator fIt = files.begin();fIt!=files.end();fIt++) {
		wlanpcap_frame_t cFrame = (*fIt)->getframe();
		if(cFrame != NULL) {
			timeval cPts = cFrame->getpcaptimestamp();
			unsigned long cTs = (*fIt)->getOffset() + cPts.tv_sec*10000000 + cPts.tv_usec;

			if(cTs<bestTimestamp) {
				bestTimestamp=cTs;
				candidate=*fIt;
			}
		}
	}
	return candidate;
}

void wlanmergecapimpl::merge(const std::string& outputFileName) {
	std::vector<mergablefile*> inputFiles;
	std::vector<std::string>::iterator ifnIt;
	for(ifnIt=this->inputFileNames.begin();ifnIt!=this->inputFileNames.end();ifnIt++) {
		mergablefile * f = new mergablefile(*ifnIt);
		inputFiles.push_back(f);
	}

#ifndef NDEBUG
	std::cout << "indexing input files to eachother" << std::endl;
#endif
	/**
	 * INDEX the beacon SSIDs and timestamps
	 */
	std::vector<mergablefile*>::iterator ifIt;
	for(ifIt=inputFiles.begin();ifIt!=inputFiles.end();ifIt++) {
		(*ifIt)->index();
	}

	/**
	 * MATCH the files against eachother, so we know the offset between a
	 * reference file and all others
	 */
#ifndef NDEBUG
	std::cout << "matching input files to eachother" << std::endl;
#endif
	this->match(inputFiles);

	/**
	 * do the real MERGE
	 */

	pcap_t * dump_pcap=pcap_open_dead(DLT_IEEE802_11_RADIO,1518);
	pcap_dumper_t * dumper = pcap_dump_open(dump_pcap,outputFileName.c_str());

	mergablefile * currentSource = NULL;

	//for duplicate detection
	wlanpcap_frame * lastFrame=NULL;
	while ((currentSource=this->getnextframe(inputFiles))!=NULL) {
		wlanpcap_frame_t  currentframe = currentSource->getframe();

#ifndef NDEBUG
		std::cout << "Got frame from source " << (void*) currentSource << std::endl;
		std::cout << "\tframe = " << (void*)currentframe << std::endl;
#endif

		if(this->removeduplicates() && lastFrame!=NULL && currentframe->equals(lastFrame)) {
			currentSource->next();
			continue;
		}

		pcap_pkthdr * header = currentframe->getpcapheader();
		unsigned long newts_usec = header->ts.tv_sec*1000000+header->ts.tv_usec+currentSource->getOffset();
		header->ts.tv_sec=newts_usec/1000000;
		header->ts.tv_usec=newts_usec%1000000;

		pcap_dump((unsigned char *)dumper,header,currentframe->getframebytes());

		if(lastFrame!=NULL)
			delete lastFrame;

		lastFrame=wlanpcap_frame::wlanpcap_frame_copy(currentframe);

		currentSource->next();



	}

	pcap_dump_close(dumper);
	pcap_close(dump_pcap);

	//cleanup
	for(ifIt=inputFiles.begin();ifIt!=inputFiles.end();ifIt++) {
		delete(*ifIt);
	}




}
