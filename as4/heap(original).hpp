#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

#define DEFAULTHEAPSIZE 1023

template <class T>
class Heap {
protected:
    T* _heap;
    int _size;

public:
    /*Heap() { _heap = new T[DEFAULTHEAPSIZE]; }*/
    Heap() { _heap = new T[DEFAULTHEAPSIZE]; _size = 0; }

    int size() const {
        // TODO: implement this
        return _size;
    }

    bool empty() const {
        // TODO: implement this
        if (size() == 0) {
            return true;
        }
        return false;
    }
    void insert(const T&);
    T extractMax();
    T peekMax() const;
    void printHeapArray() const;
    void printTree() const;
    void changeKey(const T& from, const T& to);
    void deleteItem(const T&);

    //helper functions
    int item_index(const T& item);
    void bubble_up(const T& item);
    void bubble_down(const T& item);
    void swapitem(const T& from, const T& to);
    int bigger_child(const int& item);

    ~Heap() { delete[] _heap; };
};

//Helper functions

//Return index of item
template<class T>
int Heap<T>::item_index(const T& item) {
    if (empty()) {
        throw std::out_of_range("Heap is empty!");
    }
    for (int index = 0; index < size(); index++) {
        if (_heap[index] == item) {
            return index;
        }
    }
    throw std::out_of_range("Item not inside heap!");
}

//Return bigger child index if have
template <class T>
int Heap<T>::bigger_child(const int& index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    // No children
    if (left_child >= _size && right_child >= _size) {
        return index;
    }
    // Only left child exists
    else if (right_child >= _size) {
        return (left_child < _size && _heap[left_child] > _heap[index]) ? left_child : index;
    }
    // Both children exist
    else {
        return (_heap[left_child] > _heap[right_child]) ? left_child : right_child;
    }
}


//bubble up item
template <class T>
void Heap<T>::bubble_up(const T& item) {
    int index = item_index(item);
    int parent_index = std::floor((index - 1) / 2);
    while (_heap[index] > _heap[parent_index]) {
        swapitem(_heap[parent_index], item);
        index = parent_index;
        parent_index = std::floor((index - 1) / 2);
    }
}

//bubble down item
template <class T>
void Heap<T>::bubble_down(const T& item) {
    int index = item_index(item);
    int bigger_child_index = bigger_child(index);

    while (_heap[bigger_child_index] > _heap[index]) {
        swapitem(_heap[bigger_child_index], item);
        index = bigger_child_index;
        bigger_child_index = bigger_child(index);
    }
}


//swap item
template <class T>
void Heap<T>::swapitem(const T& from, const T& to) {
    int from_index = item_index(from);
    int to_index = item_index(to);
    _heap[to_index] = from;
    _heap[from_index] = to;
}

template <class T>
void Heap<T>::insert(const T& item) {
    // TODO: implement this
    _heap[size()] = item;
    _size += 1;
    bubble_up(item);
}

template <class T>
T Heap<T>::extractMax() {
    // TODO: implement this
    //throw std::runtime_error("Not implemented");
    T max = (_heap)[0];
    T last = (_heap[_size - 1]);
    if (empty()) {
        throw std::out_of_range("Heap is empty!");
    }
    else if (size() == 1) {
        /*_heap[0] = NULL;*/
        _size -= 1;
        return max;
    }
    swapitem(max, last);
    /* (_heap)[_size-1] = NULL;*/
    _size -= 1;
    bubble_down(last);
    return max;
}

template <class T>
T Heap<T>::peekMax() const {
    // TODO: What happens if the heap is empty?
    if (empty()) {
        throw std::out_of_range("Heap is empty!");
    }
    return _heap[0];
};

template <class T>
void Heap<T>::printHeapArray() const {
    for (int i = 0; i < size(); i++) {
        cout << _heap[i] << " ";
    }
    cout << endl;
}

template <class T>
void Heap<T>::changeKey(const T& from, const T& to) {
    // TODO: implement this
    if (empty()) {
        throw std::out_of_range("Key not inside!");
    }
    for (int index = 0; index < size(); index++) {
        if (_heap[index] == from) {
            _heap[index] = to;
            int parent_index = std::floor((index - 1) / 2);
            int bigger_child_index = bigger_child(index);
            if (to > _heap[parent_index]) {
                bubble_up(to);
            }
            else if (to < _heap[bigger_child_index]) {
                bubble_down(to);
            }
            return;
        }
    }
    throw std::out_of_range("Key not inside!");
}

template <class T>
void Heap<T>::deleteItem(const T& x) {
    // TODO: implement this
    T last = _heap[_size - 1];
    swapitem(x, last);
    _size -= 1;
    if (x != last) {
        bubble_down(last);
    }
}

template <class T>
void Heap<T>::printTree() const {
    int parity = 0;
    if (size() == 0) return;
    int space = pow(2, 1 + (int)log2f(size())), i;
    int nLevel = (int)log2f(size()) + 1;
    int index = 0, endIndex;
    int tempIndex;

    for (int l = 0; l < nLevel; l++) {
        index = 1;
        parity = 0;
        for (i = 0; i < l; i++) index *= 2;
        endIndex = index * 2 - 1;
        index--;
        tempIndex = index;
        while (index < size() && index < endIndex) {
            for (i = 0; i < space - 1; i++) cout << " ";
            if (index == 0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++) cout << " ";
            index++;
        }
        cout << endl;
        index = tempIndex;
        while (index < size() && index < endIndex) {
            for (i = 0; i < (space - 1 - ((int)log10(_heap[index]))); i++)
                cout << " ";
            cout << _heap[index];
            for (i = 0; i < space; i++) cout << " ";
            index++;
        }

        cout << endl;
        space /= 2;
    }
}

#endif
