#include "MyGame.h"


void MyGame::Initialize()
{
	std::srand(static_cast<unsigned int>(std::time(0))); // random seed using time
	SetKeyPressedCallback([this](const Nugget::KeyPressed& e) { OnKeyPress(e); });
	mEnemySpeed = 4;
	mBulletSpeed = 17;
	mFireRate = 17;
	mGameRows = 5;
	mCurrentRow = 2;
	mFrameCount = 0;
	mEnemySpawnRate = 30;
	mGameEnd = false;

	mScore = new Score();
}

void MyGame::OnUpdate() {
	if (mGameEnd) {
		Nugget::Renderer::Draw(mEndScreenImage, 0, 0);
		mScore->DisplayScore();
		return;
	}
	Nugget::Renderer::Draw(mBackground, 0, 0);
	mScore->DisplayScore();
	CheckCollision();
	UpdatePositions();
	GenerateEnemy();
	ShootBullet();
	UpdateSpeed();
	mFrameCount++;
}

void MyGame::UpdateSpeed() {
	// every 5 score, shoot faster, enemy faster
	int currScore = mScore->GetScore();

	if (currScore % 5 == 0 && currScore != lastUpdatedScore) {
		std::cout << "update speed";
		mEnemySpeed += 1;
		mBulletSpeed += 1;
		if (mFireRate > 5)
			mFireRate -= 1;

		if (mEnemySpawnRate > 12)
			mEnemySpawnRate -= 2;
		lastUpdatedScore = currScore;
	}
}


// moves the player up or down
void MyGame::MovePlayerRow(bool moveUp)
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
void MyGame::UpdatePositions()
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

void MyGame::CheckCollision() {
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

void MyGame::OnKeyPress(const Nugget::KeyPressed& e)
{
	if (e.GetKeyCode() == NUGGET_KEY_UP || e.GetKeyCode() == NUGGET_KEY_W)
	{
		MovePlayerRow(true);
	}
	else if (e.GetKeyCode() == NUGGET_KEY_DOWN || e.GetKeyCode() == NUGGET_KEY_S) {
		MovePlayerRow(false);
	}
	else if (e.GetKeyCode() == NUGGET_KEY_SPACE && mGameEnd) {
		mScore->SetScore(0);
		mGameEnd = false;
	}
}

void MyGame::GenerateEnemy()
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
void MyGame::ShootBullet()
{
	if (mFrameCount % mFireRate != 0) {
		return;
	}

	int currRowCoord = GetRowYCoord(mCurrentRow);
	int halfRowHeight = mBackground.GetHeight() / (mGameRows * 2); // this makes the bullet center of row
	// create a unit with bullet image starting at x = player width, y = currRowCoord + halfRowHeight
	Nugget::Unit newBullet{ mBulletImage, mPlayerAvatar.GetWidth(), currRowCoord + halfRowHeight};
	mBulletUnits.emplace_back(std::move(newBullet));
}

int MyGame::GetRowYCoord(int row) {
	// calculates player pixel location: get background height, divide by total rows, get move amount * currRow
	int moveAmount = mBackground.GetHeight() / mGameRows;
	int yCoord = moveAmount * row;
	return yCoord;
}

void MyGame::EndGame() {
	std::cout << "Game Over";
	mEnemyUnits.clear();
	mBulletUnits.clear();
	mGameEnd = true;
}
