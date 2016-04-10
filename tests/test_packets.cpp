#include <vector>
#include <iostream>

#include <mot.h>
#include <mot/contenttypes.h>

#include <msc/datagroups.h>
#include <msc/packets.h>
#include <msc/util.h>

#include "test_util.h"

using namespace std;
using namespace mot;
using namespace msc;

int main() {
    // data payload
    string data(120, '=');
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator id(8541);
    int transportId = id.Next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(o);
    DatagroupEncoder datagroupEncoder;
    vector<Datagroup> datagroups = datagroupEncoder.Encode(segments);

    PacketEncoder packetEncoder(1, 96);
    vector<Packet> packets = packetEncoder.Encode(datagroups);
    cout << "encoded into " << packets.size() << " packets" << endl;
    ASSERT("number of packets", packets.size(), 3);

    // examine each packet
    Packet p1 = packets.at(0);
    cout << "checking first packet" << endl;
    ASSERT("packet 1: data", bytes_to_hex(p1.Encode()),
            "CC 01 30 73 00 80 00 12 21 5D 00 25 00 00 07 80 12 82 00 CC 0B 40 54 65 73 74 4F 62 6A 65 63 74 D0 0F 61 70 70 6C 69 63 61 74 69 6F 6E 2F 74 78 74 2A 17 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 2A");
    ASSERT("packet 1: address", p1.Address(), 1);
    ASSERT("packet 1: first", p1.First(), true);
    ASSERT("packet 1: last", p1.Last(), true);
    ASSERT("packet 1: continuity index", p1.Continuity(), 0);

    Packet p2 = packets.at(1);
    ASSERT("packet 2: data", bytes_to_hex(p2.Encode()),
            "D8 01 5B 74 00 80 00 12 21 5D 00 78 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D C1 EC");
    ASSERT("packet 2: address", p2.Address(), 1);
    ASSERT("packet 2: first", p2.First(), true);
    ASSERT("packet 2: last", p2.Last(), false);
    ASSERT("packet 2: continuity index", p2.Continuity(), 1);

    Packet p3 = packets.at(2);
    ASSERT("packet 3: data", bytes_to_hex(p3.Encode()),
            "E4 01 28 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D 26 D3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 C1 87");
    ASSERT("packet 3: address", p3.Address(), 1);
    ASSERT("packet 3: first", p3.First(), false);
    ASSERT("packet 3: last", p3.Last(), true);
    ASSERT("packet 3: continuity index", p3.Continuity(), 2);

    return 0;
}
