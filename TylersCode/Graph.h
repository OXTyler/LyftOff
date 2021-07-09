//
// Header file for star chart, should include star object and graph
// Will probably have 90% of the project
#include <string>
#include <math.h>
using namespace std;
struct Star{
    string name; //name determined from naming convention
    int id; //id from database
    float angle; // angle off equator
    float dist; //dist from earth (need to get units)
    int x; //cartesian coordinates
    int y;
    Star(string name, int id, float angle, float dist){
        this->name = name;
        this->id = id;
        this->angle = angle;
        this->dist = dist;
        this->x = dist * cos(angle);
        this-> y = dist * cos(angle);
    }

    int findDist(Star& next){ //returns the distance between the 2 stars
        deltaY = abs(this.y - next.y);
        deltaX = abs(this.x - next.x);
        return sqrt(deltaY^2 + deltaX^2);
    }
};

class graph{
private:
    map<int, Star> chart; //map of stars, key is the star ID,
public:
};

