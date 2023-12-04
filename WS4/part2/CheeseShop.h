// WS04 - Jan 28 2023
// cheeseshop.h
// Michael Huang

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <iostream>
#include <string>

class Cheese;

namespace sdds {

class CheeseShop {

  std::string name;
  const Cheese **cheeses{};
  size_t num_cheeses{};

public:
  CheeseShop(const std::string &n = "No Name");

  CheeseShop &addCheese(const Cheese &c);

  // rule of 5
  CheeseShop(const CheeseShop &src);
  CheeseShop &operator=(const CheeseShop &src);
  CheeseShop(CheeseShop &&src);
  CheeseShop &operator=(CheeseShop &&src);
  ~CheeseShop();

  friend std::ostream &operator<<(std::ostream &os, const CheeseShop &cs);
};

}; // namespace sdds

#endif
