#pragma once

#include "Nugget.h"

class Score
{
public:
	Score();

	void DisplayScore() const;

	void IncrementScore();

	int GetScore() const;

private:
	int mScore = 0;
	Nugget::Image mBackground{ "../Assets/background.png"};
};