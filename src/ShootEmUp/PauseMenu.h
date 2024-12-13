#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>


#include "SFML\System.hpp"
#include "SFML\window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

public:
	PauseMenu(sf::RenderWindow* window);
	virtual ~PauseMenu();

	void update();
};

#endif 
