#pragma once

#include "Command.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawTriangleCommand final : public UndoableCommand
{
public:
    DrawTriangleCommand() = delete;
    DrawTriangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPoint1Param, const Point& CornerPoint2Param, const Point& CornerPoint3Param) noexcept : Receiver_{ ReceiverParam }, CornerPoint1_{ CornerPoint1Param }, CornerPoint2_{ CornerPoint2Param }, CornerPoint3_{ CornerPoint3Param }
    {
    }

    void Execute() override
    {
        Receiver_.DrawTriangle(CornerPoint1_, CornerPoint2_, CornerPoint3_);
    }

    void Undo() override
    {
        Receiver_.EraseTriangle(CornerPoint1_, CornerPoint2_, CornerPoint3_);
    }

private:
    DrawingProcessor& Receiver_;
    const Point CornerPoint1_;
    const Point CornerPoint2_;
    const Point CornerPoint3_;
};