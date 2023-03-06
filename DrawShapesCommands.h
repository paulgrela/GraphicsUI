#pragma once

#include "Command.h"
#include "DrawingCanvas.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawCircleCommand final : public UndoableDrawShapeCommand//public UndoableCommand
{
public:
    DrawCircleCommand() = delete;
    DrawCircleCommand(DrawingProcessor& ReceiverParam, const Point& CenterPointParam, const double RadiusParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CenterPoint_{ CenterPointParam }, Radius_{ RadiusParam }, UndoableDrawShapeCommand(ColorParam)
    {
    }

    bool Execute() override
    {
        return Receiver_.DrawCircle(CenterPoint_, Radius_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseCircle(CenterPoint_, Radius_);
    }

private:
    DrawingProcessor& Receiver_;
    const Point CenterPoint_;
    const double Radius_;
};

class DrawRectangleCommand final : public UndoableDrawShapeCommand
{
public:
    DrawRectangleCommand() = delete;
    DrawRectangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPointParam, const int WidthParam, const int HeightParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CornerPoint_{ CornerPointParam }, Width_{ WidthParam }, Height_{ HeightParam }, UndoableDrawShapeCommand(ColorParam)
    {
    }

    bool Execute() override
    {
        return Receiver_.DrawRectangle(CornerPoint_, Width_, Height_, Color_);
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
};

class DrawTriangleCommand final : public UndoableDrawShapeCommand
{
public:
    DrawTriangleCommand() = delete;
    DrawTriangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPoint1Param, const Point& CornerPoint2Param, const Point& CornerPoint3Param, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CornerPoint1_{ CornerPoint1Param }, CornerPoint2_{ CornerPoint2Param }, CornerPoint3_{ CornerPoint3Param }, UndoableDrawShapeCommand(ColorParam)
    {
    }

    bool Execute() override
    {
        return Receiver_.DrawTriangle(CornerPoint1_, CornerPoint2_, CornerPoint3_, Color_);
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
};