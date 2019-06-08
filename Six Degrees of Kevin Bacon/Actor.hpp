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
#include <queue>
using namespace std;
class Actor {
private:
    string _name;
    bool _visited;
    string _prevConnection;
    string _movie;
    
public:
    Actor(string name="Kevin Bacon", bool visited=true, string prevConnection="", string movie="") {
        _name = name;
        _visited = true;
        _prevConnection = prevConnection;
        _movie = movie;
    }
    
    ~Actor(){}
    string getName()  {return _name;}
    bool hasVisited() {return _visited;}
    string getPrevConnection() {return _prevConnection;}
    string getMovie() {return _movie;}
    
};

#endif /* Actor_hpp */
