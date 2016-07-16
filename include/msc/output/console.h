#ifndef CONSOLE_OUTPUT_H_
#define CONSOLE_OUTPUT_H_

#include <vector>

#include <msc/output.h>

using namespace std;

namespace msc
{

    class ConsoleOutput : public Output
    {

    public:
        
        ConsoleOutput();

        ~ConsoleOutput();
    
        int Write(const vector<unsigned char> bytes);

    };

}

#endif
