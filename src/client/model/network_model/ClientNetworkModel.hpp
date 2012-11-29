#pragma once

#include <SFML/System.hpp>
#include <common/logger/Logger.hpp>
#include <common/service/client/ClientServiceHandler.hpp>

#include <boost/uuid/uuid.hpp>

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

namespace junk
{

class ClientNetworkModel
{
public:
  ClientNetworkModel();
  ~ClientNetworkModel();

  int32_t connectToServer(const std::string& serverIp, int port);

  GameChanges getGameChanges();
  void makeAction(const Action& action);

  void shutdown();

private:
  SessionInfo sessionInfo;

  boost::shared_ptr<TSocket> socket;
  boost::shared_ptr<TTransport> transport;
  boost::shared_ptr<TProtocol> protocol;
  boost::shared_ptr<ClientServiceClient> clientServiceClient;

  std::mutex socketMutex;

  Logger logger;

  bool alive;

}; // ClientNetworkModel

} // namespace junk
