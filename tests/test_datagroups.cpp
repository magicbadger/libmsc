#include <vector>
#include <iostream>

#include <mot.h>
#include <mot/contenttypes.h>

#include <msc/datagroups.h>
#include "msc/util.h"

using namespace std;
using namespace mot;
using namespace msc;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    SequentialTransportIdGenerator id(8541);
    int transportId = id.Next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("application/txt"));
    SegmentEncoder encoder;
    vector<Segment> segments = encoder.Encode(o);
    cout << "encoded into " << segments.size() << " segments" << endl;
    DatagroupEncoder datagroupEncoder;
    vector<Datagroup> datagroups = datagroupEncoder.Encode(segments);
    cout << "encoded into " << datagroups.size() << " datagroups" << endl;
    for(Datagroup datagroup : datagroups)
    {
        cout << "datagroup" << endl;
        cout << "=========" << endl;
        cout << datagroup.Encode();
        cout << endl;
    }
}
