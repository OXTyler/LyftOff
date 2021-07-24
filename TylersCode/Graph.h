//
// Header file for star chart, should include star object and graph
// Will probably have 90% of the project
#include <string>
#include <math.h>
#include <vector>
#include <map>
using namespace std;
struct Star{
    string name = ""; //name determined from naming convention
    string id; //id from database
    float dist; //dist from earth (need to get units)
    float x, y, z; //cartesian coordinates
    float Vx, Vy, Vz;
    //vector of conected stars with distance
    vector<pair<Star*,int>> neighbors;

    //initializes with name
    Star(string name, int id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->name = name;
        this->id = id;
        this->x = y;
        this->y = y;
        this->z = z;
    }

    //initializes with ID
    Star(int id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->id = id;
        this->x = y;
        this->y = y;
        this->z = z;
    }

    //returns distance using Pythagorean theorem
    float getDist(Star* star){
        return sqrt(pow((this->x - star->x),2.f) +
                       pow((this->y - star->y),2.f) +
                       pow((this->z - star->z),2.f));
    }

};

class graph{
private:
    map<string, Star*> chart; //map of stars, key is the star ID,
public:
    void addEdge(Star* star);
    vector<Star> BellmanFord(graph map, string srcID, string destination);
    vector<Star> BFS();
};

