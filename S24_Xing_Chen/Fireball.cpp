#include "Fireball.h"

namespace Nugget {
	Fireball::Fireball(const std::string& image, int x, int y, int power, int speed)
		: Unit(image, x, y), mPower(power), mSpeed(speed)
	{
	}

	Fireball::Fireball(std::string&& image, int x, int y, int power, int speed)
		: Unit(std::move(image), x, y), mPower(power), mSpeed(speed)
	{
	}

    int Fireball::GetPower() const
    {
        return mPower;
    }

    int Fireball::GetSpeed() const
    {
        return mSpeed;
    }

    int Fireball::GetLastFireFrame() const
    {
        return mLastFireFrame;
    }

    void Fireball::SetPower(int power)
    {
        mPower = power;
    }

    void Fireball::SetSpeed(int speed)
    {
        mSpeed = speed;
    }
    void Fireball::SetLastFireFrame(int frame)
    {
        mLastFireFrame = frame;
    }
}

