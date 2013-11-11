noinst_LTLIBRARIES=libwlanmergecap.la

AM_CPPFLAGS=\
	-I$(top_srcdir)/libwlanpcap/include \
	-I$(top_srcdir)/libwlanmergecap/include

AM_CXXFLAGS=

libwlanmergecap_la_SOURCES=\
	mergablefile.cpp \
	wlanmergecapimpl.cpp
	
libwlanmergecap_la_LIBADD=\
	$(top_builddir)/libwlanpcap/src/libwlanpcap.la