#ifndef LABIRYNTH_H
#define LABIRYNTH_H

#include <SFML/Graphics.hpp>
#include <cstring>
#include <stack>
#include <fstream>
#include "Util.h"

class Labirynth : public sf::Drawable{
private:
    unsigned int mazeWidth;
    unsigned int mazeHeight;
    unsigned int *maze;

    unsigned int cellSize;
    int pathWidth;
    int nVisitedCells;
    std::stack<std::pair<int,int>> mazeStack;
    sf::VertexArray vArray;
    sf::VertexArray borderArrayEast;
    sf::VertexArray borderArraySouth;

    sf::Color visitedColor=sf::Color::Blue;
    sf::Color borderColor=sf::Color::White;
    sf::Color unvisitedColor=sf::Color::Red;

    enum{

        CELL_PATH_N=1,
        CELL_PATH_E=2,
        CELL_PATH_S=4,
        CELL_PATH_W=8,
        CELL_VISITED=16
    };


    int getMazeNeighbour(int x, int y);
    void setUpMaze();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    bool drawBorders=true;
    bool running=true;
    Labirynth(unsigned int width, unsigned int height);
    ~Labirynth();
    unsigned int getMazeWidth() const;
    unsigned int getMazeHeight() const;
    bool createMaze();
    void reset();
    void setCellSize(int n);
    void setBorderSize(int n);
    void setMazeWidth(int n);
    void setMazeHeight(int n);
    void setVisitedColor(sf::Color color);
    void setUnvisitedColor(sf::Color color);
    void setBorderColor(sf::Color color);

    void saveToFile();
};

#endif // LABIRYNTH_H

