#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include "CovidCollection.h"

namespace sdds {
    // CovidCollection::CovidCollection(const std::string& filename) {
    //     std::ifstream file(filename);
    //     if (!file.is_open()) 
    //         throw std::runtime_error("Failed to open file: " + filename);

    //     std::istream_iterator<std::string> file_iter(file);
    //     std::istream_iterator<std::string> eof;

    //     // Define a lambda function to create Covid objects from input lines
    //     auto createCovidObject = [](const std::string& line) {
    //         std::cout << line << std::endl;
    //         if (line.length() >= 90) {
    //             std::string country = line.substr(0, 25);
    //             std::string city = line.substr(25, 25);
    //             std::string variant = line.substr(50, 25);
    //             int year = std::stoi(line.substr(75, 5));
    //             unsigned int cases = std::stoi(line.substr(80, 5));
    //             unsigned int deaths = std::stoi(line.substr(85, 5));

    //             return Covid{ country, city, variant, year, cases, deaths };
    //         }
    //         return Covid{};
    //     };

    //     // Use std::transform to read lines and create Covid objects
    //     std::transform(file_iter, eof, std::back_inserter(m_collection), createCovidObject);

    //     file.close();
    // }  

    void readCovid(std::ifstream& file, std::vector<Covid>& m_collection) {
        std::string line;
        if (std::getline(file, line)) {
            std::string country = trim(line.substr(0, 25));
            std::string city = trim(line.substr(25, 25));
            std::string variant = trim(line.substr(50, 25));
            int year = std::stoi(trim(line.substr(75, 5)));
            unsigned int cases = std::stoi(trim(line.substr(80, 5)));
            unsigned int deaths = std::stoi(trim(line.substr(85, 5)));

            m_collection.emplace_back(Covid{ country, city, variant, year, cases, deaths });

            readCovid(file, m_collection); // Recursively read the next line
        }
    }

    CovidCollection::CovidCollection(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file: " + filename);

        readCovid(file, m_collection);

        file.close();
    }

    void CovidCollection::display(std::ostream& out) const {
        std::for_each(m_collection.begin(), m_collection.end(), [&out](const Covid& covid) {
            out << covid << std::endl;
        });
    }

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid) {
        out << "| " << std::setw(21) << std::left << theCovid.country << " | "
            << std::setw(15) << std::left << theCovid.city << " | "
            << std::setw(20) << std::left << theCovid.variant << " | "
            << std::setw(6) << std::right;
        
        if (theCovid.year < 1000)
            out << "      ";
        else 
            out << theCovid.year;

        out << " | " << std::setw(4) << std::right << theCovid.cases << " | "
            << std::setw(3) << std::right << theCovid.deaths << " |";
        return out;
    }

    std::string trim(const std::string& str) {
        const auto strBegin = str.find_first_not_of(' ');
        if (strBegin == std::string::npos)
            return ""; // no content
        const auto strEnd = str.find_last_not_of(' ');
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }
}