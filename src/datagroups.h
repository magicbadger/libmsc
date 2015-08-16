#ifndef DATAGROUPS_H_
#define DATAGROUPS_H_

#include <vector>

#include <mot.h>

using namespace mot;
using namespace std;

namespace msc {

    class Datagroup
    {

    public:

        Datagroup(Segment& segment, int continuity);

        vector<unsigned char> encode();

    private:

        Segment& segment;

        int continuity;

    };

    class DatagroupEncoder
    {

    public:

        DatagroupEncoder();

        vector<Datagroup> encode_datagroups(vector<Segment> segments);

    private:

    };

}

#endif
