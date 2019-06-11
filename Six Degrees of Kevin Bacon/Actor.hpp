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
        
        //        if (previous) {
        //            path = previous->getName() + " " + previous->getPath() + " " + path;
        //            Actor* _previous = new Actor(previous->getName(), previous->getPath());
        //        } else
        _previous = previous;
        _path = path;
        
        
        
    }
    ~Actor();
    Actor(const Actor& other);
    Actor& operator= (const Actor& other);
    
//    void setPath(Actor src, string name, string path)  {
//
//        cout << "temp path " << src.getPath() << " temp name " << src.getName() << endl;
//        path = src.getName() + " & " + name + " : [" + path + "]\n";
//        _path += path;
//    }
    
    void clear() {
        _name = "";
        _path = "";
        _previous = "";
        //        if (_previous)
        //            delete _previous;
        //        _previous = nullptr;
    }
    
    
    void setName(string myName);
    //    void addPath(string og, string name, string path) {
    //
    //    }
    void addConnection(string path, string prev) {
        path = " "+path;
        prev = " "+prev;
        _path += prev;
        _previous += path;
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
