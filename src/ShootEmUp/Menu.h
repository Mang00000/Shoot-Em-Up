#ifndef MENU_H
#define MENU_H

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

class Menu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

public:
	Menu(sf::RenderWindow* window);
	void Vmenu(sf::RenderWindow* window);
	void Dmenu(sf::RenderWindow* window);
	virtual ~Menu();

	void update();
};

#endif 