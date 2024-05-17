#include <iostream>
#include <utility>

#include "Nugget.h"
#include "Score.h"

class MyGame : public Nugget::NuggetApplication
{
	virtual void Initialize() override
	{
		SetKeyPressedCallback([this](const Nugget::KeyPressed& e) { OnKeyPress(e); });
		mEnemySpeed = 4;
		mBulletSpeed = 15;
		mFireRate = 15;
		mGameRows = 5;
		mCurrentRow = 2;
		mFrameCount = 0;
		mEnemySpawnRate = 30;
		mGameEnd = false;
		std::srand(static_cast<unsigned int>(std::time(0)));
		mScore = new Score();
	}

	virtual void OnUpdate() override {
		Nugget::Renderer::Draw(mBackground, 0, 0);
		mScore->DisplayScore();
		if (mGameEnd) return;
		CheckCollision();
		UpdatePositions();
		GenerateEnemy();
		ShootBullet();
		UpdateSpeed();
		mFrameCount++;
	}

	void UpdateSpeed() {
		// every 5 score, shoot faster, enemy faster
		int currScore = mScore->GetScore();

		if (currScore % 5 == 0 && currScore != lastUpdatedScore) {
			std::cout << "update speed";
			mEnemySpeed += 1;
			mBulletSpeed += 1;
			if (mFireRate > 5)
				mFireRate -= 1;
		
			if (mEnemySpawnRate > 15)
				mEnemySpawnRate -= 2;
			lastUpdatedScore = currScore;
		}
	}


	// moves the player up or down
	void MovePlayerRow(bool moveUp)
	{
		if (moveUp) {
			if (mCurrentRow >= mGameRows - 1) {
				mCurrentRow = 0;
			}
			else {
				mCurrentRow += 1;
			}
		}
		else {
			if (mCurrentRow == 0) {
				mCurrentRow = mGameRows - 1;
			}
			else {
				mCurrentRow -= 1;
			}
		}
	}

	// updates all the positions
	void UpdatePositions()
	{
		// update player position
		int playerHeight = GetRowYCoord(mCurrentRow);
		Nugget::Renderer::Draw(mPlayerAvatar, 0, playerHeight);

		// update enemies locations
		for (auto& enemy : mEnemyUnits) {
			Nugget::Image mEnemyAvatar{ mEnemyImage };
			Nugget::Renderer::Draw(mEnemyAvatar, enemy.GetXCoord(), enemy.GetYCoord());
			// move enemy left 
			enemy.UpdateXCoord(-mEnemySpeed);
			if (enemy.GetXCoord() < 0) {
				EndGame();
				break;
			}
		}

		
		// update bullet locations
		for (auto& bullet : mBulletUnits) {
			Nugget::Image mBulletAvatar{ mBulletImage };
			Nugget::Renderer::Draw(mBulletAvatar, bullet.GetXCoord(), bullet.GetYCoord());
			// move bullet right 
			bullet.UpdateXCoord(mBulletSpeed);
		}

		// remove bullets when they reach end of background x coord
		mBulletUnits.erase(std::remove_if(mBulletUnits.begin(), mBulletUnits.end(),
			[&](const auto& bullet) { return bullet.GetXCoord() >= mBackground.GetWidth(); }), mBulletUnits.end());
	}

	void CheckCollision() {
		for (auto enemyIt = mEnemyUnits.begin(); enemyIt != mEnemyUnits.end();) {
			bool overlapFound = false;

			for (auto bulletIt = mBulletUnits.begin(); bulletIt != mBulletUnits.end();) {
				if (Nugget::UnitsOverlap(*enemyIt, *bulletIt)) {
					// Remove bullet and enemy units
					bulletIt = mBulletUnits.erase(bulletIt);
					enemyIt = mEnemyUnits.erase(enemyIt);

					overlapFound = true;

					mScore->IncrementScore();
					break;
				}
				else {
					++bulletIt;
				}
			}

			if (!overlapFound) {
				++enemyIt;
			}
		}
	}

	void OnKeyPress(const Nugget::KeyPressed& e)
	{
		if(e.GetKeyCode() == NUGGET_KEY_UP || e.GetKeyCode() == NUGGET_KEY_W)
		{
			MovePlayerRow(true);
		}
		else if (e.GetKeyCode() == NUGGET_KEY_DOWN || e.GetKeyCode() == NUGGET_KEY_S) {
			MovePlayerRow(false);
		}
	}

	void GenerateEnemy()
	{	
		// check if time to generate row
		if (mFrameCount % mEnemySpawnRate != 0) {
			return;
		}

		// randomly picks a row from 0 - mCurrentRow - 1 then generate an enemy
		int randomRow = rand() % mGameRows;

		int rowCoord = GetRowYCoord(randomRow);
		// add enemy location at end of randomRow
		Nugget::Unit newEnemy{ mEnemyImage, mBackground.GetWidth(), rowCoord };
		// error without using emplace_back and std::move - 'attempting to reference a deleted function'
		mEnemyUnits.emplace_back(std::move(newEnemy)); 
	}

	// generate a bullet starting from player position then goes to the end
	void ShootBullet()
	{
		if (mFrameCount % mFireRate != 0) {
			return;
		}

		int currRowCoord = GetRowYCoord(mCurrentRow);
		int halfRowHeight = mBackground.GetHeight() / (mGameRows * 2); // this makes the bullet center of row
		// create a unit with bullet image starting at x = 80, y = currRowCoord + halfRowHeight
		Nugget::Unit newBullet{ mBulletImage, 80, currRowCoord + halfRowHeight };
		mBulletUnits.emplace_back(std::move(newBullet));
	}
	
	int GetRowYCoord(int row) {
		// calculates player pixel location: get background height, divide by total rows, get move amount * currRow
		int moveAmount = mBackground.GetHeight() / mGameRows;
		int yCoord = moveAmount * row;
		return yCoord;
	}

	void EndGame() {
		std::cout << "Game Over";
		mEnemyUnits.clear();
		mBulletUnits.clear();
		mGameEnd = true;
		mBackground = Nugget::Image{ "../Assets/end_screen.png" };
	}

private:
	Nugget::Image mBackground{ "../Assets/background.png" };
	Nugget::Image mPlayerAvatar{ "../Assets/player_avatar_resized.png" };
	std::string mEnemyImage{ "../Assets/zombie_avatar_resized.png" };
	std::string mBulletImage{ "../Assets/bullet_resized.png" };
	std::string mEndScreenImage{ "../Assets/end_screen.png" };

	int mEnemySpeed;
	int mBulletSpeed;
	int mFireRate;
	int mGameRows;
	int mCurrentRow;
	int mFrameCount;
	int mEnemySpawnRate;

	std::vector<Nugget::Unit> mEnemyUnits;
	std::vector<Nugget::Unit> mBulletUnits;

	Score* mScore;
	int lastUpdatedScore = 0; // so it does update infinite times when score is used to update speed
	bool mGameEnd;
	
};

START_GAME(MyGame)