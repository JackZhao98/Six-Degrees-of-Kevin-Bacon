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
    string _name;
    string _path;
    string _previous;
    
public:
    Actor(string name="no actor found", string path="", string previous="") {
        _name = name;
        _previous = previous;
        _path = path;
        
        
        
    }
    ~Actor();
    Actor(const Actor& other);
    Actor& operator= (const Actor& other);
    
    void clear() {
        _name = "";
        _path = "";
        _previous = "";
    }
    
    
    void setName(string myName);

    void addConnection(string path, string prev) {
        _path = " [" + _path + "] " + _previous +" ["+ path + "] " + prev;
    }
    
    
    string getPrevious() const {return _previous;}
    string getPath() const;
    string getName() const;
    
    bool empty();
    
    friend bool operator> (const Actor& a1, const Actor& a2);
    friend bool operator< (const Actor& a1, const Actor& a2);
    friend bool operator>= (const Actor& a1, const Actor& a2);
    friend bool operator<= (const Actor& a1, const Actor& a2);
    friend bool operator== (const Actor& a1, const Actor& a2);
    friend ostream& operator<<(ostream& os, const Actor& a);
    
};

#endif /* Actor_hpp */
