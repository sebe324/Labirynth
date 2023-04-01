#ifndef LABIRYNTH_H
#define LABIRYNTH_H

#include <SFML/Graphics.hpp>
#include <cstring>
#include <stack>

class Labirynth : public sf::Drawable{
private:
    unsigned int mazeWidth;
    unsigned int mazeHeight;
    unsigned int *maze;

    unsigned int cellSize;
    int nVisitedCells;
    std::stack<std::pair<int,int>> mazeStack;
    sf::VertexArray vArray;
    sf::VertexArray borderArrayEast;
    sf::VertexArray borderArraySouth;
    enum{

        CELL_PATH_N=1,
        CELL_PATH_E=2,
        CELL_PATH_S=4,
        CELL_PATH_W=8,
        CELL_VISITED=16
    };

    int pathWidth;

    int getMazeNeighbour(int x, int y);
    void setUpMaze();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Labirynth(unsigned int width, unsigned int height);
    ~Labirynth();
    unsigned int getMazeWidth() const;
    unsigned int getMazeHeight() const;
    bool createMaze();
    void reset();
};

#endif // LABIRYNTH_H

