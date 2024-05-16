#include <iostream>
#include <utility>

#include "Nugget.h"

class MyGame : public Nugget::NuggetApplication
{
	virtual void Initialize() override
	{
		SetKeyPressedCallback([this](const Nugget::KeyPressed& e) { OnKeyPress(e); });
		mEnemySpeed = 2;
		mBulletSpeed = 15;
		mFireRate = 15;
		mGameRows = 5;
		mCurrentRow = 2;
		mFrameCount = 0;
		mEnemySpawnRate = 130;
		std::srand(static_cast<unsigned int>(std::time(0)));
	}

	virtual void OnUpdate() override {
		//std::cout << "window width " << Nugget::NuggetWindow::GetWindow()->GetWidth() << std::endl;
		Nugget::Renderer::Draw(mBackground, 0, 0);
		updatePositions();
		generateEnemy();
		shootBullet();
		mFrameCount++;
	}

	// moves the player up or down
	void movePlayerRow(bool moveUp)
	{
		if (moveUp) {
			if (mCurrentRow >= mGameRows - 1) {
				mCurrentRow = 0;
			}
			else {
				mCurrentRow += 1;
			}
			std::cout << mCurrentRow;
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
	void updatePositions()
	{
		// update player position
		int playerHeight = getRowCoord(mCurrentRow);
		Nugget::Renderer::Draw(mPlayerAvatar, 0, playerHeight);

		// update enemies locations
		for (auto& enemy : mEnemyLocations) {
			Nugget::Renderer::Draw(mEnemyAvatar, enemy.x, enemy.y);
			enemy.x -= enemy.speed;
		}

		// update bullet locations
		for (auto it = mBulletLocations.begin(); it != mBulletLocations.end();) {
			Nugget::Renderer::Draw(mBullet, it->x, it->y);
			it->x += it->speed;
			// remove bullets if x > background width
			if (it->x > mBackground.GetWidth()) {
				it = mBulletLocations.erase(it); // erase returns the next iterator
			}
			else {
				++it; // only increment if not erasing
			}
		}
	}

	void OnKeyPress(const Nugget::KeyPressed& e)
	{
		if(e.GetKeyCode() == NUGGET_KEY_UP || e.GetKeyCode() == NUGGET_KEY_W)
		{
			movePlayerRow(true);
		}
		else if (e.GetKeyCode() == NUGGET_KEY_DOWN || e.GetKeyCode() == NUGGET_KEY_S) {
			movePlayerRow(false);
		}
	}

	void generateEnemy()
	{	
		// check if time to generate row
		if (mFrameCount % mEnemySpawnRate != 0) {
			return;
		}

		// randomly picks a row from 0 - mCurrentRow - 1 then generate an enemy
		int randomRow = rand() % mGameRows;

		int rowCoord = getRowCoord(randomRow);
		// add enemy location at end of randomRow
		Enemy newEnemy;
		mEnemyLocations.emplace_back(mBackground.GetWidth(), rowCoord, 1, mEnemySpeed);


		std::cout << "random row: " << randomRow << std::endl;
	}

	// generate a bullet starting from player position then goes to the end
	void shootBullet()
	{
		if (mFrameCount % mFireRate != 0) {
			return;
		}

		int currRowCoord = getRowCoord(mCurrentRow);
		Bullet newBullet;
		mBulletLocations.emplace_back(80, currRowCoord, mBulletSpeed);
		
	}
	
	int getRowCoord(int row) {
		// calculates player pixel location: get background height, divide by total rows, get move amount * currRow
		int moveAmount = mBackground.GetHeight() / mGameRows;
		int yCoord = moveAmount * row;
		return yCoord;
	}



private:
	Nugget::Image mBackground{ "../Assets/background.png" };
	Nugget::Image mPlayerAvatar{ "../Assets/player_avatar_resized.png" };
	Nugget::Image mEnemyAvatar{ "../Assets/zombie_avatar_resized.png" };
	Nugget::Image mBullet{ "../Assets/bullet_resized.png" };

	int mEnemySpeed;
	int mBulletSpeed;
	int mFireRate;
	int mGameRows;
	int mCurrentRow;
	int mFrameCount;
	int mEnemySpawnRate;
	struct Enemy {
		int x;
		int y;
		int hp;
		int speed;
	};
	std::vector<Enemy> mEnemyLocations;

	struct Bullet {
		int x;
		int y;
		int speed;
	};
	std::vector<Bullet> mBulletLocations;
};

START_GAME(MyGame)