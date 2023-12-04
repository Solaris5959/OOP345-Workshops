// Workshop 2 - Summer 2023
// AirportModels.h
// Rania Arbash

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <string>
#include <iostream>

namespace sdds {

    struct Airport {
        std::string airport_code{};
        std::string airport_name{};
        std::string city{};
        std::string state{};
        std::string country{};
        double LATITUDE{};
        double LONGITUDE{};
        
    };

    std::ostream& operator<<(std::ostream& os, const Airport& al);

    class AirportLog {

        Airport* airports{};
        size_t num_airports{};

    public:
        AirportLog();
        AirportLog(const char* filename);
        AirportLog(const AirportLog&);
        ~AirportLog();

        void addAirport(Airport airport);
        AirportLog findAirport( const char* state, const char* contry) const;

        Airport operator[](size_t i) const;
        operator size_t() const;
    };

};

#endif