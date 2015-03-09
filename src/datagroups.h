#ifndef DATAGROUPS_H_
#define DATAGROUPS_H_

#include <vector>

#include "../../libmot/src/mot.h"

using namespace mot;
using namespace std;

class Datagroup
{

public:

	Datagroup(Segment& segment, int continuity);

	vector<unsigned char> encode();

private:

	Segment& segment;

	int continuity;

};

vector<unsigned char> calculate_crc(vector<unsigned char> data)
{
	// uuuuuhhhhh yeh. CRC goes here. I guess.
	return "AB";
}


#endif
