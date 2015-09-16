bin_PROGRAMS = test_crc test_datagroups test_packets write_datagroups write_packets test_output zmq_listen

test_crc_SOURCES = test_crc.cpp
test_crc_LDADD = -L../src -lmsc

test_datagroups_SOURCES = test_datagroups.cpp
test_datagroups_CPPFLAGS = -I../src -I${libmot_CFLAGS}
test_datagroups_LDADD = -L../src -lmsc -L${libmot_LIBS} -lmot

test_packets_SOURCES = test_packets.cpp
test_packets_CPPFLAGS = -I../src -I${libmot_CFLAGS}
test_packets_LDADD = -L../src -lmsc -L${libmot_LIBS} -lmot

write_datagroups_SOURCES = write_datagroups.cpp
write_datagroups_CPPFLAGS = -I../src -I${libmot_CFLAGS}
write_datagroups_LDADD = -L../src -lmsc -L${libmot_LIBS} -lmot

write_packets_SOURCES = write_packets.cpp
write_packets_CPPFLAGS = -I../src -I${libmot_CFLAGS}
write_packets_LDADD = -L../src -lmsc -L${libmot_LIBS} -lmot

test_output_SOURCES = test_output.cpp
test_output_CPPFLAGS = -I../src -I${libmot_CFLAGS} -I${libzmq_CFLAGS}
test_output_LDADD = -L../src -lmsc -L${libmot_LIBS} -lmot -L${libzmq_LIBS} -lzmq

zmq_listen_SOURCES = zmq_listen.cpp
zmq_listen_CPPFLAGS = -I${libzmq_CFLAGS}
zmq_listen_LDADD = -L${libzmq_LIBS} -lzmq
