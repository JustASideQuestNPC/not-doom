#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

enum Action {
  MOVE_FORWARD,
  MOVE_BACK,
  TURN_LEFT,
  TURN_RIGHT,
  STRAFE_LEFT,
  STRAFE_RIGHT,
  MOVE_UP,
  MOVE_DOWN,
  LOOK_UP,
  LOOK_DOWN,
};

const std::vector<std::string> actionNames {
  "move forward",
  "move back",
  "turn left",
  "turn right",
  "strafe left",
  "strafe right",
  "move up",
  "move down",
  "look up",
  "look down",
};

struct KeyBinding {
  sf::Keyboard::Key key;
  bool requiresModifier; // if true, will only activate when the modifier key is currently pressed. if false, will only activate when it is not pressed
};

// switches between the two action sets
sf::Keyboard::Key modifierKey{sf::Keyboard::LShift};

std::map<Action, KeyBinding> keybinds {
  { MOVE_FORWARD,   { sf::Keyboard::W,      false } },
  { MOVE_BACK,   { sf::Keyboard::S,      false } },
  { TURN_LEFT,      { sf::Keyboard::A,      false } },
  { TURN_RIGHT,     { sf::Keyboard::D,      false } },
  { STRAFE_LEFT,    { sf::Keyboard::Left,   false } },
  { STRAFE_RIGHT,   { sf::Keyboard::Right,  false } },
  { MOVE_UP,        { sf::Keyboard::D,      true  } },
  { MOVE_DOWN,      { sf::Keyboard::A,      true  } },
  { LOOK_UP,        { sf::Keyboard::W,      true  } },
  { LOOK_DOWN,      { sf::Keyboard::S,      true  } },
};

std::map<Action, bool> actionMap{};