//
// Header file for star chart, should include star object and graph
// Will probably have 90% of the project
#include <string>
#include <math.h>
using namespace std;
struct Star{
    string name = ""; //name determined from naming convention
    int id; //id from database
    float dist; //dist from earth (need to get units)
    float x, y, z; //cartesian coordinates
    float Vx, Vy, Vz;

    Star(string name, int id, float x, float y, float z, float Vx, float Vy, float Vz){
        this->name = name;
        this->id = id;
        this->x = y;
        this->y = y;
        this->z = z;
    }
    Star(int id, float x, float y, float z){
        this->id = id;
        this->x = y;
        this->y = y;
        this->z = z;
    }

    int getDist(Star* star){
        return sqrt((this->x - star->x)^2 + (this->y - star->y)^2 + (this->z - star->z)^2);
    }

};

class graph{
private:
    map<int, Star> chart; //map of stars, key is the star ID,
public:
};