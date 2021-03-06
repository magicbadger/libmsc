#include <iostream>

#include <msc/datagroups.h>
#include <msc/util.h>

using namespace std;

namespace msc
{
    Datagroup::Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
                        unsigned int repetition) :
        data(data), type(type), continuity(continuity), repetition(repetition)
    { }

    Datagroup::Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
                    unsigned int repetition, bool last, unsigned int segment_number) :
        data(data), type(type), continuity(continuity), repetition(repetition), last(last),
        segment_number(segment_number)
    { }

    Datagroup::Datagroup(vector<unsigned char> data, unsigned int type, unsigned int continuity, 
                    unsigned int repetition, bool last, unsigned int segment_number, 
                    unsigned int transport_id) :
        data(data), type(type), continuity(continuity), repetition(repetition), last(last),
        segment_number(segment_number), transport_id(transport_id)
    { }

    vector<unsigned char> Datagroup::Encode() const
    {
        // MSC data group header
        bitset<16> datagroup_header_bits(repetition + // remaining repetition (4)
                        (continuity << 4) + // continuity (4)
                        (type << 8) + // datagroup type (4)
                        (1 << 12) + // user access flag (1)
                        (1 << 13) + // segment flag (1)
                        (1 << 14) + // CRC flag (1)
                        (0 << 15)); // extension flag (1)

        // segment field
        bitset<16> session_header_bits(segment_number + // segment number (15)
                        (last << 15)); // last (1)

        // user access field
        bitset<24> useraccess_field_bits(transport_id + // transport ID (16)
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
        bytes = bytes + data;

        // calculate CRC
            vector<unsigned char> crc_data = bits_to_bytes(bitset<16>(calculate_crc(bytes)));
        bytes = bytes + crc_data; 

        return bytes;
    }

    static const unsigned int table[256] = {
        0x0000U,0x1189U,0x2312U,0x329BU,0x4624U,0x57ADU,0x6536U,0x74BFU,
        0x8C48U,0x9DC1U,0xAF5AU,0xBED3U,0xCA6CU,0xDBE5U,0xE97EU,0xF8F7U,
        0x1081U,0x0108U,0x3393U,0x221AU,0x56A5U,0x472CU,0x75B7U,0x643EU,
        0x9CC9U,0x8D40U,0xBFDBU,0xAE52U,0xDAEDU,0xCB64U,0xF9FFU,0xE876U,
        0x2102U,0x308BU,0x0210U,0x1399U,0x6726U,0x76AFU,0x4434U,0x55BDU,
        0xAD4AU,0xBCC3U,0x8E58U,0x9FD1U,0xEB6EU,0xFAE7U,0xC87CU,0xD9F5U,
        0x3183U,0x200AU,0x1291U,0x0318U,0x77A7U,0x662EU,0x54B5U,0x453CU,
        0xBDCBU,0xAC42U,0x9ED9U,0x8F50U,0xFBEFU,0xEA66U,0xD8FDU,0xC974U,
        0x4204U,0x538DU,0x6116U,0x709FU,0x0420U,0x15A9U,0x2732U,0x36BBU,
        0xCE4CU,0xDFC5U,0xED5EU,0xFCD7U,0x8868U,0x99E1U,0xAB7AU,0xBAF3U,
        0x5285U,0x430CU,0x7197U,0x601EU,0x14A1U,0x0528U,0x37B3U,0x263AU,
        0xDECDU,0xCF44U,0xFDDFU,0xEC56U,0x98E9U,0x8960U,0xBBFBU,0xAA72U,
        0x6306U,0x728FU,0x4014U,0x519DU,0x2522U,0x34ABU,0x0630U,0x17B9U,
        0xEF4EU,0xFEC7U,0xCC5CU,0xDDD5U,0xA96AU,0xB8E3U,0x8A78U,0x9BF1U,
        0x7387U,0x620EU,0x5095U,0x411CU,0x35A3U,0x242AU,0x16B1U,0x0738U,
        0xFFCFU,0xEE46U,0xDCDDU,0xCD54U,0xB9EBU,0xA862U,0x9AF9U,0x8B70U,
        0x8408U,0x9581U,0xA71AU,0xB693U,0xC22CU,0xD3A5U,0xE13EU,0xF0B7U,
        0x0840U,0x19C9U,0x2B52U,0x3ADBU,0x4E64U,0x5FEDU,0x6D76U,0x7CFFU,
        0x9489U,0x8500U,0xB79BU,0xA612U,0xD2ADU,0xC324U,0xF1BFU,0xE036U,
        0x18C1U,0x0948U,0x3BD3U,0x2A5AU,0x5EE5U,0x4F6CU,0x7DF7U,0x6C7EU,
        0xA50AU,0xB483U,0x8618U,0x9791U,0xE32EU,0xF2A7U,0xC03CU,0xD1B5U,
        0x2942U,0x38CBU,0x0A50U,0x1BD9U,0x6F66U,0x7EEFU,0x4C74U,0x5DFDU,
        0xB58BU,0xA402U,0x9699U,0x8710U,0xF3AFU,0xE226U,0xD0BDU,0xC134U,
        0x39C3U,0x284AU,0x1AD1U,0x0B58U,0x7FE7U,0x6E6EU,0x5CF5U,0x4D7CU,
        0xC60CU,0xD785U,0xE51EU,0xF497U,0x8028U,0x91A1U,0xA33AU,0xB2B3U,
        0x4A44U,0x5BCDU,0x6956U,0x78DFU,0x0C60U,0x1DE9U,0x2F72U,0x3EFBU,
        0xD68DU,0xC704U,0xF59FU,0xE416U,0x90A9U,0x8120U,0xB3BBU,0xA232U,
        0x5AC5U,0x4B4CU,0x79D7U,0x685EU,0x1CE1U,0x0D68U,0x3FF3U,0x2E7AU,
        0xE70EU,0xF687U,0xC41CU,0xD595U,0xA12AU,0xB0A3U,0x8238U,0x93B1U,
        0x6B46U,0x7ACFU,0x4854U,0x59DDU,0x2D62U,0x3CEBU,0x0E70U,0x1FF9U,
        0xF78FU,0xE606U,0xD49DU,0xC514U,0xB1ABU,0xA022U,0x92B9U,0x8330U,
        0x7BC7U,0x6A4EU,0x58D5U,0x495CU,0x3DE3U,0x2C6AU,0x1EF1U,0x0F78U,
    };

    unsigned short calculate_crc(vector<unsigned char> buf)
    {
        unsigned short crc = 0xFFFFU;
        for(auto c : buf) {
            crc = table[(unsigned short)c ^ (unsigned char)crc] ^ (crc >> 8);
        }
        crc = crc ^ 0xFFFFU;
        return crc;
    }

}
