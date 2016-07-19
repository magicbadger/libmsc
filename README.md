libmsc
======

Encoder/Decoder for MSC Datagroup and Packet data as per ETSI 300 401 Section 5.3, Main Service Channel (MSC).

# Dependencies

* zeromq
* libmot

# Current Status

Able to do some simple encoding of MOT objects to MSC Datagroups and MSC Packets. 

Entirely couple with `libmot` (https://github.com/magicbadger/libmot), in the respect that it can only encode MOT `Segment` objects.

# TODO

* Decouple from libmot (provide methods to encode non MOT segment data)
* Datagroup decoding
* Packet decoding

# Examples

Encoding a simple text MOT object into Datagroups and write out the resultant data to the console as a set of hex pairs.

```cpp
#include <vector>
#include <iostream>

#include <mot.h>
#include <mot/contenttypes.h>
#include <msc/datagroups.h>
#include <msc/packets.h>

#include <msc/util.h>

using namespace std;
using namespace mot;
using namespace msc;

int main() {
    string data("=====");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));

    // create the transport ID and MOT object
    SequentialTransportIdGenerator id(8541);
    int transportId = id.Next();
    MotObject o(transportId, "TestObject", bytes, ContentTypes::Text::ASCII);
    o.AddParameter(new MimeType("application/txt"));

    // setup the encoders
    SegmentEncoder segment_encoder;
    DatagroupEncoder datagroup_encoder;
    PacketEncoder packet_encoder(1, PacketSize::Size_96);

    // encode to segments
    vector<Segment> segments = segment_encoder.Encode(o);

    // encode to datagroups
    vector<Datagroup> datagroups = datagroup_encoder.Encode(segments);

    // encode to packets
    vector<Packet> packets = packet_encoder.Encode(datagroups);

    for(Packet packet : packets)
    {
        cout << bytes_to_hex(packet.Encode()) << endl;
    }

    return  0;
}
```

# building

``
autoreconf -if
./configure
make
``

# installing

``
make install
``

# uninstalling

``
make uninstall
``
