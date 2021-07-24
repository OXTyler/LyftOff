//
// Created by lackt on 7/24/2021.
//
#include "Graph.h"
using namespace std;

//adds star to graph by linking it to whatever is closest, based off assumption that our sun
//is added to map to begin with
void graph::addEdge( Star* star){
    float minDist = INT_MAX;
    string closestStar;
    for(auto iter = chart.begin(); iter != chart.end(); iter++){
        if(iter->second->getDist(star) < minDist){
            minDist = iter->second->getDist(star);
            closestStar = iter->first;
        }
    }
    chart[star->id] = star;
    chart[closestStar]->neighbors.push_back(make_pair(star,minDist));
    chart[star->id]->neighbors.push_back(make_pair(chart[closestStar],minDist));
}
