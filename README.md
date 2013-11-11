wlanpcaptools
=============

Tools for wireless captures taken by monitoring the wireless interface

This project contains some libraries and executables:

1. libwlanpcap: which is a library which provides a wrapper for libpcap, allowing abstraction of the wireless encapsulations (radiotap, prism...)
2. libwlanmergecap: which is a (static) library which provides all functionality to merge 2+ captures into 1 file.  
3. wlanmergecap: executable following the options of pcap mergecap to merge 2 or more files into 1 file.

features
--------

1. supported encapsulation types: radiotap and prism

todo
----
1. add convertions of encapsulation types to others (using an abstract one)
2. make indexing multithreaded if available
3. don't link to libpcap, but use dynamic loading (using ltdl)
4. fix the C only interface (only C++ interface works for now)
