#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include <client/model/ClientModel.hpp>
#include <client/view/ClientView.hpp>

namespace junk
{

class ClientController
{
public:
  explicit ClientController(ClientView& view, ClientModel& model);
  ~ClientController();

  void moveHandler(sf::Vector2f direction);
  void fireHandler(sf::Vector2f direction);
  void rotateHandler(sf::Vector2f direction);

  void clientPositionUpdatedHandler(int16_t id, sf::Vector2f direction);
  void clientDirectionUpdatedHandler(int16_t id, sf::Vector2f direction);

private:
  ClientView& view;
  ClientModel& model;

  Logger logger;
  
}; // ClientController

} // namespace junk