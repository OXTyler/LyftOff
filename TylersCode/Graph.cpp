//
// Created by lackt on 7/24/2021.
//
#include "Graph.h"
using namespace std;


//outputs all info of all stars
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
        //start of trying to find closest star to connect new star
        //does so in a greedy fashion
        float minDist = star->getDist(chart["0"]);
        float tempDist;
        nearestID = chart["0"]->id;
        bool cont = false;
        //checks all neighbors of sun (node 0) to see if one is
        //closer to new star than sun
        for (int i = 0; i < chart["0"]->neighbors.size(); i++) {

                tempDist = star->getDist(chart["0"]->neighbors[i].first);
                //if a neighbor is closer than previous closest, will mark
                if (tempDist < minDist) {
                    minDist = tempDist;
                    cont = true;
                    nearestID = chart["0"]->neighbors[i].first->id;
                }
        }
        //if continue is needed, will recursively continue from the
        //closest neighbor of the parent (in this function sun)
        if(cont){
            nearestID = addEdgeRecursive(star, chart[nearestID]);
        }

        //once that is done, connects new star to (greedy) closest star
        chart[star->id] = star;
        star->neighbors.emplace_back(chart[nearestID], star->getDist(chart[nearestID]));
        chart[nearestID]->neighbors.emplace_back(star, chart[nearestID]->getDist(star));
    }
}

//recursive function used to find the closest star to connect new star
//takes a greedy approach, so not necessarily the actual closest
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

//uses dijkstras algo to find shortest path from one star to another (given a greedily created graph)
vector<Star*> graph::Dijkstra(string srcID, string destinationID, float& distance){

    //priority queue of nodes (stars) implemented as a min heap
    priority_queue<pair<float,string>, vector<pair<float,string>>, greater<pair<float,string>>> pq;

    //vector of distances all set to INT_MAX (basically infinity)
    vector<float>dist(chart.size()+2,INT_MAX);

    //vector of the previous node, ie value of parents [9] is the node that comes before 9 on the path
    vector<string>parents(chart.size()+2, "");

    //push the starting node into priority queue with distance from itself = 0
    pq.push(make_pair(0, srcID));

    //distance = 0 at src id, used for finding sum of distances later
    dist[stoi(srcID)] = 0;

    //priority queue will be empty when all nodes are visited
    while(!pq.empty()){

        //the node currently being worked on is from top of queue
        pair<int, string> curr = pq.top();
        pq.pop();

        //id of that node
        string u = curr.second;

        //iterates through the neighbors of that node
        for(auto iter = chart[u]->neighbors.begin(); iter != chart[u]->neighbors.end(); iter++){
            //the star that is the neighbor
            Star* v  = iter->first;
            //distance from the node being worked on
            float w = iter->second;

            //if current distance(for first pass is INT_MAX) is greater than the distance
            //to node being worked on, plus the distance from that node to neighbor
            if(dist[stoi(v->id)] > dist[stoi(u)] + w){

                //make distance from source to nieghbor = distance from node being worked on
                //plus distance to neighbor
                dist[stoi(v->id)] = dist[stoi(u)] + w;

                //parent of neighbor is the node being worked on
                parents[stoi(v->id)] = u;

                //push the id of neighbor into priority queue paired with distance from source
                pq.push(make_pair(dist[stoi(v->id)], v->id));
            }
        }

    }

    //path from destination to source (its backwards)
    vector<Star*> path;

    //start with destination
    path.push_back(chart[destinationID]);

    //used to iterate through parents to get path
    string tempID = parents[stoi(destinationID)];

    //distance from source to destination, saved by being passed in by reference
    distance = dist[stoi(destinationID)];

    //temp star for iterating, starts at the parent of the destination
    Star* tempStar = chart[tempID];


    //because of parent vector being initialized with value "", as long as the value
    //isnt that, it has a parent
    while(parents[stoi(tempID)] != ""){
        //push iterating star into path
        path.push_back(tempStar);
        //set the temp id to the parent id of iterating star
        tempID = parents[stoi(tempID)];
        //set iterating star as that parent using the graph
        tempStar = chart[tempID];
    }

    //last tempStar will be the source node, pushes back here
    path.push_back(tempStar);

    return path;

}

//modified bfs, essentially works as an unweighted dijkstra's algo
//will be similar to Dijkstra due to greedy approach of graph construction
vector<Star*> graph::BFS(string sourceID, string destID) {
    vector<Star*> path;
    vector<string> parents(chart.size()+2, "");
    vector<bool> visited(chart.size()+2, false);
    queue<Star*> nodes;
    Star* src = chart[sourceID];
    nodes.push(src);
    visited[stoi(sourceID)] = true;
    Star* temp;
    while(!nodes.empty()){
        temp = nodes.front();
        nodes.pop();
        for(auto iter = chart[temp->id]->neighbors.begin(); iter != chart[temp->id]->neighbors.end(); iter++){
            if(!visited[stoi(iter->first->id)]){
                nodes.push(iter->first);
                visited[stoi(iter->first->id)] = true;
                parents[stoi(iter->first->id)] = temp->id;
            }
        }
    }
    Star* tempNode = chart[destID];
    while(parents[stoi(tempNode->id)] != ""){
        path.push_back(tempNode);
        tempNode = chart[parents[stoi(tempNode->id)]];
    }
    path.push_back(tempNode);
    return path;
}