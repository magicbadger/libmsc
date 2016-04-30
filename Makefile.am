ACLOCAL_AMFLAGS=-I config

#
# Library 
#
lib_LTLIBRARIES = src/libmsc.la

include_HEADERS = \
    include/msc/datagroups.h \
    include/msc/packets.h \
    include/msc/output/console.h \
    include/msc/output/zmq.h

src_libmsc_la_SOURCES = \
    src/msc/datagroups.cpp \
    src/msc/output.cpp \
    src/msc/packets.cpp \
    src/msc/output/console.cpp \
    src/msc/output/zmq.cpp 

src_libmsc_la_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
src_libmsc_la_CXXFLAGS = @LIBMSC_EXTRA_CXXFLAGS@
src_libmsc_la_LIBADD = -L${LIBMOT_LIBS} -L${LIBZMQ_LIBS}

#
# Tests
#
test_apps = \
    tests/test_crc \
    tests/test_output \
    tests/test_datagroups_headermode \
    tests/test_datagroups_directorymode \
    tests/test_packets 

tests_test_crc_SOURCES = \
    tests/test_crc.cpp 
tests_test_crc_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_crc_LDADD = -Lsrc/.libs -lmsc

tests_test_output_SOURCES = \
    tests/test_output.cpp 
tests_test_output_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS} -I${LIBZMQ_CFLAGS}
tests_test_output_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot -L${LIBZMQ_LIBS} -lzmq -L${LIBSODIUM_LIBS} -lsodium

tests_test_datagroups_headermode_SOURCES = \
    tests/test_datagroups_headermode.cpp 
tests_test_datagroups_headermode_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_datagroups_headermode_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

tests_test_datagroups_directorymode_SOURCES = \
    tests/test_datagroups_directorymode.cpp 
tests_test_datagroups_directorymode_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_datagroups_directorymode_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

tests_test_packets_SOURCES = \
    tests/test_packets.cpp 
tests_test_packets_CPPFLAGS = -Iinclude -I${LIBMOT_CFLAGS}
tests_test_packets_LDADD = -Lsrc/.libs -lmsc -L${LIBMOT_LIBS} -lmot

check_PROGRAMS = ${test_apps}

#  Run the test cases
TESTS = $(test_apps)
XFAIL_TESTS =

EXTRA_DIST	= COPYING NEWS README.md INSTALL.md LICENCE AUTHORS ChangeLog TODO doc
