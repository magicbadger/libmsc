#ifndef PACKETS_H_
#define PACKETS_H_

#include <vector>
#include <stdlib.h>

#include "common.h"
#include "datagroups.h"

using namespace std;

namespace msc {

    namespace PacketSize {
        const int Size_24 = 24;
    }

    class Packet
    {

    public:

        Packet(int size, int continuity, int address, vector<unsigned char> data, bool first, bool last);

        vector<unsigned char> encode();

    private:

        int size;

        int continuity;

        int address;

        vector<unsigned char> data;

        bool first, last;

    };

    class PacketEncoder
    {

    public:
        
        PacketEncoder(int address, int size);

        vector<Packet*> encode_packets(vector<Datagroup*> datagroups);

    private:

        int address;

        int size;

        int continuity;

    };

}

#endif
