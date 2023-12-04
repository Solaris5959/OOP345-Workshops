#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Book.h"

namespace sdds {
    sdds::Book::Book() { yearPublished = 0; salePrice = 0.0; }

    Book::Book(const std::string& strBook) {
        std::vector<std::string> result;
        std::stringstream ss(strBook);
        std::string item;

        getline(ss, item, ',');
        author = trim(item);
        getline(ss, item, ',');
        titleBook = trim(item);
        getline(ss, item, ',');
        countryPublished = trim(item);
        getline(ss, item, ',');
        salePrice = std::stod(trim(item));
        getline(ss, item, ',');
        yearPublished = std::stoi(trim(item));
        getline(ss, item, '\0');
        description = trim(item);
    }

    const std::string Book::title() const {
        return titleBook;
    }

    const std::string Book::country() const {
        return countryPublished;
    }

    const std::size_t Book::year() const {
        return yearPublished;

    }

    double& Book::price() {
        return salePrice;
    }

    std::ostream &operator<< (std::ostream &os, const Book &book) {
        os << std::setw(20) << book.author << " | " << std::setw(22) << book.titleBook << " | " 
            << std::setw(5) << book.countryPublished << " | " << std::setw(4) << book.yearPublished << " | "
            << std::setw(6) << std::fixed << std::setprecision(2) << book.salePrice << " | " << book.description;

        return os;
    }

    std::string Book::trim(const std::string& str) {   
        const auto strBegin = str.find_first_not_of(" ");
        const auto strEnd = str.find_last_not_of(" ");
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }
}