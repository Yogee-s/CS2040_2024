#pragma once
#include <math.h>

#include <iostream>
#include "heap.h"
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
	while (index > 0) {
		int parent = (index - 1) / 2; //note this is integer division
		if (_heap[index] > _heap[parent]) {
			T temp = _heap[index];
			_heap[index] = _heap[parent];
			_heap[parent] = temp;
		}
		else
			return;
		index = parent;
	}
}

template<class T>
bool Heap<T>::isLeaf(int index)
{
	int leftChild = 2 * index + 1;
	int rightChild = 2 * index + 2;
	if (leftChild >= _n && rightChild >= _n)
		return true;
	else
		return false;
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	while (!isLeaf(index)) {
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int biggerChild;
		if (leftChild < _n && rightChild < _n) {
			biggerChild = _heap[leftChild] > _heap[rightChild] ? leftChild : rightChild;
		}
		else if (leftChild < _n) {
			biggerChild = leftChild;
		}
		else {
			biggerChild = rightChild;
		}
		
		if (_heap[biggerChild] > _heap[index]) {
			T temp = _heap[index];
			_heap[index] = _heap[biggerChild];
			_heap[biggerChild] = temp;

			index = biggerChild;
		}
		else
			return;
	}
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	_bubbleUp(_n);
	_n++;
}

template <class T>
T Heap<T>::extractMax() {
	T max = _heap[0];
	_heap[0] = _heap[_n - 1];
	_n--;
	_bubbleDown(0);
	return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
	int index = _lookFor(from);
	if (index != -1) {
		_heap[index] = to;
		_bubbleDown(index);
	}
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
	int index = _lookFor(from);
	if (index != -1) {
		_heap[index] = to; 
		_bubbleUp(index);
	}
}

template <class T>
void Heap<T>::deleteItem(T x)
{
	int index = _lookFor(x);
	if (index != -1) {
		T last = _heap[_n - 1];
		_heap[index] = last;
		_n--;

		if (last > x)
			_bubbleUp(index);
		else
			_bubbleDown(index);
	}
}


template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
