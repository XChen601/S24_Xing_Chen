#include "MyGame.h"


void MyGame::Initialize()
{
	std::srand(static_cast<unsigned int>(std::time(0))); // random seed using time
	SetKeyPressedCallback([this](const Nugget::KeyPressed& e) { OnKeyPress(e); });
	mScore = new Score();
	ResetGame();
}

void MyGame::ResetGame()
{
	mScore->SetScore(0);
	mGameEnd = false;
	// reset all the speeds
	mEnemySpeed = 7;
	mBulletSpeed = 17;
	mFireRate = 23;
	mGameRows = 5;
	mCurrentRow = 2;
	mFrameCount = 0;
	mEnemySpawnRate = 30;
	mNextSpawnFrame = 0;
	mLastFireFrame = 0;
	mFireball.SetLastFireFrame(-999);
	mFireball.SetCoords(9999, 9999);
}

void MyGame::OnUpdate() {
	if (mGameEnd) {
		Nugget::Renderer::Draw(mEndScreenImage, 0, 0);
		mScore->DisplayScore();
		return;
	}
	Nugget::Renderer::Draw(mBackground, 0, 0);
	mFireball.DisplayFire(mBackground.GetWidth(), mBackground.GetHeight(), mFrameCount);
	mScore->DisplayScore();
	UpdatePositions();
	CheckCollision();
	GenerateEnemy();
	UpdateSpeed();
	mFrameCount++;
}

void MyGame::UpdateSpeed() {
	// every 5 score, shoot faster, enemy spawn faster
	int currScore = mScore->GetScore();

	if (currScore % 5 == 0 && currScore != lastUpdatedScore) {
		if (currScore % 15 == 0)
			mEnemySpeed += 1;
		if (mFireRate > 5)
			mFireRate -= 2;
		if (mEnemySpawnRate > 10)
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
		Nugget::Image enemyAvatar{ mEnemyImage };
		Nugget::Renderer::Draw(enemyAvatar, enemy.GetXCoord(), enemy.GetYCoord());
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

	
	// update fireball location
	mFireball.UpdateXCoord(mFireball.GetSpeed());
	Nugget::Image fireBallAvatar{ "../Assets/fireball.png" };
	Nugget::Renderer::Draw(fireBallAvatar, mFireball.GetXCoord(), mFireball.GetYCoord());


}

void MyGame::CheckCollision() {
	// check bullet collisions
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

	// check fireball collisions
	for (auto enemyIt = mEnemyUnits.begin(); enemyIt != mEnemyUnits.end();) {
		bool overlapFound = false;
		if (Nugget::UnitsOverlap(mFireball, *enemyIt)) {
			enemyIt = mEnemyUnits.erase(enemyIt);
			mFireball.SetPower(mFireball.GetPower() - 1);
			if (mFireball.GetPower() <= 0) {
				mFireball.SetCoords(9999, 9999);
			}
			overlapFound = true;
			mScore->IncrementScore();
			break;
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
		ResetGame();
	}
	else if (e.GetKeyCode() == NUGGET_KEY_SPACE && !mGameEnd) {
		ShootBullet();
	}
	else if (e.GetKeyCode() == NUGGET_KEY_D || e.GetKeyCode() == NUGGET_KEY_RIGHT) {
		ShootFireball();
	}
}

void MyGame::GenerateEnemy()
{
	// check if time to generate row
	if (mFrameCount != mNextSpawnFrame) {
		return;
	}

	// randomly picks a row from 0 - mCurrentRow - 1 then generate an enemy
	int randomRow = rand() % mGameRows;

	int rowCoord = GetRowYCoord(randomRow);
	// add enemy location at end of randomRow
	Nugget::Unit newEnemy{ mEnemyImage, mBackground.GetWidth(), rowCoord };
	// error without using emplace_back and std::move - 'attempting to reference a deleted function'
	mEnemyUnits.emplace_back(std::move(newEnemy));

	// makes generating enemies more random
	int random_offset = rand() % mEnemySpawnRate - mEnemySpawnRate/2;
	mNextSpawnFrame = mNextSpawnFrame + mEnemySpawnRate + random_offset;
}

// generate a bullet starting from player position then goes to the end
void MyGame::ShootBullet()
{
	if ((mFrameCount - mLastFireFrame) < mFireRate) {
		return; // not enough frames have passed since the last shot
	}
	int currRowCoord = GetRowYCoord(mCurrentRow);
	int halfRowHeight = mBackground.GetHeight() / (mGameRows * 2); // this makes the bullet center of row
	// create a unit with bullet image starting at x = player width, y = currRowCoord + halfRowHeight
	Nugget::Unit newBullet{ mBulletImage, mPlayerAvatar.GetWidth(), currRowCoord + halfRowHeight};
	mBulletUnits.emplace_back(std::move(newBullet));

	mLastFireFrame = mFrameCount;
}

void MyGame::ShootFireball()
{
	// if it hasnt been 60 frames yet, cant fire
	if ((mFrameCount - mFireball.GetLastFireFrame()) < mFireball.GetCooldown()) {
		return;
	}
	mFireball.SetPower(4);
	int currRowCoord = GetRowYCoord(mCurrentRow);
	mFireball.SetCoords(mPlayerAvatar.GetWidth(), currRowCoord + 5);
	mFireball.SetLastFireFrame(mFrameCount);
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
