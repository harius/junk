// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ClientService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace ::junk;

class ClientServiceHandler : virtual public ClientServiceIf
{
public:

  ClientServiceHandler()
  {
    // Your initialization goes here
  }

  void connect()
  {
    // Your implementation goes here
    printf("connect\n");
  }

  void move(const int32_t id, const Vector2f& direction)
  {
    // Your implementation goes here
    printf("move\n");
  }

  void rotate(const int32_t id, const Vector2f& direction)
  {
    // Your implementation goes here
    printf("rotate\n");
  }

  void fire(const int32_t id, const Vector2f& direction)
  {
    // Your implementation goes here
    printf("fire\n");
  }

};

int main(int argc, char **argv)
{
  int port = 9090;
  shared_ptr<ClientServiceHandler> handler(new ClientServiceHandler());
  shared_ptr<TProcessor> processor(new ClientServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

