#include "Enemy.h"

namespace Nugget
{
    Enemy::Enemy(const std::string& image, int x, int y, int speed)
        : Unit(image, x, y), mSpeed(speed)
    {
    }
    Enemy::Enemy(std::string&& image, int x, int y, int speed)
        : Unit(std::move(image), x, y), mSpeed(speed)
    {
    }

    int Enemy::GetSpeed() const
    {
        return mSpeed;
    }

    void Enemy::SetSpeed(int speed)
    {
        mSpeed = speed;
    }
}
