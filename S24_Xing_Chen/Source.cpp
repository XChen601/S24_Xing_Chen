#include "Nugget.h"
#include <iostream>


class MyGame : public Nugget::NuggetApplication
{
	virtual void Initialize() override
	{

	}

	virtual void OnUpdate() override {
		//std::cout << "window width " << Nugget::NuggetWindow::GetWindow()->GetWidth() << std::endl;
	}

private:

};

START_GAME(MyGame)