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

    SequentialTransportIdGenerator id(8541);
    int transportId = id.Next();

    // create our object
    string data(250, '='); // repeating string of 20k characters
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("application/txt"));

    // segment in 100 byte segments
    ConstantSizeSegmentationStrategy *strategy = new ConstantSizeSegmentationStrategy(100);

    SegmentEncoder encoder(strategy);
    vector<Segment> segments = encoder.Encode(o);
    cout << "encoded into " << segments.size() << " segments" << endl;
    ASSERT("number of segments", segments.size(), 4);

    DatagroupEncoder datagroupEncoder;
    vector<Datagroup> datagroups = datagroupEncoder.Encode(segments);
    cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    ASSERT("number of datagroups", datagroups.size(), 4);

    // examine each datagroup
    Datagroup d1 = datagroups.at(0);
    cout << "checking first datagroup" << endl;
    ASSERT("first datagroup: type", d1.Type(), 3);
    ASSERT("first datagroup: last", d1.Last(), true);

    Datagroup d2 = datagroups.at(1);
    cout << "checking second datagroup" << endl;
    ASSERT("second datagroup: type", d2.Type(), 4);
    ASSERT("second datagroup: last", d2.Last(), false); 

    Datagroup d3 = datagroups.at(2);
    cout << "checking third datagroup" << endl;
    ASSERT("third datagroup: type", d3.Type(), 4);
    ASSERT("third datagroup: last", d3.Last(), false); 

    Datagroup d4 = datagroups.at(3);
    cout << "checking fourth datagroup" << endl;
    ASSERT("fourth datagroup: type", d4.Type(), 4);
    ASSERT("fourth datagroup: last", d4.Last(), true); 

    return 0;
}
