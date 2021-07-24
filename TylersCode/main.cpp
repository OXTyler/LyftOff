#include <iostream>
#include "Graph.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
void getDataFromCSV(string filepath,graph& g){
    ifstream inFile(filepath);
    if(inFile.is_open()){
        string rowTitles;
        getline(inFile,rowTitles); // top row ignored
        string sun; // line for sun info
        getline(inFile, sun);

        istringstream stream(sun);
        string starID, properName;
        string tempx, tempy, tempz, tempvx, tempvy, tempvz, junk;
        getline(stream, starID, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, properName, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, tempx, ',');
        getline(stream, tempy, ',');
        getline(stream, tempz, ',');
        getline(stream, tempvx, ',');
        getline(stream, tempvy, ',');
        getline(stream, tempvz, ',');

        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
        getline(stream, junk, ',');
         // sun created
        Star* suntemp = new Star(properName, starID, stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz));
        g.addEdge(suntemp);

        string lineFromTop;
        while(getline(inFile,lineFromTop)){
            istringstream stream(lineFromTop);

            getline(stream, starID, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, properName, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, tempx, ',');
            getline(stream, tempy, ',');
            getline(stream, tempz, ',');
            getline(stream, tempvx, ',');
            getline(stream, tempvy, ',');
            getline(stream, tempvz, ',');

            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            getline(stream, junk, ',');
            if(properName.size() == 0){

                Star* temp1 = new Star(starID, stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz));
                g.addEdge(temp1);
            }
            else{

                Star* temp1 = new Star(properName, starID, stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz));
                g.addEdge(temp1);
            }





        }
        inFile.close();

    }


}




int main() {
    string filePath = "C:/Users/lackt/Documents/UF/Summer 2021/Data Structures COP 3530/Project 3/LyftOff/TylersCode/testData.txt";
    graph starGraph;
    auto start = high_resolution_clock::now();
    getDataFromCSV(filePath, starGraph);
    auto stop = high_resolution_clock::now();
 /*   int dist = 0;

   vector<Star*> path = starGraph.Dijkstra("0", "5", dist);

    for(int i = 0; i < path.size(); i++){
        cout << "Star ID: "<< path[i]->id << endl;
    }
    cout <<"Distance: " << dist << endl;
    cout <<"\n\n" << endl;



    */
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "time: " << duration.count() << "microseconds"<< endl;
    return 0;
}
