
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <iostream>
#include <string>
#include <vector>

namespace sdds {
    struct Covid {
        std::string country;
        std::string city;
        std::string variant;
        int year;
        unsigned int cases;
        unsigned int deaths;
    };

    class CovidCollection {
        std::vector<Covid> m_collection;

    public:
        CovidCollection(const std::string& filename);
        void display(std::ostream& out) const;
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
    void readCovid(std::ifstream& file, std::vector<Covid>& m_collection);
    std::string trim(const std::string& str);
}

#endif // SDDS_COVIDCOLLECTION_H
