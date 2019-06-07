//
//  Actor.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Winnie Jeng on 6/6/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include "Heap/BinaryHeap.hpp"
using namespace std;
class Actor {
private:
    string _name;
    bool _visited;
    vector<pair<string,string>> friendshipPath;
    vector<string> _movies;
//    Heap<string> path;
//    string previousConnection;
    
public:
    Actor(string name) {
        _name = name;
        _visited = false;
    }
    Actor() {}
    ~Actor(){}
    void addFriends() {}
    void movieAappearances(string movie) {
        _movies.push_back(movie);
        cout << _movies.at(_movies.size()-1) << endl;
    };
    
    void buildNetwork(string actor, string movie) {
        
    }
    
};

#endif /* Actor_hpp */
