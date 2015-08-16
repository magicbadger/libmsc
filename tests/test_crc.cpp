#define CATCH_CONFIG_MAIN

#include <vector>
#include <iostream>

#include "catch.hpp"
#include "datagroups.h"

using namespace std;

TEST_CASE( "CRC encoding tests", "[msc]" ) {

	SECTION ("CRC") {
		string data("123456789");
		vector<unsigned char> bytes;
		copy(data.begin(), data.end(), back_inserter(bytes));
        unsigned int crc = calculate_crc(bytes);
        REQUIRE(crc == 0x906e);
	}

}