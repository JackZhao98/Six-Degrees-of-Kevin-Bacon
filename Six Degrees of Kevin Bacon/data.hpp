//
//  data.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef data_hpp
#define data_hpp

#include <string>
#include <vector>
#include <iostream>
#include "Actor.hpp"

using namespace std;

class data {
private:
    string fullTitle;
    vector<string> connected;
    Actor actorName; // delete?
    string path;
    
    
    
public:
    data();
    data(const string& Name);
    data(const Actor& actor) {
        actorName = actor;
    }
    ~data();
    data(const data& other);
    data& operator=(const data& other);
    
    void addConnection(const string& connectedTitle);
    
    vector<string>& getConnection() {return connected;}
    
    void addPath(string film) {
        film = " -> " + film;
        path += film;
    }

    friend
    bool operator < (const data& LHS, const data& RHS) {
        return LHS.fullTitle < RHS.fullTitle;
    }
    friend
    bool operator <= (const data& LHS, const data& RHS) {
        return LHS.fullTitle <= RHS.fullTitle;
    }
    friend
    bool operator > (const data& LHS, const data& RHS) {
        return !(LHS <= RHS);
    }
    friend
    bool operator >= (const data& LHS, const data& RHS) {
        return !(LHS < RHS);
    }
    friend
    bool operator == (const data& LHS, const data& RHS) {
        return LHS.fullTitle == RHS.fullTitle;
    }
    friend
    bool operator != (const data& LHS, const data& RHS) {
        return !(LHS == RHS);
    }
    
};


#endif /* data_hpp */
