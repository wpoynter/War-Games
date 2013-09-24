/* 
 * File:   Application.h
 * Author: williampoynter
 *
 * Created on September 22, 2013, 5:52 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#define PI 3.14159265

#include <list>
#include <cmath>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

class Application {
private:
        sf::RenderWindow window;
        std::list<sf::Drawable*> toDraw;
        std::list<sf::CircleShape*> circles;
        std::list<sf::Sprite*> sprites;
        std::list<sf::Text*> texts;
        sf::Clock clock;
        sf::Music music;
        
        unsigned int WIDTH;
        unsigned int HEIGHT;
        unsigned int FR;
        
        bool paused;
        
        
        void kernal();
        sf::Thread Kernal;
public:
        Application(int argc, char** argv);
        virtual ~Application();
        
        bool run();
        
        void stop();
        
        void pause();
        void unpause();
        void togglePause();

};

#endif	/* APPLICATION_H */

