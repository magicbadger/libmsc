#include <vector>
#include <iostream>

#include <datagroups.h>

using namespace std;
using namespace msc;

int main() {
    cout << "1";
    string data("123456789");
    cout << "2";
    vector<unsigned char> bytes;
    cout << "3";
    copy(data.begin(), data.end(), back_inserter(bytes));
    cout << "4";
    unsigned short crc = calculate_crc(bytes);
    cout << "5";
    return crc != 0x906e;
}
