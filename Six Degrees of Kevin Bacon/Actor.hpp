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
    int _baconLevel;
    
public:
    Actor(string name="no actor found", string path="", string previous="");
    ~Actor();
    Actor(const Actor& other);
    Actor& operator= (const Actor& other);
    
    void clear();
    void setName(string myName);
    void addConnection(string path, string prev);
    void addBaconLevel();
    
    string getPrevious() const;
    string getPath() const;
    string getName() const;
    int getBaconLevel() const;
    bool empty();
    
    friend bool operator> (const Actor& a1, const Actor& a2);
    friend bool operator< (const Actor& a1, const Actor& a2);
    friend bool operator>= (const Actor& a1, const Actor& a2);
    friend bool operator<= (const Actor& a1, const Actor& a2);
    friend bool operator== (const Actor& a1, const Actor& a2);
    friend ostream& operator<<(ostream& os, const Actor& a);
    
};

#endif /* Actor_hpp */
