//
//  heapFxns.hpp
//  Heap
//
//  Created by Winnie Jeng on 5/14/19.
//  Copyright © 2019 Winnie Jeng. All rights reserved.
//

#ifndef heapFxns_hpp
#define heapFxns_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class heapFxns {
    
public:
    heapFxns() {}
    ~heapFxns() {}
    heapFxns(const heapFxns& other) {}
    //    heapFxns operator=(const heapFxns& other);
    
    void insert(vector<T>& v, T data);
    void shuffleUp(vector<T>& v, unsigned long int currentIndex);
    T remove(vector<T>& v);  // remove the first element of the tree
    void shuffleDown(vector<T>& v, unsigned long int currentIndex = 1); // call in remove
    void print(vector<T>& v);
};

template <typename T>
void heapFxns<T>::insert(vector<T>& v, T data) {
    v.push_back(data);
    unsigned long int currentIndex = v.size()-1;
    shuffleUp(v, currentIndex);
}

template <typename T>
void heapFxns<T>::shuffleUp(vector<T>& v, unsigned long int currentIndex) {
    if (currentIndex <= 1 || v.at(currentIndex) < v.at(currentIndex/2))
        return ;
    std::swap(v.at(currentIndex), v.at(currentIndex/2));
    shuffleUp(v, currentIndex/2);
}

template <typename T>
T heapFxns<T>::remove(vector<T>& v) {
    if (v.size() == 1) {
        std::cout << "Cannot remove the last item\n";
        return v.at(1);
    }
    T hold = v.at(1);
    v.at(1) = v.at(v.size()-1);
    v.pop_back();
    shuffleDown(v);
    return hold;
}

template <typename T>
void heapFxns<T>::shuffleDown(vector<T>& v, unsigned long int currentIndex) {
    if (currentIndex*2+1 == v.size() && v.at(currentIndex) < v.at(currentIndex*2)) {
        std::swap(v.at(currentIndex), v.at(currentIndex*2));
        return ;
    }
    if (currentIndex*2+1 >= v.size())  //
        return ;
    if (v.at(currentIndex) > v.at(currentIndex*2) && v.at(currentIndex) > v.at(currentIndex*2+1))
        return ;
    if (v.at(currentIndex*2) > v.at(currentIndex*2+1)) {
        swap(v.at(currentIndex), v.at(currentIndex*2));
        shuffleDown(v, currentIndex*2);
    }
    else {
        swap(v.at(currentIndex), v.at(currentIndex*2+1));
        shuffleDown(v, currentIndex*2+1);
    }
}

template <typename T>
void heapFxns<T>::print(vector<T>& v) {
    for (int i = 1; i < v.size(); ++i)
        std::cout << v.at(i) << " ";
    std::cout << std::endl;
}

#endif /* heapFxns_hpp */
