#pragma once

#include "Command.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawRectangleCommand final : public UndoableCommand
{
public:
    DrawRectangleCommand() = delete;
    DrawRectangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPointParam, const int WidthParam, const int HeightParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CornerPoint_{ CornerPointParam }, Width_{ WidthParam }, Height_{ HeightParam }, Color_{ColorParam}
    {
    }

    void Execute() override
    {
        Receiver_.DrawRectangle(CornerPoint_, Width_, Height_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseRectangle(CornerPoint_, Width_, Height_);
    }

private:
    DrawingProcessor& Receiver_;
    const Point CornerPoint_;
    const int Width_;
    const int Height_;
    const int Color_;
};