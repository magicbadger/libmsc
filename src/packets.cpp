#include "packets.h"
#include "common.h"

#include <algorithm>
#include <iostream>

using namespace std;
using namespace msc;

Packet::Packet(int size, int continuity, int address, vector<unsigned char> data, bool first, bool last)
	: size(size), continuity(continuity), address(address), data(data), first(first), last(last)
{ }

vector<unsigned char> Packet::encode()
{
    // packet header 
	bitset<24> packet_header(data.size() +  // useful data length (7)
                             (0 << 7) + // command (1)
                             (address << 8) + // address (10)
							 (last << 18) + // last (1)
						 	 (first << 19) + // first (1)
							 (continuity << 20) + // continuity (2)
                             ((size/24-1) << 22)); // size (2)

	// piece the data together
	vector<unsigned char> bytes;
	bytes = bytes + bits_to_bytes(packet_header);

	// data payload
	bytes = bytes + data; 

    // padding
    vector<unsigned char> padding(size - bytes.size() - 2, (char)0);
    bytes = bytes + padding;

	// calculate CRC
    vector<unsigned char> crc_data = bits_to_bytes(bitset<16>(calculate_crc(bytes)));
	bytes = bytes + crc_data; 

	return bytes;
}

PacketEncoder::PacketEncoder(int address, int size)
    : address(address), size(size), continuity(0)
{}

vector<Packet*> PacketEncoder::encode_packets(vector<Datagroup*> datagroups)
{
    vector<Packet*> packets;
    for(Datagroup* datagroup : datagroups)
    {
        vector<unsigned char> data = datagroup->encode();
        vector<unsigned char>::iterator start, end;
        start = end = data.begin();
        bool first = true; 
        while(end != data.end())
        {
            int b = distance(end, data.end());
            int step = min(size - 3 - 2, b);
            advance(end, step);
            vector<unsigned char> chunk(end - start);
            copy(start, end, chunk.begin());
            advance(start, step);
            bool last = (end == data.end()); 
            packets.push_back(new Packet(size, continuity, address, chunk, first, last));
            continuity = (continuity+1)%4;;
            first = false;
        }
    }

    return packets;        
}
