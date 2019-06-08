//
//  actors.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef actors_hpp
#define actors_hpp

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class data {
private:
    string fullTitle;
    vector<string> connected;
    
public:
    data();
    data(const string& Name);
    ~data();
    data(const data& other);
    data& operator=(const data& other);
    
    void addConnection(const string& connectedTitle);
    
    vector<string>& getConnection() {return connected;}

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


#endif /* actors_hpp */
