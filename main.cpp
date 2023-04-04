#include <SFML/Graphics.hpp>
#include "Labirynth.h"
#include "Textbox.h"
#include "Button.h"
#include <iostream>
#include <stdlib.h>

sf::Text createText(std::string s, sf::Font& font, sf::Vector2f pos, int charSize=30, sf::Color color=sf::Color::White){
sf::Text result;
result.setFont(font);
result.setString(s);
result.setPosition(pos);
result.setCharacterSize(charSize);
result.setFillColor(color);
return result;
}
int main(){
    sf::RenderWindow window(sf::VideoMode(1000,1000),"Maze Generator" );
    Labirynth labirynth(100,100);
    window.clear();
    window.draw(labirynth);
    window.display();
    sf::Clock clock;
    sf::View labirynthView(sf::FloatRect(0.f,0.f,600.f,600.f));
    sf::View mainView(sf::FloatRect(0.f,0.f,1000.f,1000.f));
    labirynthView.setViewport(sf::FloatRect(0.02f,0.02f,0.6f,0.6f));
    sf::RectangleShape background(sf::Vector2f(600.f,600.f));
    background.setFillColor(sf::Color(60,60,60));
    background.setPosition(20.f,20.f);
    sf::Vector2f velocity;
    sf::Time deltaTime;
    sf::Clock deltaClock;
    bool autoReset=true;
    bool generated=false;
    sf::Font font;
    if(!font.loadFromFile("font.ttf")){}

    Button buttonStop("Stop",32,sf::Color(240,240,240), {725.f,100.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonStop.hoverBodyColor=sf::Color(70,70,70);
    buttonStop.hoverContentColor=sf::Color::White;

    Button buttonStart("Start",32,sf::Color(240,240,240), {725.f,200.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonStart.hoverBodyColor=sf::Color(70,70,70);
    buttonStart.hoverContentColor=sf::Color::White;

    Button buttonReset("Reset",32,sf::Color(240,240,240), {725.f,300.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonReset.hoverBodyColor=sf::Color(70,70,70);
    buttonReset.hoverContentColor=sf::Color::White;

    Button buttonChange("Change",32,sf::Color(240,240,240), {360.f,630.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonChange.hoverBodyColor=sf::Color(70,70,70);
    buttonChange.hoverContentColor=sf::Color::White;

    Button buttonExit("Exit",32,sf::Color(240,240,240), {725.f,400.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonExit.hoverBodyColor=sf::Color(70,70,70);
    buttonExit.hoverContentColor=sf::Color::White;

    sf::Text doResetText=createText("Auto reset",font,{725.f,450.f});
    Button buttonAutoReset("Yes",32,sf::Color::Green, {725.f,500.f},{150.f,50.f},sf::Color(99,99,99),font);
    buttonAutoReset.hoverBodyColor=sf::Color(70,70,70);

    sf::Text timeTaken=createText("Time Taken 0s", font,{20.f,630.f});
    sf::Time timeGeneration;
    std::vector<Textbox> textBoxes{
        Textbox("100",font,{100.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("100",font,{200.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("1",font,{300.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("5",font,{400.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),

        Textbox("255",font,{600.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("255",font,{700.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("255",font,{800.f,760.f},30,sf::Color::White,sf::Color(70,70,70)),

        Textbox("0",font,{100.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("0",font,{200.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("255",font,{300.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),

        Textbox("255",font,{600.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("0",font,{700.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),
        Textbox("0",font,{800.f,880.f},30,sf::Color::White,sf::Color(70,70,70)),
    };
    std::vector<sf::Text> labels{
        createText("Width", font,{100.f,700.f}),
        createText("Height", font,{200.f,700.f}),
        createText("Border\nsize", font, {300.f, 700.f}),
        createText("Cell\nsize", font, {400.f,700.f}),
        createText("Border\nRed",font,{600.f,700.f},30,sf::Color(255,70,70)),
        createText("Border\nGreen",font,{700.f,700.f},30,sf::Color(70,255,70)),
        createText("Border\nBlue",font,{800.f,700.f},30,sf::Color(70,70,255)),

        createText("Cell 1\nRed", font,{100.f,820.f},30,sf::Color(255,70,70)),
        createText("Cell 1\nGreen", font,{200.f,820.f},30,sf::Color(70,255,70)),
        createText("Cell 1\nBlue", font,{300.f,820.f},30,sf::Color(70,70,255)),

        createText("Cell 2\nRed", font,{600.f,820.f},30,sf::Color(255,70,70)),
        createText("Cell 2\nGreen", font,{700.f,820.f},30,sf::Color(70,255,70)),
        createText("Cell 2\nBlue", font,{800.f,820.f},30,sf::Color(70,70,255)),
    };

    for(auto& textbox : textBoxes) textbox.setMaxSize(3);
    while(window.isOpen()){
        sf::Vector2i localPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos=window.mapPixelToCoords(localPos);
        float labScale=labirynthView.getSize().x/600.f;
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type==sf::Event::Closed) window.close();
            else if(event.type==sf::Event::Resized){
                sf::Vector2u windowSize=window.getSize();
                float idk=(float)windowSize.y/windowSize.x;
                float idk2=(1.f-idk)*0.5;
                mainView.setViewport(sf::FloatRect(idk2, 0.f, idk, 1));
                labirynthView.setViewport(sf::FloatRect(idk2+0.02*idk, 0.02, idk*0.6, 0.6));
                window.setView(mainView);
            }
        if(event.type==sf::Event::MouseWheelScrolled){
            if(event.mouseWheelScroll.delta>0){
                labirynthView.zoom(0.9f);
                if(labScale<5.5) labirynth.drawBorders=true;
            }
            else{
                labirynthView.zoom(1.1f);
                if(labScale>5.5) labirynth.drawBorders=false;
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(buttonStop.click(mousePos)){
            labirynth.running=false;
        }
        else if(buttonStart.click(mousePos)){
            labirynth.running=true;
        }
        else if(buttonReset.click(mousePos)){
            labirynthView.setCenter(300.f,300.f);
            labirynth.reset();
            labirynthView.setSize(600.f,600.f);
            timeGeneration=sf::Time::Zero;
            timeTaken.setString("Time Taken " + std::to_string((timeGeneration).asSeconds())+"s");
        }
         else if(buttonExit.click(mousePos)){
            window.close();
        }
        else if(buttonChange.click(mousePos)){

            for(int i=0; i<textBoxes.size(); i++){
            if(!textBoxes[i].getTextValue().length()>0){
                        textBoxes[i].text.setString("0");
            }
            }
            labirynth.setMazeWidth(std::stoi(textBoxes[0].getTextValue()));
            labirynth.setMazeHeight(std::stoi(textBoxes[1].getTextValue()));
            labirynth.setBorderSize(std::stoi(textBoxes[2].getTextValue()));
            labirynth.setCellSize(std::stoi(textBoxes[3].getTextValue()));
            labirynth.setBorderColor(sf::Color(
            std::stoi(textBoxes[4].getTextValue()),
            std::stoi(textBoxes[5].getTextValue()),
            std::stoi(textBoxes[6].getTextValue())
            ));
            labirynth.setVisitedColor(sf::Color(
            std::stoi(textBoxes[7].getTextValue()),
            std::stoi(textBoxes[8].getTextValue()),
            std::stoi(textBoxes[9].getTextValue())
            ));
            labirynth.setUnvisitedColor(sf::Color(
            std::stoi(textBoxes[10].getTextValue()),
            std::stoi(textBoxes[11].getTextValue()),
            std::stoi(textBoxes[12].getTextValue())
            ));
            labirynthView.setCenter(300.f,300.f);
            labirynth.reset();
            labirynthView.setSize(600.f,600.f);
            timeGeneration=sf::Time::Zero;
            timeTaken.setString("Time Taken " + std::to_string((timeGeneration).asSeconds())+"s");
        }
        else if(buttonAutoReset.click(mousePos)){
            autoReset=!autoReset;
            if(autoReset){
            buttonAutoReset.originalContentColor=sf::Color::Green;
            buttonAutoReset.content.setString("Yes");
            buttonAutoReset.hoverContentColor=sf::Color::Green;
            }
            else{
            buttonAutoReset.originalContentColor=sf::Color::Red;
            buttonAutoReset.content.setString("No");
            buttonAutoReset.hoverContentColor=sf::Color::Red;
            }
        }
        for(int i=0; i<textBoxes.size(); i++) textBoxes[i].isClicked(mousePos);
        }
        if(event.type==sf::Event::TextEntered){
            if ((event.text.unicode >=48 && event.text.unicode<=57) || event.text.unicode==8){
                for(int i=0; i<textBoxes.size(); i++) textBoxes[i].addCharacter(static_cast<char>(event.text.unicode));
            }

        }

        buttonStop.update(mousePos);
        buttonStart.update(mousePos);
        buttonReset.update(mousePos);
        buttonChange.update(mousePos);
        buttonExit.update(mousePos);
        buttonAutoReset.update(mousePos);
        }
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            velocity.y=-1000.f*deltaTime.asSeconds()*labScale;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            velocity.y=1000.f*deltaTime.asSeconds()*labScale;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            velocity.x=-1000.f*deltaTime.asSeconds()*labScale;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            velocity.x=1000.f*deltaTime.asSeconds()*labScale;
        }
        labirynthView.move(velocity*=0.9f);
        if(labirynth.createMaze()){
         if(autoReset){
                labirynth.reset();
                timeGeneration=sf::Time::Zero;
                }
        }
        else if(labirynth.running)timeTaken.setString("Time Taken " + std::to_string((timeGeneration+=deltaTime).asSeconds())+"s");

        window.clear(sf::Color(20.f,20.f,20.f));
        window.draw(background);
        window.setView(labirynthView);
         window.draw(labirynth);
        window.setView(mainView);
        window.draw(buttonStop);
        window.draw(buttonStart);
        window.draw(buttonReset);
        window.draw(buttonChange);
        window.draw(buttonExit);
        window.draw(buttonAutoReset);
        window.draw(doResetText);
        for(int i=0; i<labels.size(); i++){
            window.draw(labels[i]);
        }
        window.draw(timeTaken);
        for(int i=0; i<textBoxes.size(); i++) window.draw(textBoxes[i]);
        window.display();
        deltaTime=deltaClock.restart();
    }
return 0;
}
