#include "ClientNetworkModel.hpp"

namespace junk
{

ClientNetworkModel::ClientNetworkModel() : logger("client_model.log", "CLIENT_NETWORK_MODEL", true)
{
	logger << "ClientNetworkModel created";
}

void ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  socket = boost::shared_ptr<TTransport> (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient> (new ClientServiceClient(protocol));
  id = clientServiceClient->connect();
}

ClientNetworkModel::~ClientNetworkModel()
{
	logger << "ClientNetworkModel destructed";
}

ClientNetworkModel::move(sf::Vector2f direction)
{
  ClientServiceClient->move(id, direction);
}

ClientNetworkModel::rotate(sf::Vector2f direction)
{
  ClientServiceClient->rotate(id, direction);
}

ClientNetworkModel::fire(sf::Vector2f direction)
{
  ClientServiceClient->fire(id, direction);
}

} // namespace junk