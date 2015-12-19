#include <vector>
#include <iostream>

#include <mot.h>
#include <mot_contenttypes.h>

#include <datagroups.h>
#include <datagroups_mot.h>
#include <packets.h>

#include "msc_util.h"
#include "test_util.h"

using namespace std;
using namespace mot;
using namespace msc;

int main() {
    // data payload
    string data("==========");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8541);
    int transportId = id->next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.addParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment*> segments = encoder.encode(o);
    cout << "encoded into " << segments.size() << " segments" << endl;
    ASSERT("segments", segments.size(), 2);

    DatagroupEncoder datagroupEncoder;
    vector<Datagroup*> datagroups = datagroupEncoder.encode_datagroups(segments);
    cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    ASSERT("datagroups", datagroups.size(), 2);

    PacketEncoder packetEncoder(1, 96);
    vector<Packet*> packets = packetEncoder.encode_packets(datagroups);
    cout << "encoded into " << packets.size() << " packets" << endl;
    ASSERT("packets", packets.size(), 2);

    ASSERT("packet 1", bytes_to_hex(packets.at(0)->encode()),
            "CC 01 30 73 00 80 00 12 21 5D 00 25 00 00 00 A0 12 82 00 CC 0B 40 54 65 73 74 4F 62 6A 65 63 74 D0 0F 61 70 70 6C 69 63 61 74 69 6F 6E 2F 74 78 74 62 B2 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 D3 E2");

    ASSERT("packet 2", bytes_to_hex(packets.at(1)->encode()),
            "DC 01 15 74 00 80 00 12 21 5D 00 0A 3D 3D 3D 3D 3D 3D 3D 3D 3D 3D CF 6F 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 9E EB");

    return 0;
}
