#pragma once

#include "Command.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawTriangleCommand final : public UndoableCommand
{
public:
    DrawTriangleCommand() = delete;
    DrawTriangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPoint1Param, const Point& CornerPoint2Param, const Point& CornerPoint3Param, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CornerPoint1_{ CornerPoint1Param }, CornerPoint2_{ CornerPoint2Param }, CornerPoint3_{ CornerPoint3Param }, Color_{ColorParam}
    {
    }

    void Execute() override
    {
        Receiver_.DrawTriangle(CornerPoint1_, CornerPoint2_, CornerPoint3_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseTriangle(CornerPoint1_, CornerPoint2_, CornerPoint3_);
    }

private:
    DrawingProcessor& Receiver_;
    Point CornerPoint1_;
    Point CornerPoint2_;
    Point CornerPoint3_;
    int Color_;
};