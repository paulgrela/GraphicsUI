#pragma once

#include "Command.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawCircleCommand final : public UndoableCommand
{
public:
    DrawCircleCommand() = delete;
    DrawCircleCommand(DrawingProcessor& ReceiverParam, const Point& CenterPointParam, const double RadiusParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CenterPoint_{ CenterPointParam }, Radius_{ RadiusParam }, Color_{ColorParam}
    {
    }

    void Execute() override
    {
        Receiver_.DrawCircle(CenterPoint_, Radius_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseCircle(CenterPoint_, Radius_);
    }

private:
    DrawingProcessor& Receiver_;
    const Point CenterPoint_;
    const double Radius_;
    const int Color_;
};
