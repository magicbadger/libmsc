#include <vector>
#include <iostream>
#include <unistd.h>

#include <mot.h>
#include <mot/contenttypes.h>

#include <msc/datagroups.h>
#include <msc/output/zmq.h>

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
    SegmentEncoder segment_encoder;
    vector<Segment> segments = segment_encoder.Encode(o);
    DatagroupEncoder datagroup_encoder; 
    vector<Datagroup> datagroups = datagroup_encoder.Encode(segments);

    //Output* output = new ConsoleOutput();
	cout << "creating output" << endl;
    Output* output = new ZmqOutput("tcp://localhost:8001");
	cout << "opening output: " << output << endl;
    output->Open();
    for(Datagroup datagroup : datagroups)
    {
		cout << "writing datagroup to output" << endl;
        output->Write(datagroup.Encode());
        sleep(2);
    }
	cout << "closing output" << endl;
    output->Close();
    return  0;
}
