#pragma once

#include "Nugget.h"

namespace Nugget
{
    class NUGGET_API Fireball : public Unit
    {
    public:
        // Constructors
        Fireball(const std::string& image, int x, int y, int power, int speed, int cooldown);
        Fireball(std::string&& image, int x, int y, int power, int speed, int cooldown);

        ~Fireball();
        int GetPower() const;
        int GetSpeed() const;
        int GetCooldown() const;
        int GetLastFireFrame() const;

        void SetPower(int power);
        void SetSpeed(int speed);
        void SetLastFireFrame(int frame);
        void DisplayFire(int x, int y, int currentFrame);

    private:
        int mPower;
        int mSpeed;
        int mLastFireFrame;
        int mCooldown;
        Nugget::Image mFireImage{ "../Assets/fire.png" };
    };
}