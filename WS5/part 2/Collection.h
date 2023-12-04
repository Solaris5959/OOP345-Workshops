#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <string>
#include <iostream>

namespace sdds {
    template<typename T>
    class Collection {
        std::string colName;
        T* items;
        int arr_size = 0;
        void (*observerFn)(const Collection<T>&, const T&);
        bool observerExists = false;

    public:
        size_t size() const {
            return arr_size;
        }

        std::string name() const {
            return colName;
        }

        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            observerFn = observer;
            observerExists = true;
        }

        Collection<T>& operator+=(const T& item) {
            bool found = false;

            if (arr_size > 0)
                for (int i = 0; i < arr_size; i++)
                    if (item.title() == items[i].title())
                        found = true;

            if (!found) {
                size_t newSize = arr_size + 1;
                T *newItemList = new T[newSize];

                if (arr_size > 0) {
                    std::copy(items, items + arr_size, newItemList);
                    delete[] items;
                }

                items = newItemList;
                items[arr_size] = item;
                arr_size = newSize;

                if (observerExists)
                    observerFn(*this, item);
            }

            return *this;
        }

        T& operator[](size_t idx) const {
            if (idx >= 0 && idx < (unsigned) arr_size)
                return items[idx];
            else
                throw std::out_of_range("Bad index [" + std::to_string(idx) +
                                        "]. Collection has [" + std::to_string(arr_size) + "] items.");
        }

        T* operator[](const std::string& title) const {
            int indexFound = -1;
            for (int i = 0; i < arr_size && indexFound == -1; i++)
                if (items[i].title() == title)
                    indexFound = i;

            if (indexFound == -1)
                return nullptr;
            else
                return &items[indexFound];
        }

        Collection(const std::string& name) {
            colName = name;
        }

        ~Collection() {
            delete[] items;
        }

        friend std::ostream& operator<<(std::ostream &os, const Collection<T> &collection) {
            for (int i = 0; i < collection.arr_size; i++)
                os << collection.items[i];
        
            return os;
        }
    };
}

#endif