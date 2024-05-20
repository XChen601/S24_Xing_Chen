#pragma once

#include "Nugget.h"
#include "Score.h"
#include "Fireball.h"

class MyGame : public Nugget::NuggetApplication
{
public:
    virtual void Initialize() override;
    virtual void OnUpdate() override;

private:
    void UpdateSpeed();
    void MovePlayerRow(bool moveUp);
    void UpdatePositions();
    void CheckCollision();
    void OnKeyPress(const Nugget::KeyPressed& e);
    void ResetGame();
    void GenerateEnemy();
    void ShootBullet();
    void ShootFireball();
    int GetRowYCoord(int row);
    void EndGame();

    Nugget::Image mBackground{ "../Assets/background.png" };
    Nugget::Image mPlayerAvatar{ "../Assets/player_avatar_resized.png" };
    std::string mEnemyImage{ "../Assets/zombie_avatar_resized.png" };
    std::string mBulletImage{ "../Assets/bullet_resized.png" };
    Nugget::Image mEndScreenImage{ "../Assets/end_screen.png" };

    int mEnemySpeed;
    int mBulletSpeed;
    int mFireRate;
    int mGameRows;
    int mCurrentRow;
    int mFrameCount;
    int mEnemySpawnRate;
    int mNextSpawnFrame;
    int mLastFireFrame;
    Nugget::Fireball mFireball{ "../Assets/fireball.png", 2000, 2000, 3, 10, 160 };

    std::vector<Nugget::Unit> mEnemyUnits;
    std::vector<Nugget::Unit> mBulletUnits;

    Score* mScore;
    int lastUpdatedScore = 0;
    bool mGameEnd;
    
};
