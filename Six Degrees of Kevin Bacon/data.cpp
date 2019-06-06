//
//  actors.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include "data.hpp"


data::data(): fullTitle("") {
}
data::data(const string& Name): fullTitle(Name) {
    
}
data::~data() {}

data::data(const data& other):fullTitle(other.fullTitle) {
    connected = other.connected;
}
data& data::operator=(const data& other) {
    if (this != &other) {
        fullTitle = other.fullTitle;
        connected = other.connected;
    }
    return *this;
}

void data::addConnection(const string& movieID) {
    connected.push_back(movieID);
}

