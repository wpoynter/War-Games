/* 
 * File:   Application.cpp
 * Author: williampoynter
 * 
 * Created on September 22, 2013, 5:52 PM
 */

#include "Application.h"

Application::Application(int argc, char** argv) : Kernal(&Application::kernal, this) {
        
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        
        window.create(sf::VideoMode(1024,640),"We are one",sf::Style::Fullscreen, settings);
        WIDTH = window.getSize().x;
        HEIGHT = window.getSize().y;
        
        FR = 200;
        paused = false;
}

Application::~Application() {
}

bool Application::run() {
        
        sf::CircleShape *cir = new sf::CircleShape(100.f);
        cir->setFillColor(sf::Color::Green);
        cir->setOutlineColor(sf::Color::Red);
        cir->setOutlineThickness(25);
        cir->setOrigin(100,100);
        cir->setPosition(WIDTH/2,HEIGHT/2);
        cir->setPointCount(100);
        toDraw.push_back(cir);
        circles.push_back(cir);
        
        sf::CircleShape *cir2 = new sf::CircleShape(40.f);
        toDraw.push_back(cir2);
        circles.push_back(cir2);
        cir2->setFillColor(sf::Color::Blue);
        cir2->setOutlineColor(sf::Color::Yellow);
        cir2->setOutlineThickness(2);
        cir2->setOrigin(40,40);
        cir2->setPosition(WIDTH/2,HEIGHT/2-140);
        cir2->rotate(0);
        cir2->setPointCount(100);
        
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text *text = new sf::Text("hello", font);
        text->setCharacterSize(30);
        text->setStyle(sf::Text::Bold);
        text->setColor(sf::Color::Red);
        sf::FloatRect textRect = text->getLocalBounds();
        text->setOrigin(textRect.left + textRect.width,
               textRect.top  + textRect.height);
        text->setPosition(sf::Vector2f(WIDTH-10,HEIGHT-10));
        toDraw.push_back(text);  
        texts.push_back(text);
        
        sf::Texture texture;
        if (!texture.loadFromFile("Space_envader.png")) exit(0);
        texture.setRepeated(false);
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(texture);
        toDraw.push_back(sprite);
        sprites.push_back(sprite);
        sprite->setScale(0.2,0.2);
        
        music.openFromFile("music.flac");
        music.play();
        
        Kernal.launch();
        
        sf::Event event;
        
        while (window.isOpen())
        {
                while (window.pollEvent(event))
                {
                        switch(event.type) {
                                case sf::Event::LostFocus:
                                        pause();
                                        break;
                                case sf::Event::GainedFocus:
                                        unpause();
                                        break;
                                case sf::Event::Closed:
                                        stop();
                                        break;
                                case sf::Event::KeyPressed:
                                        if (event.key.code == sf::Keyboard::Escape)
                                                stop();
                                        if (event.key.code == sf::Keyboard::P)
                                                togglePause();
                                        break;
                                default:
                                        break;
                                        
                        }

                }
                usleep(200000);
        }
        
        return 0;
}

void Application::kernal() {
        
        float angle = 0; float mag;
        int dir = 1;
        sf::Time time = clock.getElapsedTime();
        while (window.isOpen())
        {
                float elapsed = clock.getElapsedTime().asMilliseconds() - time.asMilliseconds();
                if (elapsed >= (1000/FR)) {
                        
                        while (paused) 
                                usleep(1000);
                        
                        time = clock.getElapsedTime();
                        float freq = 1000/elapsed;
                        
                        angle = angle + 60.f*(elapsed/1000.f);
                        mag = 300*(elapsed/1000.f);
                        
                        circles.back()->setPosition(cos(angle*PI/180)*140+WIDTH/2, sin(angle*PI/180)*140+HEIGHT/2);
                        std::stringstream ss;
                        ss << freq << "Hz";
                        texts.back()->setString(ss.str());
                        
                        sprites.back()->move(dir*mag,0);
                        
                        if (sprites.back()->getGlobalBounds().width + sprites.back()->getGlobalBounds().left >= WIDTH ||
                                sprites.back()->getGlobalBounds().left <= 0)
                                dir = dir * -1;
                        
                        sf::FloatRect textRect = texts.back()->getLocalBounds();
                        texts.back()->setOrigin(textRect.left + textRect.width,
                               textRect.top  + textRect.height);
                        texts.back()->setPosition(sf::Vector2f(WIDTH-10,HEIGHT-10));

                        window.clear();
                        for (std::list<sf::Drawable*>::iterator iter = toDraw.begin(); iter != toDraw.end(); iter++)
                                window.draw(**iter);
                        window.display();
                } else
                        usleep(((1000/FR)-1-elapsed) * 1000);
        }
}

void Application::stop() {
        Kernal.terminate();
        window.close();
}

void Application::pause() {
        paused = true;
        music.pause();
}

void Application::unpause() {
        paused = false;
        music.play();
}

void Application::togglePause() {
        paused = !paused;
        if (music.getStatus() == sf::Music::Paused)
                music.play();
        else
                music.pause();
}