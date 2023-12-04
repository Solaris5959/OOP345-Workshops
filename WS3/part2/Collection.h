// Workshop 3 - Templates
// Created by: Jeevan Pant
// Date created: 2023/07/22

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

namespace sdds {

	template<typename T, unsigned C> // C-capacity
	class Collection {
		T m_items[C]{}; 
		unsigned m_cap{ C }; // capacity
		unsigned m_numItems{}; // size
		static T m_smallestItem; // smallest item across all collection instances
		static T m_largestItem; // largest item across all collection instances
	protected:
		void setSmallestItem(const T& obj); // updates m_smallestItem - Part 2 moved from private to protected
		void setLargestItem(const T& obj); // updates m_largestItem - Part 2 moved from private to protected
		T& operator[](unsigned x); // member access - Part 2 addition 
		void incrSize(); // increases m_numItems - Part 2 addition 
	public:
		unsigned size() const; // returns size
		unsigned capacity() const; // returns capacity
		bool operator+=(const T&);
		static T getSmallestItem(); // returns m_smallestItem
		static T getLargestItem(); // returns m_largestItem
		void print(std::ostream&) const; // displays data
	};

	template<typename T, unsigned C>
	T Collection<T, C>::m_smallestItem{T(9999)}; // smallest item across all the collections

	template<typename T, unsigned C>
	T Collection<T, C>::m_largestItem{T(-9999)}; // largest item across all the collections

	// class variable specialization for Book type 
	template<>
	Book Collection<Book, 10>::m_smallestItem{ Book("", 1, 10000) };

	template<>
	Book Collection<Book, 10>::m_largestItem{ Book("",10000, 1) };

	template<>
	Book Collection<Book, 72>::m_smallestItem={ Book("", 1, 10000) };

	template<>
	Book Collection<Book, 72>::m_largestItem={ Book("",10000, 1) };

	template<typename T, unsigned C>
	void  Collection<T, C>::setSmallestItem(const T& obj) {
		if (obj < m_smallestItem)
			m_smallestItem = obj;
	}

	template<typename T, unsigned C>
	void  Collection<T, C>::setLargestItem(const T& obj) {
		if (obj > m_largestItem)
			m_largestItem = obj;
	}

	template<typename T, unsigned C>
	T& Collection<T, C>::operator[](unsigned x) {
		return m_items[x];
	}

	template<typename T, unsigned C>
	void Collection<T, C>::incrSize() {
		m_numItems++;
	}

	template<typename T, unsigned C>
	unsigned Collection<T, C>::size() const {
		return m_numItems;
	}

	template<typename T, unsigned C>
	unsigned Collection<T, C>::capacity() const {
		return m_cap;
	}

	template<typename T, unsigned C> 
	bool Collection<T, C>::operator+=(const T& obj) {
		if (m_numItems < m_cap) {
			setSmallestItem(obj);
			setLargestItem(obj);
			m_items[m_numItems] = obj;
			m_numItems++;
			return true;
		}
		return false;
	}


	template<typename T, unsigned C>
	T Collection<T, C>::getSmallestItem() {
		return m_smallestItem;
	}

	template<typename T, unsigned C>
	T Collection<T, C>::getLargestItem() {
		return m_largestItem;
	}

	template<typename T, unsigned C>
	void Collection<T, C>::print(std::ostream& os) const {
		unsigned i;
		os << "[";
		for (i = 0; i < this->size()-1; i++)
			os << m_items[i] << ",";
		os << m_items[i] << "]" << std::endl;
	}

	template<>
	void Collection<Book, 10>::print(std::ostream& os) const {
		unsigned i;
		os << "| " << std::setw(75) << std::setfill('-') << "-" << "|" << std::setfill(' ') << std::endl;
		for (i = 0; i < this->size() - 1; i++)
			os << "| " << m_items[i] << " |\n";
		os << "| " << m_items[i] << " |" << std::endl;
		os << "| " << std::setw(75) << std::setfill('-') << "-" << "|" << std::setfill(' ') << std::endl;
	}
	template<>
	void Collection<Book, 72>::print(std::ostream& os) const {
		unsigned i;
		os << "| " << std::setw(75) << std::setfill('-') << "-" << "|" << std::setfill(' ') << std::endl;
		for (i = 0; i < this->size() - 1; i++)
			os << "| " << m_items[i] << " |\n";
		os << "| " << m_items[i] << " |" << std::endl;
		os << "| " << std::setw(75) << std::setfill('-') << "-" << "|" << std::setfill(' ') << std::endl;
	}

}


#endif 
