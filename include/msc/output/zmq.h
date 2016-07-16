#ifndef ZMQOUTPUT_H_
#define ZMQOUTPUT_H_

#include <vector>
#include <zmq.h>
#include <string>

#include <msc/output.h>

using namespace std;

namespace msc
{

    class ZmqOutput : public Output
    {
    
    public:
        
        ZmqOutput(string destination, int io_threads = 1);
    
        ~ZmqOutput();

        int Open();
        
        int Write(const vector<unsigned char> bytes);
        
        int Close();

    private: 

        void *context; // zmq context

        void *socket; // zmq socket

        string destination; // output destination zmq://<host>:<port>
		
		int io_threads; // number of threads in the pool
		
    };

}

#endif
