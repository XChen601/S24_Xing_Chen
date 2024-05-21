#pragma once

#include "Nugget.h"

namespace Nugget
{
    class Enemy : public Unit
    {
    public:
        Enemy(const std::string& image, int x, int y, int speed);

        Enemy(std::string&& image, int x, int y, int speed);

        int GetSpeed() const;
        void SetSpeed(int speed);

    private:
        int mSpeed;
    };
}
