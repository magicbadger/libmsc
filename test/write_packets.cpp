#include <vector>
#include <iostream>

#include <mot.h>
#include <contenttypes.h>

#include "../src/datagroups.h"

using namespace std;
using namespace mot;
using namespace msc;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8541);
    int transportId = id->next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.addParameter(new MimeType("application/txt"));
    SegmentEncoder segment_encoder;
    vector<Segment*> segments = segment_encoder.encode(o);
    DatagroupEncoder datagroup_encoder; 
    vector<Datagroup*> datagroups = datagroup_encoder.encode_datagroups(segments);
    PacketEncoder packet_encoder;
    vector<Packet*> packets = packet_encoder.encode_packets(datagroups);

    for(Packet* packet : packets)
    {
        cout << packet->encode();
    }
    return  0;
}
