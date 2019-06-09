//
//  Actor.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Winnie Jeng on 6/6/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include <iostream>
#include <string>

using namespace std;
class Actor {
private:
    string _whoAmI;
    string _prevConnection;
    
public:
    Actor(string whoAmI="no actor found") {
        _whoAmI = whoAmI;
    }
    ~Actor() {}
    Actor(const Actor& other) {
        _whoAmI = other._whoAmI;
        _prevConnection = other._prevConnection;
    }
    Actor& operator= (const Actor& other) {
        if (this != &other)  {
            _whoAmI = other._whoAmI;
            _prevConnection = other._prevConnection;
        }
        return *this;
    }
    string getName() {return _whoAmI;}
    string getPrevConnection() {return _prevConnection;}
    void setName(string myName) {_whoAmI=myName;}
    void setPrevConnection(string prev) {_prevConnection=prev;}

    bool empty() { return (_whoAmI=="no actor found") ? (true) : (false); }
    
    friend bool operator> (const Actor& a1, const Actor& a2) {
        return a1._whoAmI > a2._whoAmI;
    }
    friend bool operator< (const Actor& a1, const Actor& a2) {
        return a1._whoAmI < a2._whoAmI;
    }
    friend bool operator>= (const Actor& a1, const Actor& a2) {
        return a1._whoAmI >= a2._whoAmI;
    }
    friend bool operator<= (const Actor& a1, const Actor& a2) {
        return a1._whoAmI <= a2._whoAmI;
    }
    
};

#endif /* Actor_hpp */
