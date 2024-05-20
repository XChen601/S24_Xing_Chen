#pragma once

#include "Nugget.h"

namespace Nugget
{
    class NUGGET_API Fireball : public Unit
    {
    public:
        // Constructors
        Fireball(const std::string& image, int x, int y, int power, int speed);
        Fireball(std::string&& image, int x, int y, int power, int speed);

        int GetPower() const;
        int GetSpeed() const;
        int GetLastFireFrame() const;

        void SetPower(int power);
        void SetSpeed(int speed);
        void SetLastFireFrame(int frame);

    private:
        int mPower;
        int mSpeed;
        int mLastFireFrame;
    };
}