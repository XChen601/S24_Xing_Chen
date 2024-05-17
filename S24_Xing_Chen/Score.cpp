#include "Score.h"


Score::Score()
{
}

void Score::DisplayScore() const
{
	// 19 -> get last digit, start = top right - digit.width, digit.height
	int score = mScore;
	int currXCoord = mBackground.GetWidth() - 20;

	if (score == 0) {
		Nugget::Image digitImage{ "../Assets/0.png" };
		Nugget::Renderer::Draw(digitImage, currXCoord - digitImage.GetWidth(), 20);
	}

	while (score != 0) {
		int lastDigit = score % 10;

		std::string digitLocation = std::format("../Assets/{}.png", lastDigit);
		Nugget::Image digitImage{ digitLocation };
		Nugget::Renderer::Draw(digitImage, currXCoord - digitImage.GetWidth(), 20);
		currXCoord -= digitImage.GetWidth();

		score /= 10;
	}
	
}

void Score::IncrementScore()
{
	mScore += 1;
}

int Score::GetScore() const
{
	return mScore;
}
