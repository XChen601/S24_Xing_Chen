#pragma once

#include "Nugget.h"

class Score
{
public:
	Score();

	void DisplayScore() const;

	void IncrementScore();

	int GetScore() const;

	void SetScore(int score);

private:
	int mScore = 0;
	Nugget::Image mBackground{ "../Assets/background.png"};
};