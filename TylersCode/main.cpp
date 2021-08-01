#include <iostream>
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <GL/freeglut.h>

using namespace std;

//globals needed to make openGL work
//openGL isn't great, so things like this needed
bool run = false;
graph starGraph;
vector<Star*> DijkstraPath;
vector<Star*> BFSPath;



//used to parse csv file
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

//sets the points of all stars in the chart
void points(unordered_map<string, Star*> chart){


    //creates 3d vertex points of all the stars
    for(auto iter = chart.begin(); iter != chart.end(); iter++) {
        float x = iter->second->x;
        float y = iter->second->y;
        float z = iter->second->z;
        //this begins the render of a point
        glBegin(GL_POINTS);
        glEnable(GL_POINT_SIZE);
        glPointSize(5);
        glVertex3f(x, y, z);
        glEnd(); //end of a render
    }

}
//this creates a path using a vector of stars
void points(vector<Star*> stars){
    //sets line width
    glLineWidth(1);
    //sets point size
    glPointSize(8);
    //to create a line, you need 2 points
    //so this gets them from a star and the next
    //in vector
    for(int i = 0; i < stars.size() - 1; i++) {
        float x = stars[i]->x;
        float y = stars[i]->y;
        float z = stars[i]->z;
        float x2 = stars[i+1]->x;
        float y2 = stars[i+1]->y;
        float z2 = stars[i+1]->z;
        glBegin(GL_LINES);
        glColor3d(200, 0, 200);
        glVertex3f(x, y, z);
        glVertex3f(x2, y2, z2);
        glEnd();
        //creates points at every star in the path
        glBegin(GL_POINTS);
        glEnable(GL_POINT_SIZE);
        glColor3d(30, 150, 255); //these colors hardly work as intended btw
        glVertex3f(x, y, z);
        glVertex3f(x2, y2, z2);
        glEnd();

    }
}

//hey now, you're an          (Function to display all stars)
void allStar() {
    //OpenGL isnt great so to only render once, used a global boolean to determine if it needs to render again
    if(!run) {
        glOrtho(-1000, 1000, -1000, 1000, -10000, 10000);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        points(starGraph.chart);
        glFlush();
        glutSwapBuffers();
        run = true;
    }
}

void DijkstraLine(){
    if(!run) {
        //finds largest and smallest x and y to set scale of window
        int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
        for (int i = 0; i < DijkstraPath.size(); i++) {
            if (DijkstraPath[i]->x > maxx) maxx = DijkstraPath[i]->x;
            if (DijkstraPath[i]->y > maxy) maxy = DijkstraPath[i]->y;
            if (DijkstraPath[i]->x < minx) minx = DijkstraPath[i]->x;
            if (DijkstraPath[i]->x < miny) miny = DijkstraPath[i]->y;
        }
        //sets scale of window grid, adds buffer for better view
        glOrtho(minx - 10, maxx + 10, miny - 10, maxy + 10, -10000, 10000);
        //clears the window before render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //sets all star points, then overlays path
        points(starGraph.chart);
        points(DijkstraPath);
        glFlush();
        glutSwapBuffers();
        run = true;
    }
}

void BFSLINE(){
    if(!run) {
        int minx = INT_MAX, miny = INT_MAX, maxx = INT_MIN, maxy = INT_MIN;
        for (int i = 0; i < BFSPath.size(); i++) {
            if (BFSPath[i]->x > maxx) maxx = BFSPath[i]->x;
            if (BFSPath[i]->y > maxy) maxy = BFSPath[i]->y;
            if (BFSPath[i]->x < minx) minx = BFSPath[i]->x;
            if (BFSPath[i]->x < miny) miny = BFSPath[i]->y;
        }
        //sets scale of window grid, adds buffer for better view
        glOrtho(minx - 10, maxx + 10, miny - 10, maxy + 10, -10000, 10000);
        //clears the window before render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //sets all star points, then overlays path
        points(starGraph.chart);
        points(BFSPath);
        glFlush();
        glutSwapBuffers();
        run = true;
    }
}


void Dijkstra(string src, string dest){
    auto start = high_resolution_clock::now();
    float dist = 0;
    DijkstraPath = starGraph.Dijkstra(src, dest, dist);
    cout << "Dijkstra:" << endl;
    //prints out data of the stars on the path
    for(int i = 0; i < DijkstraPath.size(); i++){
        cout << "Star ID: "<< DijkstraPath[i]->id << endl;
    }
    cout <<"Distance: " << dist << endl;
    cout <<"\n\n" << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //time it takes to run the operation
    cout << "time: " << duration.count() << "microseconds"<< endl;
    cout <<"\n\n" << endl;
}

void BFS(string src, string dest){
    auto start = high_resolution_clock::now();
    BFSPath = starGraph.BFS(src, dest);
    cout << "BFS:" << endl;
    //prints out data of the stars on the path
    for(int i = 0; i < BFSPath.size(); i++){
        cout << "Star ID: "<< BFSPath[i]->id << endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //time it takes to run the operation
    cout << "time: " << duration.count() << "microseconds"<< endl;
    cout <<"\n\n" << endl;

}

int inputOutput(){

    cout << "Our star directory is stored by integer values from 0 to 119,615" << endl;
        int choice;
        cout << "Menu Options:" << endl;
        cout << "1. Print All Named Stars" << endl;
        cout << "2. Find Distance Between Two Stars" << endl;
        cout << "3. Exit" <<endl;
        cin >> choice;

        if(choice == 1){
            // function call to print all named stars
            starGraph.chartInfo();
            return 0;
        }

        if(choice == 2){
            int option = 0;
            cout << "1. Dijkstra's Algorithm Traversal" << endl;
            cout << "2. BFS" << endl;
            cin >> option;
            cout << "Enter source star ID" << endl;
            string sourceID;
            cin >> sourceID;
            cout << "Enter destination star ID" << endl;
            string destID;
            cin >> destID;

            if(option == 1){
                Dijkstra(sourceID, destID);
                return 1;
            }
            if(option == 2){
                BFS(sourceID, destID);
                return 2;
            }

        }
        if(choice == 3){
            return -1;
        }
    else{
        return -1;
    }

}

//simple function so esc key works with windows
void processKeys(unsigned char key, int xx, int yy)
{
    switch(key) {

        case 27: // QUIT
            glutLeaveMainLoop();
    }
}
void window(int choice, int argc, char* argv[]){
    //choice from user determines action
    if(choice == 1) {
        //these functions are needed to create window
        //made multiple times so full star map can have different size
        glutInit(&argc, argv);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(200, 100);
        glutCreateWindow("Dijkstra Path");
        glutDisplayFunc(DijkstraLine);
    }
    else if(choice == 2){
        glutInit(&argc, argv);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(200, 100);
        glutCreateWindow("BFS Path");
        glutDisplayFunc(BFSLINE);
    }
    else if(choice == 0){
        glutInit(&argc, argv);
        //see? we made it big
        glutInitWindowSize(1280, 720);
        glutInitWindowPosition(200, 100);
        glutCreateWindow("Star Chart");
        glutDisplayFunc(allStar);
    }
    //by default whole application closes on window close, this fixes that to
    //just exit function
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutKeyboardFunc(processKeys);
    glutMainLoop();
}
int main(int argc, char* argv[]) {
    cout << "----Welcome to LyftOFf----" << endl; // can use setw functions to make this look better
    cout << "----Brought to you by SpaceG----" << endl;

//yo we got a rocket ship
    cout << "       !\n"
            "       !\n"
            "       ^\n"
            "      / \\\n"
            "     /___\\\n"
            "    |=   =|\n"
            "    |     |\n"
            "    |     |\n"
            "    |     |\n"
            "    | Lyft|\n"
            "    | Off |\n"
            "    |     |\n"
            "    |     |\n"
            "    |     |\n"
            "    |     |\n"
            "   /|##!##|\\\n"
            "  / |##!##| \\\n"
            " /  |##!##|  \\\n"
            "|  / ^ | ^ \\  |\n"
            "| /  ( | )  \\ |\n"
            "|/   ( | )   \\|\n"
            "    ((   ))\n"
            "   ((  :  ))\n"
            "   ((  :  ))\n"
            "    ((   ))\n"
            "     (( ))\n"
            "      ( )\n"
            "       .\n"
            "       .\n"
            "       .";
    cout << endl;
    cout << endl;
    int choice;

    //sets filepath and loads in data to hash table
    string filePath = "C:\\Users\\lackt\\Documents\\UF\\Summer2021\\DataStructuresCOP3530\\Project3\\LyftOff\\TylersCode\\testData.txt";
    getDataFromCSV(filePath, starGraph);
    while(choice != -1){
        choice = inputOutput();
        if(choice != -1) window(choice, argc, argv);
        //if it gets here it will need to render again, hence run = false
        run = false;
    }
    return 0;

}