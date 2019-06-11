//
//  Actor.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Winnie Jeng on 6/10/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <stdio.h>
#include "Actor.hpp"

//Actor::Actor(string name, string path, Actor* previous){
//    _name = name;
//    if (previous) {
//        path = previous->getName() + " " + previous->getPath() + " " + path;
//        Actor* _previous = new Actor(previous->getName(), previous->getPath());
//    }
//    _path += path;
//    
//}
Actor::~Actor() {
//    clear();
}

Actor::Actor(const Actor& other) {
    _name = other._name;
    _path = other._path;
    _previous = other._previous;
}
Actor& Actor::operator= (const Actor& other) {
    if (this != &other)  {
        _name = other._name;
        _path = other._path;
        _previous = other._previous;
    }
    return *this;
}


//void Actor::setPath(string og, string name, string path) {
//    cout << "previous actor's path " <<_previous->getName() << " " << _previous->getPath() << endl;
//    path = og + " & " + name + " : [" + path + "]\n";
//    _path += path;
//}


void Actor::setName(string myName) {_name=myName;}
string Actor::getPath() const {return _path;}
string Actor::getName() const {return _name;}

bool Actor::empty() { return (_name=="no actor found") ? (true) : (false); }

bool operator> (const Actor& a1, const Actor& a2) {
    return a1._name > a2._name;
}
bool operator< (const Actor& a1, const Actor& a2) {
    return a1._name < a2._name;
}
bool operator>= (const Actor& a1, const Actor& a2) {
    return a1._name >= a2._name;
}
bool operator<= (const Actor& a1, const Actor& a2) {
    return a1._name <= a2._name;
}
bool operator== (const Actor& a1, const Actor& a2) {
    return a1._name == a2._name;
}
ostream& operator<<(ostream& os, const Actor& a) {
    os << a.getName() << a.getPath() << endl;
//    os << "a.prev " << a.getPrevious() << endl;
    
    return os;
}
