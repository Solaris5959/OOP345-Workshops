// Workshop 2 - Summer 2023
// AirportModels.cpp
// Rania Arbash

#include <fstream>
#include <iostream>
#include <iomanip>
#include "AirportModels.h"

namespace sdds {

    std::ostream& operator<<(std::ostream& os, const Airport& ap) {
        if (ap.airport_code != "")
        {
            os << std::setfill('.');
            os << std::setw(20) << std::right << "Airport Code" << " : "
                << std::setw(30) << std::left << ap.airport_code << '\n'
                << std::setw(20) << std::right << "Airport Name" << " : "
                << std::setw(30) << std::left << ap.airport_name << '\n'
                << std::setw(20) << std::right << "City" << " : "
                << std::setw(30) << std::left << ap.city << '\n'
                << std::setw(20) << std::right << "State" << " : "
                << std::setw(30) << std::left << ap.state << '\n'
                << std::setw(20) << std::right << "Country" << " : "
                << std::setw(30) << std::left << ap.country << '\n'
                << std::setw(20) << std::right << "Latitude" << " : "
                << std::setw(30) << std::left << ap.LATITUDE << '\n'
                << std::setw(20) << std::right << "Longitude" << " : "
                << std::setw(30) << std::left << ap.LONGITUDE << '\n'
                ;
            os << std::setfill(' ');
        }
        else {
            os << "Empty Airport";
        }
        return os;
    }

    AirportLog::AirportLog() {}
    AirportLog::AirportLog(const AirportLog& copy) {
        airports = new Airport[copy.num_airports];
        for (size_t i = 0; i < copy.num_airports; i++) {
            this->airports[i] = copy.airports[i];
        }
        num_airports = copy.num_airports;


    }
    AirportLog::AirportLog(const char* filename) {
        if (filename) {
            std::ifstream fin(filename);
            if (fin.is_open()) {

                std::string line;
                getline(fin, line); // extract header
                while (getline(fin, line).good()) {
                    num_airports++;
                }

                airports = new Airport[num_airports];

                // Reset stream and start pos 
                fin.clear();
                fin.seekg(0);

                size_t idx = 0;
                getline(fin, line); // extract header
                while (fin && idx < num_airports) {
                    Airport temp;
                    getline(fin, temp.airport_code, ',');
                    getline(fin, temp.airport_name, ',');
                    getline(fin, temp.city, ',');
                    getline(fin, temp.state, ',');
                    getline(fin, temp.country, ',');

                    fin >> temp.LATITUDE;
                    fin.ignore();
                    fin >> temp.LONGITUDE;
                    fin.ignore();

                    airports[idx] = temp;
                    idx++;
                }
                // Alternatively use addMatch to implement
            }
        }
    }

    AirportLog::~AirportLog() {
        delete[] airports;
    }

    void AirportLog::addAirport(Airport airport) {

        Airport* temp = new Airport[num_airports + 1];
        for (auto i = 0u; i < num_airports; ++i) {
            temp[i] = airports[i];
        }
        temp[num_airports] = airport;
        delete[] airports;
        airports = temp;
        num_airports++;
    }

    AirportLog AirportLog::findAirport(const char* state, const char* county) const {
        AirportLog ret{};
        for (auto i = 0u; airports && i < num_airports; ++i) {

            if (airports[i].state == state && airports[i].country == county )
                ret.addAirport(airports[i]);
        }
        return ret;
    }

    Airport AirportLog::operator[](size_t i) const {
        if (this->airports) {
            return airports[i];
        }
        return Airport();
    }

    AirportLog::operator size_t() const {
        return num_airports;
    }
};
