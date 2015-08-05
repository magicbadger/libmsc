#include "datagroups.h"
#include "common.h"

using namespace std;

Datagroup::Datagroup(Segment& segment, int continuity)
	: segment(segment), continuity(continuity)
{ }

vector<unsigned char> Datagroup::encode()
{
	// MSC data group header
	bitset<16> datagroup_header_bits(segment.getRepetition() + // remaining repetition (4)
									(continuity << 4) + // continuity (4)
									(segment.getType() << 8) + // datagroup type (4)
									(1 << 12) + // user access flag (1)
									(1 << 13) + // segment flag (1)
									(1 << 14) + // CRC flag (1)
									(0 << 15)); // extension flag (1)

	// segment field
	bitset<16> session_header_bits(segment.getIndex() + // segment number (15)
								  (segment.isLast() << 15)); // last (1)


	// user access field
	bitset<24> useraccess_field_bits(segment.getTransportId() + // transport ID (16)
									(2 << 16) + // user access length indicator (4)
									(1 << 20) + // transport ID flag (1)
									(0 << 21)); // RFA (3)
	// piece the data together
	vector<unsigned char> bytes;

	// headers
	bytes = bytes + bits_to_bytes(datagroup_header_bits);
	bytes = bytes + bits_to_bytes(session_header_bits);
	bytes = bytes + bits_to_bytes(useraccess_field_bits);

	// data payload
	bytes = bytes + segment.encode();

	// calculate CRC
    vector<unsigned char> crc_data = bits_to_bytes(bitset<16>(calculate_crc(bytes)));
	bytes = bytes + crc_data; 

	return bytes;
}
