// WS04 - Jan 28 2023
// cheese.cpp
// Michael Huang
#include "Cheese.h"
#include <iomanip>
#include <iostream>
#include <string>

namespace sdds {

// one line of "Name, Weight, Price, Features" as input
Cheese::Cheese(const std::string &str) {
  size_t start{}, end{};
  end = str.find(",", start);
  name = trim(str.substr(start, end - start));

  start = end + 1;
  end = str.find(",", start);
  weight = stoul(str.substr(start, end - start));

  start = end + 1;
  end = str.find(",", start);
  pricePerG = stod(str.substr(start, end - start));

  while (end != str.length()) {
    start = end + 1;
    end = str.find(",", start);
    if (end == std::string::npos)
      end = str.length();
    features += trim(str.substr(start, end - start)) + " ";
  }
}

// slice the cheese and get some if possible, otherwise you get not a cheese
Cheese Cheese::slice(size_t wei) {
  Cheese cheese = Cheese();
  if (weight >= wei) {
    weight -= wei;
    cheese = *this;
    cheese.weight = wei;
  }
  return cheese;
}

std::string Cheese::getName() const { return name; }
size_t Cheese::getWeight() const { return weight; }
double Cheese::getPrice() const { return pricePerG; }
std::string Cheese::getFeatures() const { return features; }

// helper
std::string trim(const std::string &str) {
  const size_t first = str.find_first_not_of(" ");
  const size_t last = str.find_last_not_of(" ");
  std::string val = str.substr(first, last - first + 1);
  return val;
}

std::ostream &operator<<(std::ostream &os, const Cheese &cheese) {
  os << "|" << std::left << std::setw(21) << cheese.getName() << "|"
     << std::setw(5) << cheese.getWeight() << "|" << std::setw(5) << std::fixed
     << std::setprecision(2) << cheese.getPrice() << "|" << std::setw(34)
     << std::right << cheese.getFeatures() << "|" << std::endl;
  return os;
}

}; // namespace sdds
