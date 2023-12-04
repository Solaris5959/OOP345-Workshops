// WS04 - Jan 28 2023
// cheese.h
// Michael Huang

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>
#include <string>

namespace sdds {
class Cheese {

  std::string name{"NaC"}; // NaC - Not a cheese
  size_t weight{};
  double pricePerG{};
  std::string features{};

public:
  Cheese(){};
  Cheese(const std::string &cheese);
  Cheese slice(size_t weight);

  std::string getName() const;
  size_t getWeight() const;
  double getPrice() const;
  std::string getFeatures() const;
};

// helper
std::string trim(const std::string &str);
std::ostream &operator<<(std::ostream &os, const Cheese &cheese);

}; // namespace sdds

#endif
