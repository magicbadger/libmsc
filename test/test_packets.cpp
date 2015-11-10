#include <vector>
#include <iostream>

#include <mot.h>
#include <contenttypes.h>

#include "datagroups.h"
#include "packets.h"

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
    SegmentEncoder encoder;
    vector<Segment*> segments = encoder.encode(o);
    cout << "encoded into " << segments.size() << " segments" << endl;
    DatagroupEncoder datagroupEncoder;
    vector<Datagroup*> datagroups = datagroupEncoder.encode_datagroups(segments);
    cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    PacketEncoder packetEncoder(1, 96);
    vector<Packet*> packets = packetEncoder.encode_packets(datagroups);
    cout << "encoded into " << packets.size() << " packets" << endl;
    for(Packet* packet : packets)
    {
        cout << "packet" << endl;
        cout << "=========" << endl;
        cout << packet->encode();
        cout << endl;
    }
}
