#include <vector>
#include <iostream>
#include <unistd.h>

#include <mot.h>
#include <mot_contenttypes.h>

#include <datagroups.h>
#include <datagroups_mot.h>
#include "output.h"
#include "output/zmq_output.h"

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

    //Output* output = new ConsoleOutput();
	cout << "creating output" << endl;
    Output* output = new ZmqOutput("tcp://localhost:8001");
	cout << "opening output: " << output << endl;
    output->Open();
    for(Datagroup* datagroup : datagroups)
    {
		cout << "writing datagroup to output" << endl;
        output->Write(datagroup->encode());
        sleep(2);
    }
	cout << "closing output" << endl;
    output->Close();
    return  0;
}
