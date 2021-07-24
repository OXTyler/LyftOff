//
// Created by lackt on 7/24/2021.
//
#include "Graph.h"
using namespace std;

void graph::chartInfo() {
    cout <<chart.size() << endl;
    for(auto iter = chart.begin(); iter != chart.end(); iter++){
        iter->second->printStar();
    }
}


//adds star to graph by linking it to whatever is closest, if graph empty, just adds star
void graph::addEdge(Star* star){
    if(chart.empty()){
        chart[star->id] = star;
    }
    else {
        float minDist = INT_MAX;
        auto* closestStar = new string;
        for (auto & iter : chart) {
            if (iter.second->getDist(star) < minDist) {
                minDist = iter.second->getDist(star);
                *closestStar = iter.first;
            }
        }
        chart[star->id] = star;
        chart[*closestStar]->neighbors.emplace_back(star, minDist);
        chart[star->id]->neighbors.emplace_back(chart[*closestStar], minDist);
        delete closestStar;
    }

}



vector<Star*> graph::Dijkstra(string srcID, string destinationID, int& distance){

    //priority queue of nodes (stars)
    priority_queue<pair<float,string>, vector<pair<float,string>>, greater<pair<float,string>>> pq;
    //vector of distances all set to INT_MAX (basically infinity)
    vector<float>dist(chart.size(),INT_MAX);
    vector<string>parents(chart.size(), "");
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
    cout << "algo done" << endl;
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