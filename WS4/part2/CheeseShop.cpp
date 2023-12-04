// WS04 - Jan 28 2023
// cheeseshop.cpp
// Michael Huang

#include "Cheese.h"
#include "CheeseShop.h"
#include <iostream>
#include <string>

namespace sdds {
CheeseShop::CheeseShop(const std::string &n) { name = n; }

CheeseShop &CheeseShop::addCheese(const Cheese &c) {
  // resize array to add a copy of the cheese
  const Cheese **temp = new const Cheese *[num_cheeses + 1];
  for (auto i = 0u; i < num_cheeses; ++i) {
    temp[i] = new Cheese(*cheeses[i]);
  }

  temp[num_cheeses] = new Cheese(c);
  for (auto i = 0u; i < num_cheeses; ++i)
    delete cheeses[i];
  delete[] cheeses;

  num_cheeses++;
  cheeses = temp;
  return *this;
}

// rule of 5
CheeseShop::CheeseShop(const CheeseShop &src) { *this = src; }

CheeseShop &CheeseShop::operator=(const CheeseShop &src) {
  if (this != &src) {
    for (auto i = 0u; i < num_cheeses; ++i)
      delete cheeses[i];
    delete[] cheeses;
    cheeses = nullptr;

    num_cheeses = src.num_cheeses;
    name = src.name;

    if (src.cheeses) {
      cheeses = new const Cheese *[num_cheeses];
      for (auto i = 0u; i < num_cheeses; ++i) {
        cheeses[i] = new Cheese(*src.cheeses[i]);
      }
    }
  }

  return *this;
}

CheeseShop::CheeseShop(CheeseShop &&src) { *this = std::move(src); }

CheeseShop &CheeseShop::operator=(CheeseShop &&src) {
  if (this != &src) {
    for (auto i = 0u; i < num_cheeses; ++i)
      delete cheeses[i];
    delete[] cheeses;

    num_cheeses = src.num_cheeses;
    name = src.name;
    cheeses = src.cheeses;
    src.num_cheeses = 0;
    src.name = "";
    src.cheeses = nullptr;
  }

  return *this;
}

CheeseShop::~CheeseShop() {
  for (auto i = 0u; i < num_cheeses; ++i)
    delete cheeses[i];
  delete[] cheeses;
}

std::ostream &operator<<(std::ostream &os, const CheeseShop &cs) {
  os << "--------------------------\n";
  os << cs.name << "\n";
  os << "--------------------------\n";
  if (!cs.cheeses) {
    os << "This shop is out of cheese!\n";
  } else {
    for (auto i = 0u; i < cs.num_cheeses; ++i)
      os << *cs.cheeses[i];
  }
  os << "--------------------------\n";
  return os;
}
}; // namespace sdds
