#include <iostream>
#include "Graph.h"
#include <iomanip>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
void getDataFromCSV(string filepath,graph g){
    ifstream inFile(filepath);
    if(inFile.is_open()){
        string rowTitles;
        getline(inFile,rowTitles); // top row ignored

        string sun; // line for sun info
        getline(inFile, sun);

        istringstream stream(sun);
        string starID,henryDraperID,harvardRevisedID,gliese,bayerFlamsteed,RADec,properName,distInParsecs,visualMagnitude,absMag,spectrum,colorIndex;
        string tempx,tempy,tempz,tempvx,tempvy,tempvz;
        getline(stream, starID, ',');
        getline(stream, henryDraperID, ',');
        getline(stream, harvardRevisedID, ',');
        getline(stream, gliese, ',');
        getline(stream, bayerFlamsteed, ',');
        getline(stream, RADec, ',');
        getline(stream, properName, ',');
        getline(stream, distInParsecs, ',');
        getline(stream, visualMagnitude, ',');
        getline(stream, absMag, ',');
        getline(stream, spectrum, ',');
        getline(stream, colorIndex, ',');
        getline(stream, tempx, ',');
        getline(stream, tempy, ',');
        getline(stream, tempz, ',');
        getline(stream, tempvx, ',');
        getline(stream, tempvy, ',');
        getline(stream, tempvz, ',');
        Star Sun(properName, stoi(starID), stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz)); // sun created
        Star* suntemp = &Sun;
        g.addEdge(suntemp);

        string lineFromTop;
        while(getline(inFile,lineFromTop)){
            istringstream stream(lineFromTop);

            getline(stream, starID, ',');
            getline(stream, henryDraperID, ',');
            getline(stream, harvardRevisedID, ',');
            getline(stream, gliese, ',');
            getline(stream, bayerFlamsteed, ',');
            getline(stream, RADec, ',');
            getline(stream, properName, ',');
            getline(stream, distInParsecs, ',');
            getline(stream, visualMagnitude, ',');
            getline(stream, absMag, ',');
            getline(stream, spectrum, ',');
            getline(stream, colorIndex, ',');
            getline(stream, tempx, ',');
            getline(stream, tempy, ',');
            getline(stream, tempz, ',');
            getline(stream, tempvx, ',');
            getline(stream, tempvy, ',');
            getline(stream, tempvz, ',');
            if(properName.size() == 0){
                Star s(stoi(starID), stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz));
                Star* temp1 = &s;
                g.addEdge(temp1);
            }
            else{
                Star s(properName, stoi(starID), stof(tempx), stof(tempy), stof(tempz), stof(tempvx), stof(tempvy), stof(tempvz));
                Star* temp2 = &s;
                g.addEdge(temp2);
            }


            // Add this star to the graph somehow



        }








    }




}




int main() {

    return 0;
}
