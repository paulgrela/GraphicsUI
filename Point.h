#pragma once

class Point final
{
public:
    Point(const int x, const int y) noexcept : x_{ x }, y_{ y }
    {
    }

    [[nodiscard]] int GetXCoordinate() const noexcept
    {
        return x_;
    }

    [[nodiscard]] int GetYCoordinate() const noexcept
    {
        return y_;
    }

private:
    int x_{ 0 };
    int y_{ 0 };
};