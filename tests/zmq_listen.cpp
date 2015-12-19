#include <iostream>
#include <zmq.h>
#include <vector>

using namespace std;

int main() 
{
    void *ctx = zmq_ctx_new();
    void *socket = zmq_socket(ctx, ZMQ_SUB);
    
    zmq_bind(socket, "tcp://0.0.0.0:8001");
    zmq_setsockopt(socket, ZMQ_SUBSCRIBE, NULL, 0);

    while(true) {
        zmq_msg_t msg;
        zmq_msg_init(&msg);
        zmq_msg_recv(&msg, socket, 0);
        const char* data = static_cast<const char*>(zmq_msg_data(&msg));
        string s(data, data+zmq_msg_size(&msg));
        cout << s << flush;
        zmq_msg_close (&msg);
    }

    return 0;
}
