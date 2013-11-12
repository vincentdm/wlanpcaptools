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

#include <iostream>
#include <cstring>
#include <vector>
#include "config.h"
#include "wlanpcap.h"
//for wlanpcap_init();
#include "wlanmergecap.h"

int print_help(const char * const myName) {

	std::cout << PACKAGE_NAME << " " PACKAGE_VERSION << std::endl;
	std::cout << "Merge two or more capture files into one." << std::endl;
	std::cout << std::endl;
	std::cout << "Usage: " << myName << " -w <outfile> <infile> [<infile> ...]" << std::endl;

	std::cout << "Output:" << std::endl;
	std::cout << std::endl;
	/*
	std::cout << "  -a                concatenate rather than merge files.
	std::cout << "                    default is to merge based on frame timestamps." << std::endl;
	std::cout << "	-s <snaplen>      truncate packets to <snaplen> bytes of data." << std::endl;
	*/
	std::cout << "	-w <outfile>|-    set the output filename to <outfile> or '-' for stdout." << std::endl;
	/*
	std::cout << "	-F <capture type> set the output file type; default is pcapng." << std::endl;
	std::cout << "	                  an empty "-F" option will list the file types." << std::endl;
	std::cout << "	-T <encap type>   set the output file encapsulation type;" << std::endl;
	std::cout << "	                  default is the same as the first input file." << std::endl;
	std::cout << "	                  an empty "-T" option will list the encapsulation types." << std::endl;
	*/
	std::cout << "Misc:" << std::endl;
	std::cout << std::endl;
	std::cout << "  -v                be verbose." << std::endl;
	std::cout << "  -h, --help        print this help and exit." << std::endl;


	std::cout << std::endl;
	return 1;
}

int main(int argc, char ** argv) {

	const char * myName = argv[0];
	char * outputFile;
	bool verbose = false;
	std::vector<std::string> inputFiles;

	if(argc < 2) {
		std::cerr << "I don't know what to merge" << std::endl;
		return print_help(myName);
	}

	bool optionsDone=false;
	for(unsigned int argi=1;argi<argc && !optionsDone;argi++) {
		char * arg = argv[argi];

		if(strncmp(arg,"-h",2) == 0 || strncmp(arg,"--help",6)==0) {
			return print_help(myName);
		} else if(strncmp(arg,"-w",2)== 0) {
			if(argc > (argi+1)) {
				outputFile = argv[++argi];
			} else {
				return print_help(myName);
			}
		} else if(strncmp(arg,"-v",2)== 0) {
			verbose=true;
		} else if(strncmp(arg,"-",1) !=0 || strncmp(arg,"--",2)==0) {
			optionsDone=true;
			if(strncmp(arg,"--",2) == 0) {
				argi++;
			}

			for(unsigned int inputFileIdx = argi; inputFileIdx < argc;inputFileIdx++) {
				inputFiles.push_back(argv[inputFileIdx]);
			}
		}


	}

	if(outputFile == 0) {
		std::cerr << "Output file not given!" << std::endl;
		return print_help(myName);
	}

	if(inputFiles.size() == 0) {
		std::cerr << "Input files not given!" << std::endl;
		return print_help(myName);
	}
	if(inputFiles.size() == 1) {
		std::cerr << "Only one input file given, this won't have any effect!" << std::endl;
		return print_help(myName);
	}


	if(verbose) {
		std::cout << "Writing output to " << outputFile << std::endl;
		std::vector<std::string>::iterator ifIt;
		std::cout << "Reading input from files:" << std::endl;
		for(ifIt=inputFiles.begin();ifIt!=inputFiles.end();ifIt++) {
			std::cout << "\t" << *ifIt << std::endl;
		}
	}

	if(verbose)
		std::cout << "Passing control to libwlanmergecap..." << std::endl;

	//first init the wlanpcap to make sure all functions are allocated

	wlanpcap_init();

	//create the merger
	wlanmergecap_t merger = wlanmergecap::create_wlanmergecap(inputFiles);

	//let it merge
	merger->removeduplicates(true);
	merger->merge(outputFile);

	//destroy it again
	wlanmergecap::delete_wlanmergecap(merger);

	//cleanup the previously allocated functions
	wlanpcap_destroy();

	return 0;
}
