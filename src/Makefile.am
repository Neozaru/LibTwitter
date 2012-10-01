top_srcdir = ../

AUTOMAKE_OPTIONS = subdir-objects

#lib_LTLIBRARIES = libtwitter.la
bin_PROGRAMS = testSuite

#libtwitter_la_SOURCES = Twitter/JSON_Parser.cpp Twitter/JSON_Parser.h

testSuite_SOURCES = Twitter/JSON_Parser.cpp Twitter/JSON_Parser.h \
					Twitter/Session.cpp Twitter/Session.h \
					Twitter/User.cpp Twitter/User.h \
					Twitter/Tweet.cpp Twitter/Tweet.h \
					Twitter/Parsable_Object.h \
					tests.cpp

testSuite_LDADD = -L/usr/local/lib -ljsoncpp $(libtwitterc_LIBS)