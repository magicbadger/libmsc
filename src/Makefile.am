SUBDIRS = . output

lib_LIBRARIES = libmsc.a

libmsc_a_SOURCES = common.cpp common.h \
                   datagroups.cpp datagroups.h \
                   packets.cpp packets.h \
                   output.cpp output.h \
                   output/console_output.cpp output/console_output.h \
                   output/zmq_output.cpp output/zmq_output.h \
                   util.h 

libmsc_a_CPPFLAGS = -I${libmot_CFLAGS} -I${libzmq_CFLAGS}
libmsc_a_LIBADD = -L${libmot_LIBS} -lmot -L${libzmq_LIBS} -lzmq
