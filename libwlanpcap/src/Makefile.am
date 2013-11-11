AM_CPPFLAGS=\
	-DWLAN_DLL -DWLAN_DLL_EXPORTS \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libwlanpcap/include

AM_CXXFLAGS=



	
noinst_LTLIBRARIES=libwlanpcap.la


#wlanpcap library
libwlanpcap_la_SOURCES=\
	radiotap.cpp \
	prism.cpp \
	wlanpcapimpl.cpp \
	wlanpcap_c.cpp \
	wlanpcapframeimpl.cpp

libwlanpcap_la_LDFLAGS= -fvisiblity=hidden
libwlanpcap_la_LIBADD=\
	-lpcap
