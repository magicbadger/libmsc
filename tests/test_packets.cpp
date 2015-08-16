#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include <mot.h>

#include "catch.hpp"
#include "../src/datagroups.h"
#include "../src/packets.h"

using namespace std;
using namespace mot;
using namespace msc;

TEST_CASE( "MSC packet encoding tests", "[msc]" ) {

	SECTION ("PACKET") {
		string data("=====");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));
		SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8541);
		int transportId = id->next();
		MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
		o.addParameter(new MimeType("application/txt"));
		SegmentEncoder encoder;
		vector<Segment> segments = encoder.encode(o);
        DatagroupEncoder datagroupEncoder;
        vector<Datagroup> datagroups = datagroupEncoder.encode_datagroups(segments);
        PacketEncoder packetEncoder(1, 96);
        vector<Packet> packets = packetEncoder.encode_packets(datagroups);
        for(Packet packet : packets)
        {
            cout << packet.encode();
        }
	}

}
