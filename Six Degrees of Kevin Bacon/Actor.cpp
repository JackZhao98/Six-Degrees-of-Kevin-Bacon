//
//  Actor.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Winnie Jeng on 6/10/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <stdio.h>
#include "Actor.hpp"

Actor::Actor(string name, string path, string previous) {
    _name = name;
    _previous = previous;
    _path = path;
    _baconLevel = 0;
}

Actor::~Actor() {}

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

void Actor::clear() {
    _name = "";
    _path = "";
    _previous = "";
}

void Actor::addConnection(string path, string prev) {
    _path = " [" + _path + "] " + _previous +" ["+ path + "] " + prev;
    // every time addConnection() is called, bacon level increments
    addBaconLevel();
}

void Actor::setName(string myName) {_name=myName;}

void Actor::addBaconLevel() {++_baconLevel;}

string Actor::getPrevious() const {return _previous;}

string Actor::getPath() const {return _path;}

string Actor::getName() const {return _name;}

int Actor::getBaconLevel() const {return _baconLevel;}

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
    os << "Bacon number: " << a.getBaconLevel() << endl;
    os << "Path: " << a.getName() << a.getPath() << endl;
    return os;
}

