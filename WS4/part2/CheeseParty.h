// WS04 - Jan 28 2023
// cheeseparty.h
// Michael Huang

#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include <iostream>

class Cheese;

namespace sdds {

class CheeseParty {

  const Cheese **cheeses{};
  size_t num_cheeses{};

public:
  CheeseParty(){};

  CheeseParty &addCheese(const Cheese &c);
  CheeseParty &removeCheese();

  // rule of 5
  CheeseParty(const CheeseParty &src);
  CheeseParty &operator=(const CheeseParty &src);
  CheeseParty(CheeseParty &&src);
  CheeseParty &operator=(CheeseParty &&src);
  ~CheeseParty();

  friend std::ostream &operator<<(std::ostream &os, const CheeseParty &cs);
};

}; // namespace sdds

#endif
