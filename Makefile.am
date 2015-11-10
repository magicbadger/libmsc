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


src_libmsc_la_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
src_libmsc_la_CXXFLAGS = @LIBMSC_EXTRA_CXXFLAGS@
src_libmsc_la_LIBADD = -L${LIBMOT_LIBS} -L${LIBZMQ_LIBS}

#
# Tests
#
test_apps = \
    test/test_crc \
    test/test_output \
    test/test_datagroups \
    test/test_packets 

test_test_crc_SOURCES = \
    test/test_crc.cpp 
test_test_crc_LDADD = -Lsrc/.libs -lmsc

test_test_output_SOURCES = \
    test/test_output.cpp 
test_test_output_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
test_test_output_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot -L${LIBZMQ_LIBS} -lzmq

test_test_datagroups_SOURCES = \
    test/test_datagroups.cpp 
test_test_datagroups_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
test_test_datagroups_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

test_test_packets_SOURCES = \
    test/test_packets.cpp 
test_test_packets_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
test_test_packets_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
