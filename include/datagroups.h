#ifndef DATAGROUPS_H_
#define DATAGROUPS_H_

#include <vector>

using namespace std;

namespace msc {

    class Datagroup
    {

    public:

	Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
		  unsigned int repetition);

	Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
		  unsigned int repetition, bool last, unsigned int segment_number);

	Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
		  unsigned int repetition, bool last, unsigned int segment_number, 
		  unsigned int transport_id);

	vector<unsigned char> encode() const;


    private:

	vector<unsigned char> data;

	unsigned int type;

	unsigned int continuity;

	unsigned int repetition;

	bool last;

	unsigned int segment_number;

	unsigned int transport_id;

    };

    unsigned short calculate_crc(vector<unsigned char> data);

}

#endif // DATAGROUPS_H_
