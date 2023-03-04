#pragma once

#include "Command.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawRectangleCommand final : public UndoableCommand
{
public:
DrawRectangleCommand() = delete;
DrawRectangleCommand(DrawingProcessor& ReceiverParam, const Point& CenterPointParam, const int WidthParam, const int HeightParam) noexcept : Receiver_{ ReceiverParam }, CenterPoint_{ CenterPointParam }, Width_{ WidthParam }, Height_{ HeightParam }
{
}

virtual void Execute() override
{
    Receiver_.DrawRectangle(CenterPoint_, Width_, Height_);
}

virtual void Undo() override
{
    Receiver_.EraseRectangle(CenterPoint_, Width_, Height_);
}

private:
    DrawingProcessor& Receiver_;
    const Point CenterPoint_;
    const int Width_;
    const int Height_;
};