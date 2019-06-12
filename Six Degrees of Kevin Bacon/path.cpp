//
//  path.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/6/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//
#include <list>
#include <set>
#include <queue>
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

bool path::buildPath(const std::string& startActor, const std::string& targetActor, const IMDb& database) {
    vector<string> moviesParticipated, castsInvolved;
    queue<path> temporaryPath;
    AVLTree<string> visitedCasts, visitedFilms;
    
    path p(startActor);
    // Initialize path with the starting actor,
    // and initialize temp path with an initial actor
    temporaryPath.push(p);
    
    // Run this loop as long as there are possible paths waited to be explored.
    while (!temporaryPath.empty()) {
        if (temporaryPath.front().getLength() > 6) {
            /* 6 is the Maximum Depth (path lengths) I want to check */
            temporaryPath.pop();
            continue;
        }
        
        path currentPath = temporaryPath.front();
        temporaryPath.pop();
        
        // Store the last known actor connected to current actor.
        string lastKnownToCurrent = currentPath.getLastKnownActor();
        
        // If lastknown is in the "checked list", then skip this loop.
        if (visitedCasts.searchAVL(lastKnownToCurrent))
            continue;
        
        // Otherwise, add this actor to the "checked list".
        visitedCasts.insert(lastKnownToCurrent);
        // Access all the movies that this actor has involved with.
        // Store the values in "moviesParticipated"
        database.getCredits(lastKnownToCurrent, moviesParticipated);
        
        for (int i = 0; i < moviesParticipated.size(); ++ i) {
            // Check every single movie in the "moviesParticipated"
            string currentMovie = moviesParticipated.at(i);
            
            // Skip this loop if the film has already been visited.
            if (visitedFilms.searchAVL(lastKnownToCurrent))
                continue;
            
            visitedFilms.insert(currentMovie);
            database.getCast(currentMovie, castsInvolved);
                
            // Now we have a list of casts involved with this movie.
            for (int j = 0; j < castsInvolved.size(); ++ j) {
                // Check every single cast in the "castsParticipated"
                string temp_player = castsInvolved.at(j);
                currentPath.addConnection(currentMovie, temp_player);
                
                if (temp_player == targetActor) {
                    cout << currentPath << endl;
                    return true;
                } else {
                    // Stores the current path into the queue.
                    temporaryPath.push(currentPath);
                    // Then remove last connected that was just made for the next actor exploration
                    currentPath.removeLastConnection();
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
    links.push_back(edge(movie,actor));
}
void path::removeLastConnection() {
    links.pop_back();
}

const std::string& path::getLastKnownActor() const {
    if (links.size())
        return links.back().actorName;
    return startActor;
}

void path::reversePath() {
    // Reverse path start with the last actor,
    // and connect previous actor with the movie of previous actor
    // Meaning that, before: A1 with edge [M1,A2] now becomes A2, [M1, A1]
    path reverse(getLastKnownActor());
    for (unsigned long int i = links.size() - 1; i >= 0; --i) {
        // Hence add connection with current movie and prev actor name.
        reverse.addConnection(links[i].movieTitle, links[i-1].actorName);
    }
    *this = reverse;
}

std::ostream& operator<<(std::ostream& out, const path& print) {
    if (print.links.size() == 0)
        return out << "[Empty path]" << std::endl;
    out << "\n\tInitial Actor: " << print.startActor << '\n';
    out << "\tTarget Actor: " << print.links[print.links.size()-1].actorName << '\n';
    out << "\tPath Length: " << print.links.size() << "\n\n" ;
    out << "\t" << print.startActor << " --> ";
    for (int i = 0; i < (int) print.links.size(); i++) {
        out << "\"" << print.links[i].movieTitle << "\" --> " << print.links[i].actorName << "." << std::endl;
        if (i + 1 == (int) print.links.size()) break;
            out << "\t" << print.links[i].actorName << " --> ";
    }
    
    return out;
}
