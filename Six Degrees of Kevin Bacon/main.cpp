//
//  main.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <iostream>       // std::cout
#include <stack>
#include <chrono>
#include "IMDb.hpp"
#include "Heap/BinaryHeap.hpp"
#include <queue>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    IMDb imdb;
    vector<string> films, casts;
    
    auto start = chrono::high_resolution_clock::now();
    imdb.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration=end-start;

//    imdb.getCredits("George Cukor", films);
//    imdb.getCast("Gone with the Wind", casts);
//    for (int i = 0; i < films.size(); ++ i) {
//        cout << films[i] << "\n";
//    }
//    for (int i = 0; i < casts.size(); ++ i) {
//        cout << casts[i] << "\n";
//    }
//
    //how is Person 1 related to Person 2
    string person1 = "Kevin Bacon";
    stack<string> s;
    queue<string> q;
    imdb.getCredits(person1, films);
    
    for (int i = 0; i < films.size(); ++i) {
        s.push(films[i]);
        imdb.getCast(s.top(), casts);
    }
    
    while (!s.empty()) {
        imdb.getCast(s.top(), casts);
        for (int i = 0; i < casts.size(); ++i) {
            q.push(casts[i]);
        }
        s.pop();
    }
    cout  <<  endl;
    cout << q.size() << endl;

//    for (int i = 0; i < casts.size(); ++i)  {
//        cout  << " " << casts[i] <<  endl;
//    }
    
    while (!q.empty()) {
        cout << q.front()  << endl;
        q.pop();
    }
    // 1. go down the list of all of person 1's movies
    // 2. search from the movies all the actors associated with that movie
    //          - start from the actor from the first visited movie
    //          - add the actor into the queue if he is not visited
    //          - set the actor's visited boolean to true and personConnectedTo to Person 1
    //          -
    
    

    return 0;
}
