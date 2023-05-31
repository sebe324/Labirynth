#include "Textbox.h"


Textbox::Textbox(std::string value, sf::Font& font, sf::Vector2f pos, unsigned int charSize, sf::Color color, sf::Color bgColor){
text.setString(value);
text.setFont(font);
text.setPosition(pos);
text.setCharacterSize(charSize);
text.setFillColor(color);
sf::FloatRect textRect=text.getGlobalBounds();

background.setPosition(pos);
minBackgroundSize={textRect.width+text.getCharacterSize(),textRect.height+text.getCharacterSize()};
background.setSize(minBackgroundSize);
background.setFillColor(bgColor);
}

void Textbox::isClicked(sf::Vector2f mousePos){
if(text.getString().isEmpty()){
if(background.getGlobalBounds().contains(mousePos)) active=true;
else active=false;
}
else if(background.getGlobalBounds().contains(mousePos)) active=true;
else active=false;
}

void Textbox::addCharacter(char c){
if(active){
        if(c==8 && !text.getString().isEmpty()){
            std::string aux=text.getString().toAnsiString();
            aux.pop_back();
            text.setString(aux);
        }
        else if(c==8 && text.getString().isEmpty()){
            //do nothing
        }
        else if(text.getString().getSize()<maxSize){
        if(c==13){
                text.setString(text.getString()+'\n');
                std::cout<<"enter!";
        }
        else text.setString(text.getString()+c);
}
changeBackground();
}
}
void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const{
if(active) target.draw(background);
target.draw(text,states);
}

std::string Textbox::getTextValue(){
return text.getString().toAnsiString();
}
void Textbox::setMaxSize(int n){
maxSize=n;
if(maxSize<text.getString().getSize()){
std::string aux=text.getString().toAnsiString();
aux.erase(maxSize);
text.setString(aux);
changeBackground();
}
}

void Textbox::changeBackground(){
sf::FloatRect textRect=text.getGlobalBounds();
if(textRect.width+text.getCharacterSize()>minBackgroundSize.x && textRect.width+text.getCharacterSize()>minBackgroundSize.y){
background.setSize({textRect.width+text.getCharacterSize(),textRect.height+text.getCharacterSize()});
}
}

