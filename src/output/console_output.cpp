#include "console_output.h"
#include "util.h"

#include <iostream>

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
