#include <iostream>

#include <msc/segment_encoder.h>
#include <msc/util.h>

using namespace std;

namespace msc
{

    DatagroupEncoder::DatagroupEncoder()
    { }
    
    vector<Datagroup> DatagroupEncoder::Encode(vector<mot::Segment> segments)
    {
        mot::SegmentDatagroupType last_type;
        vector<Datagroup> datagroups;
        unsigned int i = 0;
        for(mot::Segment segment : segments)
        {
            if(last_type && last_type != segment.Type()) i = 0;
            Datagroup datagroup = Datagroup(segment.Encode(), segment.Type(), i%16, segment.Repetition(),
                                segment.Last(), segment.Index(), segment.TransportId());
                            
            datagroups.push_back(datagroup);
            i++;
            last_type = segment.Type();
        }

        return datagroups;
    }    
}
