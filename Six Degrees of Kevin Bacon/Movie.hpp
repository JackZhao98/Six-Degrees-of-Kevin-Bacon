//
//  Movie.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Winnie Jeng on 6/10/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef Movie_hpp
#define Movie_hpp
#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
class Movie {
    string _title;
public:
    Movie(string title="") {
        _title = title;
    }
    ~Movie() {}
    friend bool operator> (const Movie& a1, const Movie& a2) {
        return a1._title > a2._title;
    }
    friend bool operator< (const Movie& a1, const Movie& a2) {
        return a1._title < a2._title;
    }
    friend bool operator>= (const Movie& a1, const Movie& a2) {
        return a1._title >= a2._title;
    }
    friend bool operator<= (const Movie& a1, const Movie& a2) {
        return a1._title <= a2._title;
    }
    friend bool operator== (const Movie& a1, const Movie& a2) {
        return a1._title == a2._title;
    }
    friend ostream& operator<<(ostream& os, const Movie& a) {
        os<< a._title;
        return os;
    }
    
};
#endif /* Movie_hpp */
