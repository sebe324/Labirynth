#include "Labirynth.h"
#include <string>
Labirynth::Labirynth(unsigned int width, unsigned int height){
    mazeWidth=width;
    mazeHeight=height;
    if(mazeWidth==0) mazeWidth++;
    if(mazeHeight==0) mazeHeight++;
    maze = new unsigned int[mazeWidth*mazeHeight];
    memset(maze,0,mazeWidth*mazeHeight*sizeof(int));
    maze[0]=CELL_VISITED;
    nVisitedCells=1;
    mazeStack.push(std::make_pair(0,0));

    cellSize=4;
    pathWidth=1;
    setUpMaze();
}
Labirynth::~Labirynth(){
delete [] maze;
}
void Labirynth::setUpMaze(){
    vArray=sf::VertexArray(sf::Quads,mazeWidth*mazeHeight*4);
    borderArrayEast=sf::VertexArray(sf::Quads,mazeWidth*mazeHeight*4);
    borderArraySouth=sf::VertexArray(sf::Quads,mazeWidth*mazeHeight*4);

    for(int r=0; r<mazeHeight; r++)
    for(int c=0; c<mazeWidth; c++){

        vArray[(r*mazeWidth+c)*4].position=sf::Vector2f((c*cellSize)+(pathWidth*c),r*cellSize+(pathWidth*r));
        vArray[(r*mazeWidth+c)*4+1].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize)+(pathWidth*r));
        vArray[(r*mazeWidth+c)*4+2].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));
        vArray[(r*mazeWidth+c)*4+3].position=sf::Vector2f((c*cellSize)+(pathWidth*c),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));

        vArray[(r*mazeWidth+c)*4].color=sf::Color::Red;
        vArray[(r*mazeWidth+c)*4+1].color=sf::Color::Red;
        vArray[(r*mazeWidth+c)*4+2].color=sf::Color::Red;
        vArray[(r*mazeWidth+c)*4+3].color=sf::Color::Red;

        borderArraySouth[(r*mazeWidth+c)*4].position=sf::Vector2f((c*cellSize)+(pathWidth*c),r*cellSize+cellSize+(pathWidth*r));
        borderArraySouth[(r*mazeWidth+c)*4+1].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize+cellSize)+(pathWidth*r));
        borderArraySouth[(r*mazeWidth+c)*4+2].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));
        borderArraySouth[(r*mazeWidth+c)*4+3].position=sf::Vector2f((c*cellSize)+(pathWidth*c),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));

        borderArrayEast[(r*mazeWidth+c)*4].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c),r*cellSize+(pathWidth*r));
        borderArrayEast[(r*mazeWidth+c)*4+1].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize)+(pathWidth*r));
        borderArrayEast[(r*mazeWidth+c)*4+2].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c+pathWidth),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));
        borderArrayEast[(r*mazeWidth+c)*4+3].position=sf::Vector2f((c*cellSize+cellSize)+(pathWidth*c),(r*cellSize+cellSize)+(pathWidth*r+pathWidth));
    }

}
int Labirynth::getMazeNeighbour(int x, int y){
return (mazeStack.top().second+y)*mazeWidth+(mazeStack.top().first+x);
}
bool Labirynth::createMaze(){

    if(nVisitedCells<mazeWidth*mazeHeight){
    std::vector<int> neighbours;
    //NORTH

        if(mazeStack.top().second > 0 && ~maze[getMazeNeighbour(0,-1)] & CELL_VISITED){

                neighbours.push_back(0);
        }
        //EAST
        if(mazeStack.top().first < mazeWidth-1 && ~maze[getMazeNeighbour(1,0)] & CELL_VISITED)
            {
                neighbours.push_back(1);
            }
        //SOUTH
        if(mazeStack.top().second < mazeHeight-1 && ~maze[getMazeNeighbour(0,1)] & CELL_VISITED)
            {
            neighbours.push_back(2);
            }
        //WEST
        if(mazeStack.top().first > 0 && ~maze[getMazeNeighbour(-1,0)] & CELL_VISITED)
            {
                neighbours.push_back(3);
            }
            for(int i=0; i<4; i++) vArray[getMazeNeighbour(0,0)*4+i].color=sf::Color::Blue;
    if(!neighbours.empty()){
        int next_cell_dir = neighbours[rand() % neighbours.size()];
        switch(next_cell_dir){
    case 0: maze[getMazeNeighbour(0,0)] |= CELL_PATH_N; //north
            maze[getMazeNeighbour(0,-1)]|= CELL_PATH_S;
            for(int i=0; i<4; i++) borderArraySouth[getMazeNeighbour(0,-1)*4+i].color=sf::Color(0,0,0,0);
            mazeStack.push(std::make_pair((mazeStack.top().first+0),(mazeStack.top().second-1)));
             break;
    case 1: maze[getMazeNeighbour(0,0)] |= CELL_PATH_E; //east
            maze[getMazeNeighbour(1,0)]|= CELL_PATH_W;
            for(int i=0; i<4; i++) borderArrayEast[getMazeNeighbour(0,0)*4+i].color=sf::Color(0,0,0,0);
            mazeStack.push(std::make_pair((mazeStack.top().first+1),(mazeStack.top().second)));
             break;
    case 2: maze[getMazeNeighbour(0,0)]|= CELL_PATH_S; //south
            maze[getMazeNeighbour(0,1)]|= CELL_PATH_N;
            for(int i=0; i<4; i++) borderArraySouth[getMazeNeighbour(0,0)*4+i].color=sf::Color(0,0,0,0);
            mazeStack.push(std::make_pair((mazeStack.top().first),(mazeStack.top().second+1)));
             break;
    case 3: maze[getMazeNeighbour(0,0)] |= CELL_PATH_W; //west
            maze[getMazeNeighbour(-1,0)]|= CELL_PATH_E;
            for(int i=0; i<4; i++) borderArrayEast[getMazeNeighbour(-1,0)*4+i].color=sf::Color(0,0,0,0);
            mazeStack.push(std::make_pair((mazeStack.top().first-1),(mazeStack.top().second)));
             break;
        }

        maze[getMazeNeighbour(0,0)]|=CELL_VISITED;
        nVisitedCells++;
    }
    else{
        mazeStack.pop();
    }
    return false;
    }
    return true;
}
void Labirynth::reset(){
    memset(maze,0,mazeWidth*mazeHeight*sizeof(int));
    maze[0]=CELL_VISITED;
    nVisitedCells=1;
    mazeStack=std::stack<std::pair<int,int>>();
    mazeStack.push(std::make_pair(0,0));
    setUpMaze();
}
void Labirynth::draw(sf::RenderTarget &target, sf::RenderStates states) const{
target.draw(vArray);
target.draw(borderArraySouth);
target.draw(borderArrayEast);
}
