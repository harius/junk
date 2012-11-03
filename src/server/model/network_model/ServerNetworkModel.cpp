#include "ServerNetworkModel.hpp"

namespace junk
{

sf::Vector2f convert(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

ServerNetworkModel::ServerNetworkModel() : logger("SERVER_NETWORK_MODEL", "server_model.log", true)
{
  handler = boost::shared_ptr<ClientServiceHandler > (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor > (new ClientServiceProcessor(handler));
  protocolFactory = boost::shared_ptr<TProtocolFactory > (new TBinaryProtocolFactory());

  // using thread pool with maximum 15 threads to handle incoming requests
  threadManager = boost::shared_ptr<ThreadManager > (ThreadManager::newSimpleThreadManager(15));
  threadFactory = boost::shared_ptr<PosixThreadFactory > (new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  server = boost::shared_ptr<TNonblockingServer >
    (new TNonblockingServer(processor, protocolFactory, 7777, threadManager));

  serverThread = std::shared_ptr<std::thread >
    (new std::thread(&TNonblockingServer::serve, server.get()));

  handler->moveSignal.connect(this->moveSignal);
  handler->rotateSignal.connect(this->rotateSignal);
  handler->fireSignal.connect(this->fireSignal);
  handler->connectSignal.connect(this->connectSignal);
  handler->getChangesSignal.connect(this->getChangesSignal);

  logger << "ServerNetworkModel created";
}

ServerNetworkModel::~ServerNetworkModel()
{
  logger << "ServerNetworkModel destructed";
}

Vector2f convertSFMLtoThrift(const sf::Vector2f& v)
{
  Vector2f v1;
  v1.x = v.x;
  v1.y = v.y;
  return v1;
}

} // namespace junk
