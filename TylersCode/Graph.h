#include <string>
#include <cmath>
#include <utility>
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
    //vector of connected stars with distance
    vector<pair<Star*,float>> neighbors;

    //initializes with name
    Star(string name, string id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->name = std::move(name);
        this->id = std::move(id);
        this->x = x;
        this->y = y;
        this->z = z;
        this->Vx = Vx;
        this->Vy = Vy;
        this->Vz = Vz;
    }

    //initializes with ID
    Star(string id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->id = std::move(id);
        this->x = x;
        this->y = y;
        this->z = z;
        this->Vx = Vx;
        this->Vy = Vy;
        this->Vz = Vz;
    }

    //returns distance using Pythagorean theorem
    float getDist(Star* star) const{
        return sqrt(pow((this->x - star->x),2.f) +
                       pow((this->y - star->y),2.f) +
                       pow((this->z - star->z),2.f));
    }

    void printStar(){
        if(!name.empty()){
            cout << "Name: " << name << endl;
        }
        cout << "ID: " << id << endl;
        cout << "Position: (" << x << ", " << y << ", " << z << ")" << endl;
        cout << "Velocity: <" << Vx << ", " << Vy << ", " << Vz << ">" << endl;
        cout << "Neighbors: " << endl;
        for(auto & neighbor : neighbors){
            cout << "    ID: " << neighbor.first->id << "    Distance: " << neighbor.second << endl;
        }
    }

};

class graph{

public:
    unordered_map<string, Star*> chart; //map of stars, key is the star ID,
    void addEdge(Star* star);
    string addEdgeRecursive(Star* star, Star* next);
    vector<Star*> Dijkstra(string srcID, string destination, float& dist);
    void chartInfo();
    vector<Star*> BFS(string sourceID, string destID);
};

