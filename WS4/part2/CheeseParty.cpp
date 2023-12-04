// WS04 - Jan 28 2023
// cheeseparty.cpp
// Michael Huang

#include "Cheese.h"
#include "CheeseParty.h"
#include <iostream>
#include <string>

namespace sdds {

CheeseParty &CheeseParty::addCheese(const Cheese &c) {

  // check if cheese already in party
  bool found{false};
  for (auto i = 0u; i < num_cheeses && !found; ++i) {
    if (cheeses[i] == &c)
      found = true;
  }

  // resize array to add the cheese by address
  if (!found) {
    const Cheese **temp = new const Cheese *[num_cheeses + 1];
    for (auto i = 0u; i < num_cheeses; ++i) {
      temp[i] = cheeses[i];
    }

    temp[num_cheeses] = &c;
    delete[] cheeses;
    num_cheeses++;
    cheeses = temp;
  }
  return *this;
}

CheeseParty &CheeseParty::removeCheese() {
  // find cheeses with 0 weight and set them to nullptr to remove them
  bool found{false};
  for (auto i = 0u; i < num_cheeses && !found; ++i) {
    if (cheeses[i]->getWeight() == 0) {
      found = true;
      cheeses[i] = nullptr;
    }
  }
  return *this;
}

// rule of 5
CheeseParty::CheeseParty(const CheeseParty &src) { *this = src; }

CheeseParty &CheeseParty::operator=(const CheeseParty &src) {
  if (this != &src) {
    delete[] cheeses;
    cheeses = nullptr;
    num_cheeses = src.num_cheeses;

    if (src.cheeses) {
      cheeses = new const Cheese *[num_cheeses];
      for (auto i = 0u; i < num_cheeses; ++i) {
        cheeses[i] = src.cheeses[i];
      }
    }
  }

  return *this;
}
CheeseParty::CheeseParty(CheeseParty &&src) { *this = std::move(src); }

CheeseParty &CheeseParty::operator=(CheeseParty &&src) {
  if (this != &src) {
    delete[] cheeses;
    num_cheeses = src.num_cheeses;
    cheeses = src.cheeses;
    src.num_cheeses = 0;
    src.cheeses = nullptr;
  }
  return *this;
}

CheeseParty::~CheeseParty() { delete[] cheeses; }

std::ostream &operator<<(std::ostream &os, const CheeseParty &cs) {
  os << "--------------------------\n";
  os << "Cheese Party"
     << "\n";
  os << "--------------------------\n";
  if (!cs.cheeses) {
    os << "This party is just getting started!\n";
  } else {
    for (auto i = 0u; i < cs.num_cheeses; ++i) {
      if (cs.cheeses[i])
        os << *cs.cheeses[i];
    }
  }
  os << "--------------------------\n";
  return os;
}
} // namespace sdds
