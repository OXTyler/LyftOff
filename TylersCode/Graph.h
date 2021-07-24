//
// Header file for star chart, should include star object and graph
// Will probably have 90% of the project
#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iomanip>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
struct Star{
    string name = ""; //name determined from naming convention
    string id = ""; //id from database
    float x, y, z; //cartesian coordinates
    float Vx, Vy, Vz; //velocities
    //vector of conected stars with distance
    vector<pair<Star*,float>> neighbors;

    //initializes with name
    Star(string name, string id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->name = name;
        this->id = id;
        this->x = x;
        this->y = y;
        this->z = z;
        this->Vx = Vx;
        this->Vy = Vy;
        this->Vz = Vz;
    }

    //initializes with ID
    Star(string id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->id = id;
        this->x = x;
        this->y = y;
        this->z = z;
        this->Vx = Vx;
        this->Vy = Vy;
        this->Vz = Vz;
    }

    //returns distance using Pythagorean theorem
    float getDist(Star* star){
        return sqrt(pow((this->x - star->x),2.f) +
                       pow((this->y - star->y),2.f) +
                       pow((this->z - star->z),2.f));
    }

    void printStar(){
        if(name != ""){
            cout << "Name: " << name << endl;
        }
        cout << "ID: " << id << endl;
        cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl;
        cout << "Velocity: <" << Vx << ", " << Vy << ", " << Vz << ">" << endl;
        cout << "Neighbors: " << endl;
        for(int i = 0; i < neighbors.size() ; i++){
            cout << "    ID: " << neighbors[i].first->id << "    Distance: " << neighbors[i].second << endl;
        }
    }

};

class graph{
private:
    unordered_map<string, Star*> chart; //map of stars, key is the star ID,
public:
    void addEdge(Star* star);
    vector<Star*> Dijkstra(string srcID, string destination, int& dist);
    vector<Star> BFS();
    void chartInfo();
};

