ACLOCAL_AMFLAGS=-I config

#
# Library 
#
lib_LTLIBRARIES = src/libmsc.la

include_HEADERS = \
    include/datagroups.h \
    include/packets.h

src_libmsc_la_SOURCES = \
    src/common.h \
    src/common.cpp \
    src/datagroups.cpp \
    src/output.cpp \
    src/packets.cpp \
    util.h \
    src/output/console_output.cpp \
    src/output/console_output.h \
    src/output/zmq_output.cpp \
    src/output/zmq_output.h


src_libmsc_la_CPPFLAGS = -I include -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
src_libmsc_la_CXXFLAGS = @LIBMSC_EXTRA_CXXFLAGS@
src_libmsc_la_LIBADD = -L${LIBMOT_LIBS} -L${LIBZMQ_LIBS}

#
# Tests
#
test_apps = \
    tests/test_crc \
    tests/test_output \
    tests/test_datagroups \
    tests/test_packets 

tests_test_crc_SOURCES = \
    tests/test_crc.cpp 
tests_test_crc_LDADD = src/libmsc.la

tests_test_output_SOURCES = \
    tests/test_output.cpp 
tests_test_output_LDADD = src/libmsc.la

tests_test_datagroups_SOURCES = \
    tests/test_datagroups.cpp 
tests_test_datagroups_LDADD = src/libmsc.la

tests_test_packets_SOURCES = \
    tests/test_packets.cpp 
tests_test_packets_LDADD = src/libmsc.la

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
