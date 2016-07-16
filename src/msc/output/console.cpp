#include <iostream>

#include <msc/util.h>
#include <msc/output/console.h>
#include <msc/datagroups.h>


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
