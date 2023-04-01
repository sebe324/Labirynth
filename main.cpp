#include <SFML/Graphics.hpp>
#include "Labirynth.h"
#include <iostream>
int main(){
    sf::RenderWindow window(sf::VideoMode(1000,1000),"Labirynt" );
    Labirynth labirynth(200,200);
    window.clear();
    window.draw(labirynth);
    window.display();
    sf::Clock clock;
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type==sf::Event::Closed) window.close();
        }
        if(labirynth.createMaze()){
        std::cout<<"Time taken: "<<clock.restart().asSeconds()<<std::endl;
         labirynth.reset();
        }
        window.clear();
         window.draw(labirynth);
        window.display();

    }
return 0;
}
