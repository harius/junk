#include "ServerGameModel.hpp"
#include "sigc++/sigc++.h"
#include <functional>

namespace junk
{

ServerGameModel::ServerGameModel()
 : logger("server_game_model.log", "SERVER_GAME_MODEL", true), isRunning(false)
{
	logger << "ServerGameModel created";
}

ServerGameModel::~ServerGameModel()
{
	logger << "ServerGameModel destroyed";
}

ServerGameModel::~ServerGameModel()
{
}

void ServerGameModel::start()
{
	isRunning = true;
	gameLoopTimer.restart();
	gameLoopThread = std::thread(std::ref(*this));

	logger << "Game model started";
}

void ServerGameModel::stop()
{
	gameChangesMutex.lock();
	isRunning = false;
	gameChangesMutex.unlock();

	gameLoopThread.join();

	logger << "Game model stopped";
}

IDType ServerGameModel::addPlayer(sf::Vector2f position, sf::Vector2f rotation)
{
	gameChangesMutex.lock();

	logger << "Adding a player...";

	IDType newPlayerID = 0;
	for (auto &unit : units)
	{
		if (newPlayerID == unit.first)
		{
			newPlayerID++;
		}
	}

	logger << std::string("New player ID = ") + std::to_string(newPlayerID);

	std::shared_ptr<unit::Unit> newPlayerPtr;
	newPlayerPtr = std::move(std::shared_ptr<unit::Unit>(new unit::Player(position, rotation)));

	units.insert(std::make_pair(newPlayerID, std::move(newPlayerPtr)));

	logger << "Player added";

	gameChangesMutex.unlock();

	return newPlayerID;
}

void ServerGameModel::removePlayer(IDType playerID)
{
	gameChangesMutex.lock();

	logger << std::string("Removing a player with ID = ") + std::to_string(playerID);

	if (units.find(playerID) == units.end())
	{
		logger << "There is no such player";
	}
	else
	{
		units.erase(playerID);
		logger << "Player removed";
	}

	gameChangesMutex.unlock();
}

void ServerGameModel::move(IDType playerID, sf::Vector2f vector)
{
	static const float speed = 25.0; // will be deleted

	gameChangesMutex.lock();

	if (units.find(playerID) == units.end())
	{
		logger << "There is no such player";
	}
	else
	{	
		units.at(playerID)->setMoveVector(vector);
		units.at(playerID)->setMoveSpeed(speed);

		logger << std::string("Movement vector of player with ID = ") + std::to_string(playerID);
		logger << std::string("changed to (") + std::to_string(vector.x) 
			+ std::string(", ") + std::to_string(vector.y) + std::string(")");
	}

	gameChangesMutex.unlock();
}

void ServerGameModel::rotate(IDType playerID, sf::Vector2f rotation)
{
	gameChangesMutex.lock();

	if (units.find(playerID) == units.end())
	{
		logger << "There is no such player";
	}
	else
	{
		dynamic_cast<unit::RotatableUnit*>(units.at(playerID).get())->setPosition(rotation);
		logger << std::string("View vector of player with ID = ") + std::to_string(playerID);
		logger << std::string("changed to (") + std::to_string(rotation.x) 
			+ std::string(", ") + std::to_string(rotation.y) + std::string(")");
	}
	directionUpdatedSignal(playerID, rotation);

	gameChangesMutex.unlock();
}

/*void ServerGameModel::fire(IDType playerID)
{
	gameChangesMutex.lock();

	gameChangesMutex.unlock();
}*/

/*bool ServerGameModel::subscribeForFireSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	fireSignal.connect(slot);
}*/

void ServerGameModel::subscribeForPositionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	logger << "Subscribing for positionUpdatedSignal";
	positionUpdatedSignal.connect(slot);
}

void ServerGameModel::subscribeForDirectionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	logger << "Subscribing for directionUpdatedSignal";
	directionUpdatedSignal.connect(slot);
}

void ServerGameModel::operator()()
{
	while (true)
	{	
		gameChangesMutex.lock();

		if (!isRunning)
		{
			gameChangesMutex.unlock();
			break;
		}

		for (auto &unit : units)
		{
			unit.second->synchronize(gameLoopTimer);
		}

		/*for (auto player : players)
		{
			for (auto bullet : bullets)
			{
				if (player.second.interactsWith(bullet.second))
				{
				}
			}
		}*/

		gameChangesMutex.unlock();
	}

	return;
} // namespace unit

} // namespace junk
