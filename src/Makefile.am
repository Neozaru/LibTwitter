top_srcdir = ../

AUTOMAKE_OPTIONS = subdir-objects

#lib_LTLIBRARIES = libtwitter.la
bin_PROGRAMS = testSuite

#libtwitter_la_SOURCES = Twitter/JSON_Parser.cpp Twitter/JSON_Parser.h

testSuite_SOURCES = Twitter/JSON_Parser.cpp Twitter/JSON_Parser.h \
					Twitter/Session.cpp Twitter/Session.h \
					Twitter/User.cpp Twitter/User.h \
					Twitter/Tweet.cpp Twitter/Tweet.h \
					Twitter/Direct_Message.cpp Twitter/Direct_Message.h \
					Twitter/User_Stream.cpp Twitter/User_Stream.h \
					Twitter/Parsable_Object.h \
					tests.cpp

testSuite_LDADD = $(jsoncpp_LIBS) $(libtwitterc_LIBS)

AM_CPPFLAGS = $(jsoncpp_CFLAGS)


# Remove is libcurl is statically linked
testSuite_LDADD += $(libcurl_LIBS)
AM_CPPFLAGS += $(libcurl_CFLAGS)
