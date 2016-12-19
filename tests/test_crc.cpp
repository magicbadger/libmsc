#include <vector>
#include <iostream>

#include <msc/datagroups.h>

using namespace std;
using namespace msc;

/*
Classic CRC check
http://reveng.sourceforge.net/crc-catalogue/16.htm
*/
int main() {
    string data("123456789");
    vector<unsigned char> bytes;
    copy(data.begin(), data.end(), back_inserter(bytes));
    unsigned short crc = calculate_crc(bytes);
    return crc != 0x906e;
}
