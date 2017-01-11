#ifndef SEGMENT_ENCODER_H_
#define SEGMENT_ENCODER_H_

#include <vector>

#include <mot.h>
#include <msc/datagroups.h>

using namespace std;

namespace msc {

    class DatagroupEncoder
    {

    public:

        DatagroupEncoder();

        vector<Datagroup> Encode(vector<mot::Segment> segments);

    private:

    };    

}

#endif // SEGMENT_ENCODER_H_
