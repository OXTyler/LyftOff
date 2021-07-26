//
// Created by lackt on 7/24/2021.
//
#include "Graph.h"
using namespace std;

void graph::chartInfo() {
    cout <<chart.size()+2 << endl;
    for(auto iter = chart.begin(); iter != chart.end(); iter++){
        iter->second->printStar();
    }
}


//adds star to graph by linking it to whatever is closest, if graph empty, just adds star
void graph::addEdge(Star* star){
    string nearestID;
    if(chart.empty()){
        chart[star->id] = star;
    }
    else {

        float minDist = star->getDist(chart["0"]);
        float tempDist;
        nearestID = chart["0"]->id;
        bool cont = false;
        for (int i = 0; i < chart["0"]->neighbors.size(); i++) {
                tempDist = star->getDist(chart["0"]->neighbors[i].first);
                if (tempDist < minDist) {
                    minDist = tempDist;
                    cont = true;
                    nearestID = chart["0"]->neighbors[i].first->id;
                }
        }
        if(cont){
            nearestID = addEdgeRecursive(star, chart[nearestID]);
        }
        chart[star->id] = star;
        star->neighbors.emplace_back(chart[nearestID], star->getDist(chart[nearestID]));
        chart[nearestID]->neighbors.emplace_back(star, chart[nearestID]->getDist(star));
    }
}

string graph::addEdgeRecursive(Star* star, Star* next){
    bool cont = false;
    float tempDist;
    float minDist = star->getDist(next);
    string nearestID = next->id;
    for (int i = 0; i < next->neighbors.size(); i++) {
            tempDist = star->getDist(next->neighbors[i].first);
            if (tempDist < minDist) {
                minDist = tempDist;
                cont = true;
                nearestID = next->neighbors[i].first->id;
            }
    }
    if (cont) {
        nearestID = addEdgeRecursive(star, chart[nearestID]);
    }
    return nearestID;
}

vector<Star*> graph::Dijkstra(string srcID, string destinationID, float& distance){

    //priority queue of nodes (stars)
    priority_queue<pair<float,string>, vector<pair<float,string>>, greater<pair<float,string>>> pq;
    //vector of distances all set to INT_MAX (basically infinity)
    vector<float>dist(chart.size()+2,INT_MAX);
    vector<string>parents(chart.size()+2, "");
    pq.push(make_pair(0, srcID));
    dist[stoi(srcID)] = 0;

    while(!pq.empty()){
        pair<int, string> curr = pq.top();
        pq.pop();
        string u = curr.second;

        for(auto iter = chart[u]->neighbors.begin(); iter != chart[u]->neighbors.end(); iter++){
            Star* v  = iter->first;
            float w = iter->second;
            if(dist[stoi(v->id)] > dist[stoi(u)] + w){
                dist[stoi(v->id)] = dist[stoi(u)] + w;
                parents[stoi(v->id)] = u;
                pq.push(make_pair(dist[stoi(v->id)], v->id));
            }
        }

    }

    vector<Star*> path;
    path.push_back(chart[destinationID]);

    string tempID = parents[stoi(destinationID)];
    distance = dist[stoi(destinationID)];
    Star* tempStar = chart[tempID];

    while(parents[stoi(tempID)] != ""){
        path.push_back(tempStar);
        tempID = parents[stoi(tempID)];
        tempStar = chart[tempID];
    }
    path.push_back(tempStar);

    return path;

}