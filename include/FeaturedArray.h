#ifndef FEATUREDARRAY_H
#define FEATUREDARRAY_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <string>
using namespace std;

template<typename T>
class FeaturedArray {
private:
    T* data;
    size_t size;
    size_t capacity;

    int search(const T& val);
    void reSize();
public:
    FeaturedArray();
    ~FeaturedArray();

    bool sortedInsert(const T& val);
    bool Delete(const T& val);
    T* searchData(const T& val);

    T& operator[](size_t index) const;
    FeaturedArray<T>& operator=(const FeaturedArray<T>& other);

    void deleteExceptFirst();

    bool isFull() const;
    size_t getSize() const;
    bool isEmpty() const;

};
//CONSTRUCTOR & DESTRUCTOR ----------------------------------------------------
template<typename T>
FeaturedArray<T>::FeaturedArray() : size(0), capacity(2) {
    data = new T[capacity];
}
template<typename T>
FeaturedArray<T>::~FeaturedArray() {
    delete[] data;
}
//INSERT , DELETE & SEARCH ----------------------------------------------------
template<typename T>
bool FeaturedArray<T>::sortedInsert(const T& val) {
    int result = search(val);
    if (result == -1) {
        if (isFull())
            reSize();
        for (size_t i = 0; i < size; i++) {
            if (data[i] > val) {
                for (size_t j = size; j > i; j--)
                    data[j] = data[j - 1];
                data[i] = val;
                size++;
                return true;
            }
        }
        data[size++] = val;
        return true;
    }
    return false;
}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
bool FeaturedArray<T>::Delete(const T& val) {
    int index = search(val);
    if (index != -1) {
        for (int i = index; i < static_cast<int>(size) - 1; i++)
            data[i] = data[i + 1];
        size--;
        if (capacity > size * 3)
            reSize();
        return true;
    }
    return false;
}//>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
T* FeaturedArray<T>::searchData(const T& val)
{
    if (isEmpty())
        return nullptr;
    int mid, left = 0, right = static_cast<int>(size) - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (data[mid] == val)
            return &(data[mid]);
        else if (data[mid] > val)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return nullptr;
}
//OPERATOR OVERLOADING---------------------------------------------------------
template<typename T>
T& FeaturedArray<T>::operator[](size_t index) const {
    if (!(index >= 0 && index < size))
        throw std::out_of_range("Out Of Range Index :( ");
    return data[index];
}
template<typename T>
FeaturedArray<T>& FeaturedArray<T>::operator=(const FeaturedArray<T>& other) {
    if (this != &other) {
        delete[] this->data;
        this->capacity = other.capacity;
        this->size = other.size;
        this->data = new T[other.capacity];
        for (size_t i = 0; i < other.size; i++)
            this->data[i] = other.data[i];
    }
    return *this;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<typename T>
bool FeaturedArray<T>::isFull() const {
    return size == capacity;
}
template<typename T>
size_t FeaturedArray<T>::getSize() const {
    return size;
}
template<typename T>
bool FeaturedArray<T>::isEmpty() const {
    return size == 0;
}
template<typename T>
void FeaturedArray<T>::deleteExceptFirst() {
    size = 1;
    reSize();
}
//PRIVATE MEMBERS--------------------------------------------------------------
template<typename T>
int FeaturedArray<T>::search(const T& val) {
    if (isEmpty())
        return -1;
    int mid, left = 0, right = static_cast<int>(size) - 1;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (data[mid] == val)
            return mid;
        else if (data[mid] > val)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
//DEEP RESIZING----------------------------------------------------------------
template<typename T>
void FeaturedArray<T>::reSize() {
    const size_t mini = 2;
    size_t newCapacity = max( (size * 2) , mini );
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size; i++)
        newData[i] = data[i];
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

#endif // FEATUREDARRAY_H
