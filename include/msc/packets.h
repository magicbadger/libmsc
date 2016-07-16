#ifndef PACKETS_H_
#define PACKETS_H_

#include <vector>
#include <stdlib.h>

#include "datagroups.h"

using namespace std;

namespace msc {

    namespace PacketSize {
        const int Size_24 = 24;
        const int Size_48 = 48;
        const int Size_72 = 72;
        const int Size_96 = 96;
    }

    class Packet
    {

    public:

        Packet(int size, int continuity, int address, vector<unsigned char> data, bool first, bool last);

        vector<unsigned char> Encode();
        
        int Size() { return size; };
        
        int Continuity() { return continuity; };
        
        int Address() { return address; };
        
        bool First() { return first; };
        
        bool Last() { return last; };

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

        vector<Packet> Encode(vector<Datagroup> datagroups);

    private:

        int address;

        int size;

        int continuity;

    };

}

#endif
