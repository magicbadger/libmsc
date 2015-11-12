#include <iostream>

#include "msc_util.h"
#include "console_output.h"
#include "datagroups.h"


namespace msc
{

    ConsoleOutput::ConsoleOutput()
    {
    }

    ConsoleOutput::~ConsoleOutput()
    {
    }
    
    int ConsoleOutput::Write(const vector<unsigned char> buffer)
    {
        cout << buffer;
        return 0;
    }

}
