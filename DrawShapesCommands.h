#pragma once

#include "Command.h"
#include "DrawingCanvas.h"
#include "DrawingProcessor.h"
#include "Point.h"

class DrawCircleCommand final : public UndoableDrawShapeCommand
{
public:
    DrawCircleCommand() = delete;
    DrawCircleCommand(DrawingProcessor& ReceiverParam, const Point& CenterPointParam, const double RadiusParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, Radius_{ RadiusParam }, UndoableDrawShapeCommand(ColorParam, 1, CenterPointParam)
    {
    }

    bool Execute() override
    {
        return Receiver_.DrawCircle({ Position_.GetXCoordinate(), Position_.GetYCoordinate() }, Radius_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseCircle({ Position_.GetXCoordinate(), Position_.GetYCoordinate() }, Radius_);
    }

private:
    DrawingProcessor& Receiver_;
    const double Radius_;
};

class DrawRectangleCommand final : public UndoableDrawShapeCommand
{
public:
    DrawRectangleCommand() = delete;
    DrawRectangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPointParam, const int WidthParam, const int HeightParam, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, Width_{ WidthParam }, Height_{ HeightParam }, UndoableDrawShapeCommand(ColorParam, 1, CornerPointParam)
    {
    }

    bool Execute() override
    {
        return Receiver_.DrawRectangle({ Position_.GetXCoordinate(), Position_.GetYCoordinate() }, Width_, Height_, Color_);
    }

    void Undo() override
    {
        Receiver_.EraseRectangle({ Position_.GetXCoordinate(), Position_.GetYCoordinate() }, Width_, Height_);
    }

private:
    DrawingProcessor& Receiver_;
    const int Width_;
    const int Height_;
};

class DrawTriangleCommand final : public UndoableDrawShapeCommand
{
public:
    DrawTriangleCommand() = delete;
    DrawTriangleCommand(DrawingProcessor& ReceiverParam, const Point& CornerPoint1Param, const Point& CornerPoint2Param, const Point& CornerPoint3Param, const int ColorParam) noexcept : Receiver_{ ReceiverParam }, CornerPoint1_{ CornerPoint1Param }, CornerPoint2_{ CornerPoint2Param }, CornerPoint3_{ CornerPoint3Param }, UndoableDrawShapeCommand(ColorParam, 1, CornerPoint1Param)
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