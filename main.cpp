/* 
 * File:   main.cpp
 * Author: williampoynter
 *
 * Created on September 20, 2013, 10:46 PM
 */

#include <cstdlib>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

using namespace std;

void one() {
        for(int i = 0; i < 10; i++) {
                std::cout << "One: " << i << std::endl;
        }
}

void two() {
        for(int i = 0; i < 10; i++) {
                std::cout << "Two: " << i << std::endl;
        }
}

int main(int argc, char** argv) {
        
        std::thread first (one);
        std::thread second (two);
        
        std::cout << "Main" << std::endl;
        
        first.join();
        second.join();
        
        std::cout << "End" << std::endl;
        
        /*sf::RenderWindow window(sf::VideoMode(640, 360), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(5);
        shape.setPosition(220,80);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }*/
        
        return 0;
}

