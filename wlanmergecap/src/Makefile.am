
bin_PROGRAMS=wlanmergecap

AM_CPPFLAGS=\
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libwlanpcap/include \
	-I$(top_srcdir)/libwlanmergecap/include

AM_CXXFLAGS=

wlanmergecap_SOURCES=\
	wlanmergecap.cpp
	
wlanmergecap_LDFLAGS=

wlanmergecap_LDADD=\
	$(top_builddir)/libwlanmergecap/src/libwlanmergecap.la
