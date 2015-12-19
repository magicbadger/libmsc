ACLOCAL_AMFLAGS=-I config

#
# Library 
#
lib_LTLIBRARIES = src/libmsc.la

include_HEADERS = \
    include/datagroups.h \
    include/datagroups_mot.h \
    include/packets.h

src_libmsc_la_SOURCES = \
    src/datagroups.cpp \
    src/datagroups_mot.cpp \
    src/output.cpp \
    src/packets.cpp \
    src/output/console_output.cpp \
    src/output/console_output.h \
    src/output/zmq_output.cpp \
    src/output/zmq_output.h


src_libmsc_la_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
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
tests_test_crc_CPPFLAGS = -Iinclude
tests_test_crc_LDADD = -Lsrc/.libs -lmsc

tests_test_output_SOURCES = \
    tests/test_output.cpp 
tests_test_output_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
tests_test_output_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot -L${LIBZMQ_LIBS} -lzmq

tests_test_datagroups_SOURCES = \
    tests/test_datagroups.cpp 
tests_test_datagroups_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_datagroups_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

tests_test_packets_SOURCES = \
    tests/test_packets.cpp 
tests_test_packets_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_packets_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
