// Workshop 3 - Templates
// Created by: Jeevan Pant
// Date created: 2023/07/22

#include "Book.h"

using namespace std;

namespace sdds{

	Book::Book():m_title{ "" }, m_numChapters{ 0 }, m_numPages{ 0 } {}
	Book::Book(const string& title, unsigned short numChapters, unsigned short numPages)
		:m_title{ title }, m_numChapters{ numChapters }, m_numPages{ numPages }{
	}
	Book::~Book() {
	}
	Book::operator bool() const { 
		return m_title.length() > 0 && m_numChapters > 0 && m_numPages > 0;
	}
	ostream& Book::print(ostream& os) const {
		if (*this) {
			string text1 = m_title + "," + to_string(m_numChapters) + ","
				+ to_string(m_numPages);
			string text2 = "(" + to_string(double(m_numPages) / m_numChapters) + ")";
			cout << setw(56) << right << text1 << " | " << setw(15) << left << text2 ;
		}
		else {
			os << "| Invalid book data"  ;

		}
		return os;
	}

	ostream& operator<<(ostream& os, const Book& bk) {
		return bk.print(os);
	}



}