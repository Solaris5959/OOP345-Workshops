#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <list>
#include <cmath>
#include "CovidCollection.h"

namespace sdds {
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

    void CovidCollection::display(std::ostream& out, const std::string& country) const {
        unsigned int totalCases = 0;
        unsigned int totalDeaths = 0;
        unsigned int countryCases = 0;
        unsigned int countryDeaths = 0;
        
        if (country != "ALL")
            out << "Displaying information of country = " << country << std::endl;

        std::for_each(m_collection.begin(), m_collection.end(), 
            [&](const Covid& covid) {
            totalCases += covid.cases;
            totalDeaths += covid.deaths;

            if (country == "ALL" || covid.country == country) {
                countryCases += covid.cases;
                countryDeaths += covid.deaths;
                out << covid << std::endl;
            }
        });

        double countryPercentage = (static_cast<double>(countryCases) / totalCases) * 100;
        double worldPercentage = (static_cast<double>(countryDeaths) / totalDeaths) * 100;

        if (country == "ALL") {
/*
|                                                  Total cases around the world: 43134 |
|                                                 Total deaths around the world: 18101 |
----------------------------------------------------------------------------------------            
*/
            out << "| " << std::setw(78) << std::right << "Total cases around the world:" << std::setw(6) << totalCases << " |" << std::endl;
            out << "| " << std::setw(78) << std::right << "Total deaths around the world:" << std::setw(6) << totalDeaths << " |" << std::endl;
        }
        else {
/*
----------------------------------------------------------------------------------------
|                                                   Total cases in United States: 3634 |
|                                                  Total deaths in United States: 1513 |
|           United States has 8.424908% of global cases and 8.358654% of global deaths |
----------------------------------------------------------------------------------------
*/
            out << "----------------------------------------------------------------------------------------" << std::endl;
            out << "| " << std::setw(79) << std::right << "Total cases in " + country + ":" 
                << std::setw(5) << countryCases << " |" << std::endl;
            out << "| " << std::setw(79) << std::right << "Total deaths in " + country + ":" 
                << std::setw(5) << countryDeaths << " |" << std::endl;

            // Print the percentages line by constructing a string with the precisions of the percentages set
            std::ostringstream percentageStream;
            percentageStream << std::right << country << " has " << std::fixed << std::setprecision(6) 
                             << countryPercentage << "% of global cases and " << worldPercentage << "% of global deaths |";

            std::string percentageString = percentageStream.str();

            out << "| " << std::setw(86) << percentageString << std::endl;
        }
    }

    void CovidCollection::sort(const std::string& field) {
        std::sort(m_collection.begin(), m_collection.end(), 
            [&](const Covid& a, const Covid& b) {
            if (field == "country") {
                return (a.country == b.country) ? a.deaths < b.deaths : a.country < b.country;
            }
            else if (field == "city") {
                return (a.city == b.city) ? a.deaths < b.deaths : a.city < b.city;
            }
            else if (field == "variant") {
                return (a.variant == b.variant) ? a.deaths < b.deaths : a.variant < b.variant;
            }
            else if (field == "year") {
                return (a.year == b.year) ? a.deaths < b.deaths : a.year < b.year;
            }
            else if (field == "cases") {
                return (a.cases == b.cases) ? a.deaths < b.deaths : a.cases < b.cases;
            }
            else {
                return a.deaths < b.deaths || (a.deaths == b.deaths && a.country < b.country);
            }
        });
    }

    bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const {
        return std::any_of(m_collection.begin(), m_collection.end(), 
            [&](const Covid& covid) {
            return (covid.variant) == variant && (covid.country == country) && (covid.deaths > deaths);
        });
    }

    std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
        std::list<Covid> result;
        std::copy_if(m_collection.begin(), m_collection.end(), std::back_inserter(result), 
            [&](const Covid& covid) {
            return covid.deaths >= deaths;
        });
        return result;
    }

    void CovidCollection::updateStatus() {
        std::for_each(m_collection.begin(), m_collection.end(), 
            [](Covid& covid) {
            if (covid.deaths > 300)
                covid.status = "EPIDEMIC";
            else if (covid.deaths < 50)
                covid.status = "EARLY";
            else
                covid.status = "MILD";
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
            << std::setw(3) << std::right << theCovid.deaths << " | | " << std::setw(8) << theCovid.status << " |";
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