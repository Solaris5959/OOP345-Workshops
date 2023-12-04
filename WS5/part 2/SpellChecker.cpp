#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "SpellChecker.h"

namespace sdds {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream inFile;
		inFile.open(filename);

		if (inFile.is_open()) {
			std::string line;
            int i = 0;
			
			while(std::getline(inFile, line)) {
				std::stringstream ss(line);
                std::string word;

                getline(ss, word, ' ');
                m_badWords[i] = word;
                getline(ss, word, '\n');
                const auto strBegin = word.find_first_not_of(" ");
                const auto strEnd = word.find_last_not_of(" ");
                const auto strRange = strEnd - strBegin + 1;
                word = word.substr(strBegin, strRange);
                m_goodWords[i++] = word;
			}
			inFile.close();
		}
		else {
            throw std::string("Bad file name!");
		}
    }
    
    void SpellChecker::operator()(std::string& text) { // maybe works
        size_t indexOfBad;
        for (int i = 0; i < 6; i++) {
            indexOfBad = text.find(m_badWords[i]); 
            if (indexOfBad != text.npos) {
                text.replace(indexOfBad, m_badWords[i].size(), m_goodWords[i]);
                replacements[i]++;
            }
        }
    }
    
    void SpellChecker::showStatistics(std::ostream& out) const {
        out << "Spellchecker Statistics" << std::endl;

        for (int i = 0; i < 6; i++) {
            out << std::setw(15) << std::right << m_badWords[i] << ": " << replacements[i] << " replacements\n";
        }
    }
}