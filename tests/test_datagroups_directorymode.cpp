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

    // create our objects
    string data(5, '='); // 5 characters 
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    vector<MotObject> objects;

    // first object
    MotObject o1(id.Next(), "Object1", bytes, ContentTypes::Text::ASCII);
    o1.AddParameter(new MimeType("application/txt"));
    objects.push_back(o1);

    // second object
    MotObject o2(id.Next(), "Object2", bytes, ContentTypes::Text::ASCII);
    o2.AddParameter(new MimeType("application/txt"));
    objects.push_back(o2);

    // third object
    MotObject o3(id.Next(), "Object3", bytes, ContentTypes::Text::ASCII);
    o3.AddParameter(new MimeType("application/txt"));
    objects.push_back(o3);

    // encode segments
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(id.Next(), objects);
    cout << "encoded into " << segments.size() << " segments" << endl;
    ASSERT("number of segments", segments.size(), 4);

    DatagroupEncoder datagroupEncoder;
    vector<Datagroup> datagroups = datagroupEncoder.Encode(segments);
    cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    ASSERT("number of datagroups", datagroups.size(), 4);

    // examine each datagroup
    Datagroup d1 = datagroups.at(0);
    cout << "checking first datagroup" << endl;
    ASSERT("first datagroup: type", d1.Type(), 6);
    ASSERT("first datagroup: last", d1.Last(), true);

    Datagroup d2 = datagroups.at(1);
    cout << "checking second datagroup" << endl;
    ASSERT("second datagroup: type", d2.Type(), 4);
    ASSERT("second datagroup: last", d2.Last(), true); 

    Datagroup d3 = datagroups.at(2);
    cout << "checking third datagroup" << endl;
    ASSERT("third datagroup: type", d3.Type(), 4);
    ASSERT("third datagroup: last", d3.Last(), true); 

    Datagroup d4 = datagroups.at(3);
    cout << "checking fourth datagroup" << endl;
    ASSERT("fourth datagroup: type", d4.Type(), 4);
    ASSERT("fourth datagroup: last", d4.Last(), true); 

    cout << bytes_to_hex(d1.Encode()) << " " << bytes_to_hex(d2.Encode()) << " " << bytes_to_hex(d3.Encode()) << " " << bytes_to_hex(d4.Encode());

    return 1;
}
