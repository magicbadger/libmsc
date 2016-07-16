#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <vector>

using namespace std;

namespace msc
{

    class Output
    {

    public:

        virtual ~Output() = 0;

        virtual int Open() { return 0; };

        virtual int Write(const vector<unsigned char> bytes) = 0;

        virtual int Close() { return 0; };

    private:

    };

}

#endif 
