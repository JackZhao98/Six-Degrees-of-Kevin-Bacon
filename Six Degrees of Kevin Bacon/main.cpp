// Six Degrees of Kevin Bacon
// Author: Miss Jeng, Mr. Zhao

#include <iostream>
#include <chrono>
#include "IMDb.hpp"
#include "path.hpp"
using namespace std;
void render();
bool traditionalMode(const IMDb& i);
bool freedomMode(const IMDb& i);
string userInput(const string& hint, const IMDb& i);
int main(int argc, const char * argv[]) {
    render();
    return 0;
}

void render() {
    IMDb database;
    auto start = chrono::high_resolution_clock::now();
    database.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration = end - start;
    cout << "\nDatabase loaded, elapsed time: "<< chrono::duration_cast<chrono::seconds>(duration).count() << "s\n\n";
    
    char select = '\0';
    while (true) {
        select = '\0';
        while (tolower(select) != 'a' && tolower(select) != 'b' && tolower(select) != 'x') {
            cout << "Choose Mode:\n [a] Traditional [b] Freedom [x] Exit\n:";
            cin >> select;
            cin.ignore(10,'\n');
        }
        switch (select) {
            case 'a':
                traditionalMode(database);
                break;
            case 'b':
                freedomMode(database);
                break;
            default:
                cout << "Thanks for playing!\n";
                return;
        }
    }
}

string userInput(const string& hint, const IMDb& i) {
    string input;
    while (true) {
        vector<string> credits;
        cout << hint << " (or press Enter to exit): ";
        getline(cin, input);
        if (input == "")
            break;
        if (i.getCredits(input, credits))
            break;
        cout << "Unable to find \"" << input << "\" in my IMDb database. Please try again." << endl;
    }
    return input;
}


bool freedomMode(const IMDb& i) {
    path p;
    vector<string> films,casts;
    cout << "Freedom Mode --->\nEnter any two actor/cast names and find their connections!\n";
    while (true) {
        string start = userInput("Start with a Cast name ", i);
        if (start == "")
            return false;
        string target = userInput("Target Cast name: ", i);
        if (target == "")
            return false;
        if (target == start) {
            cout << "Degree of 0, Nice try\n";
        }
        else {
            auto Pstart = chrono::high_resolution_clock::now();
            if (!p.buildPath(start, target, i))
                cout << "No path found between " << start << " and " << target << "\n";
            auto Pend = chrono::high_resolution_clock::now();
            auto Pduration = Pend - Pstart;
            cout << "\tTime Elapsed: (" << chrono::duration_cast<chrono::milliseconds>(Pduration).count() << "ms)\n\n";
        }
    }
    return false;
}

bool traditionalMode(const IMDb& i) {
    path p;
    vector<string> films,casts;
    cout << "Traditional Mode --->\nEnter two actor/cast names and find which person has the highest Bacon Number!\n";
    while (true) {
        string first = userInput("Actor 1 name ", i);
        if (first == "")
            return false;
        string second = userInput("Actor 2 name: ", i);
        if (second == "")
            return false;
        
        while (first == second && second != "") {
            cout << "Repeated input.\n";
            string second = userInput("Actor 2 name: ", i);
        }
        
        auto Pstart = chrono::high_resolution_clock::now();
        if (!p.buildPath(first, "Kevin Bacon", i))
            cout << "No path found between " << first << " and Kevin Bacon.\n";
        auto Pend = chrono::high_resolution_clock::now();
        auto Pduration = Pend - Pstart;
        cout << "\tTime Elapsed: (" << chrono::duration_cast<chrono::milliseconds>(Pduration).count() << "ms)\n\n";
        
        auto Pstart2 = chrono::high_resolution_clock::now();
        if (!p.buildPath(second, "Kevin Bacon", i))
            cout << "No path found between " << second << " and Kevin Bacon.\n";
        auto Pend2 = chrono::high_resolution_clock::now();
        auto Pduration2 = Pend2 - Pstart2;
        cout << "\tTime Elapsed: (" << chrono::duration_cast<chrono::milliseconds>(Pduration2).count() << "ms)\n\n";
        
    }
    return false;
}
