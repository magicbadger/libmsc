#include <vector>
#include <iostream>

#include "mot.h"
#include "datagroups.h"

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
    int i = 0;
    SegmentDatagroupType last_type;
    for(Segment* segment : segments)
    {
        if(last_type && last_type != segment->getType()) i = 0;
        Datagroup d(*segment, i%16);
        cout << d.encode();
    }
    return  0;
}
