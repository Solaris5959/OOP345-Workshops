// Workshop 3 - Templates
// Created by: Jeevan Pant
// Date created: 2023/07/22

#ifndef SDDS_ORDERED_COLLECTION_H
#define SDDS_ORDERED_COLLECTION_H

namespace sdds {

	template<typename T>
	class OrderedCollection: public Collection<T,72> {
	public:
		bool operator+=(const T& obj) {
			bool success = false;
			int pos=-1;
			unsigned i;
			if (Collection<T, 72>::size() < Collection<T, 72>::capacity()) {
				Collection<T, 72>::setSmallestItem(obj);
				Collection<T, 72>::setLargestItem(obj);
				if (Collection<T, 72>::size() == 0) {
					(*this)[0] = obj;
				}
				else {
					for (i = 0; i < Collection<T, 72>::size() && pos == -1; i++) {
						if (obj < (*this)[i]) {
							pos = i;
						}
					}
					pos = pos == -1 ? i : pos;
					for (int j = Collection<T, 72>::size(); j > pos ; j--) {
						(*this)[j] = (*this)[j-1];
					}
					(*this)[pos] = obj;

				}
				Collection<T, 72>::incrSize();

				success = true;
			}
			return success;
		}
	};
	


}


#endif
