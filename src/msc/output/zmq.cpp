#include <iostream>

#include <msc/output/zmq.h>

namespace msc
{
    ZmqOutput::ZmqOutput(string destination, int io_threads) :
        destination(destination), io_threads(io_threads)
    {
        cout << "created zmq output" << endl;
    }

    ZmqOutput::~ZmqOutput()
    {
        Close();
    }

    int ZmqOutput::Open()
    {
        cout << "opening" << endl;
        
		// open the context
		context = zmq_ctx_new();
        if(context == nullptr) return 1;
        
		int err = 0;
		
		// set size of the thread pool
		err = zmq_ctx_set (context, ZMQ_IO_THREADS, io_threads);
		
		// create the socket
        socket = zmq_socket(context, ZMQ_PUB);
        if(socket == nullptr) return 1;
		
		// set the ZMQ_CONFLATE option, to only keep the last outbound
		// message in the socket queue
		bool val = true;
		err = zmq_setsockopt(context,ZMQ_CONFLATE, &val, sizeof(val));
		
		// connect the socket to the remote destination
        err = zmq_connect(socket, destination.c_str());
        if(err) return err;
		
        return 0;
    }

    int ZmqOutput::Write(vector<unsigned char> buffer)
    {
		string buf = string(buffer.begin(), buffer.end());
        cout << "sending buffer: " << buf << ", length=" << buf.size() << endl;
		int rc = zmq_send(socket, &buffer[0], buffer.size(), 0);
		if(rc != buffer.size()) return 1;
		
        return 0;
    }

    int ZmqOutput::Close()
    {
        zmq_close(socket);
        zmq_ctx_destroy(context);
        return 0;
    }   
}    
