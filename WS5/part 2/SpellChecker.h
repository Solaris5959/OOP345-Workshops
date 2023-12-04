#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <string>

namespace sdds {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        int replacements[6] = {0, 0, 0, 0, 0, 0};

    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}

#endif