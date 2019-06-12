//
//  path.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/6/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//
#include <list>
#include <set>
#include "path.hpp"
using namespace std;
path::path(const std::string& _startActor):startActor(_startActor) {}

path::~path() {
    startActor = "";
    links.clear();
}

path::path(const path& other) {
    startActor = other.startActor;
    links = other.links;
}

path& path::operator=(const path& other) {
    if (this != &other) {
        startActor = other.startActor;
        links = other.links;
    }
    return *this;
}

bool path::buildPath(const std::string& startActor, const std::string& targetActor, IMDb& database) {
    
    list<path> temporaryPath;
    set<string> visitedCasts;
    set<string> visitedFilms;
    
    path buildpath(startActor);
    temporaryPath.push_back(buildpath);
    
    while (!temporaryPath.empty() && temporaryPath.front().getLength() <= 6) {
        path front = temporaryPath.front();
        temporaryPath.pop_front();
        
        string player = front.getLastActor();
        if (visitedCasts.find(player) == visitedCasts.end()) {
            visitedCasts.insert(player);
            vector<string> credits;
            database.getCredits(player, credits);
            
            for (int i=0; i<credits.size(); i++) {
                string movie = credits[i];
                if (visitedFilms.find(movie) == visitedFilms.end()) {
                    visitedFilms.insert(movie);
                    
                    vector<string> players;
                    database.getCast(movie, players);
                    
                    for (int j=0; j<players.size(); j++) {
                        string temp_player = players[j];
                        front.addConnection(movie, temp_player);
                        if (temp_player == targetActor) {
                            cout<<front<<endl;
                            return true;
                        }else{
                            temporaryPath.push_back(front);
                            front.removeLastConnection();
                        }
                    }
                }
            }
        }
    }
    
    return false;
}

int path::getLength() const {
    return static_cast<int>(links.size());
}
void path::addConnection(const std::string& movie, const std::string& actor) {
    links.push_back(link(movie,actor));
}
void path::removeLastConnection() {
    links.pop_back();
}

const std::string& path::getLastActor() const {
    if (links.size())
        return links.back().actorName;
    return startActor;
}

void path::reversePath() {
    path reverse(getLastActor());
    for (unsigned long int i = links.size() - 1; i > 0; --i) {
        reverse.addConnection(links[i].movieTitle, links[i-1].actorName);
    }
    if (links.size() > 0)
        reverse.addConnection(links[0].movieTitle, startActor);
    *this = reverse;
}

std::ostream& operator<<(std::ostream& out, const path& print) {
    if (print.links.size() == 0)
        return out << "[Empty path]" << std::endl;
    out << "\n\tStarting Actor: " << print.startActor << '\n';
    out << "\tTarget Actor: " << print.links[print.links.size()-1].actorName << '\n';
    out << "\tPath Length: " << print.links.size() << "\n\n" ;
    out << "\t" << print.startActor << " participated in ";
    for (int i = 0; i < (int) print.links.size(); i++) {
        out << "\"" << print.links[i].movieTitle << "\" with " << print.links[i].actorName << "." << std::endl;
        if (i + 1 == (int) print.links.size()) break;
            out << "\t" << print.links[i].actorName << " participated in ";
    }
    
    return out;
}
