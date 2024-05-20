#include "Fireball.h"

namespace Nugget {
	Fireball::Fireball(const std::string& image, int x, int y, int power, int speed, int cooldown)
		: Unit(image, x, y), mPower(power), mSpeed(speed), mCooldown(cooldown)
	{
	}

	Fireball::Fireball(std::string&& image, int x, int y, int power, int speed, int cooldown)
		: Unit(std::move(image), x, y), mPower(power), mSpeed(speed), mCooldown(cooldown)
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

    int Fireball::GetCooldown() const
    {
        return mCooldown;
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
    void Fireball::DisplayFire(int x, int y, int currentFrame)
    {   
        if ((currentFrame - mLastFireFrame) < mCooldown) {
            return;
        }
        std::cout << "test";
        Nugget::Renderer::Draw(mFireImage, x - mFireImage.GetWidth(), y - mFireImage.GetHeight());
    }
}

