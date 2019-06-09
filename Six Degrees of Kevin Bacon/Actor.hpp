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
    Actor() {}
    Actor(string whoAmI, string prevConnection) {
        _whoAmI = whoAmI;
        _prevConnection = prevConnection;
    }
    ~Actor() {}
    string getName() {return _whoAmI;}
    string getPrevConnection() {return _prevConnection;}
    void setName(string myName) {_whoAmI=myName;}
    void setPrevConnection(string prev) {_prevConnection=prev;}
    
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
