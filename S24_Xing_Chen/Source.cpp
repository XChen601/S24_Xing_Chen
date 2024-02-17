#include "Nugget.h"
#include <iostream>

class MyGame : public Nugget::NuggetApplication
{
	virtual void OnUpdate() override {
		std::cout << "engine is running" << std::endl;
	}

};

START_GAME(MyGame)