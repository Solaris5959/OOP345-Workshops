
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <list>
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
        std::string status = "General";
    };

    class CovidCollection {
        std::vector<Covid> m_collection;
    public:
        CovidCollection(const std::string& filename);
        void display(std::ostream& out, const std::string& country = "ALL") const;
        void sort(const std::string& field = "country");
        bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
        std::list<Covid> getListForDeaths(unsigned int deaths) const;
        void updateStatus();
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
    void readCovid(std::ifstream& file, std::vector<Covid>& m_collection);
    std::string trim(const std::string& str);
}

#endif // SDDS_COVIDCOLLECTION_H
