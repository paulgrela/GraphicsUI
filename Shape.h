#pragma once

#include "Point.h"
#include "Command.h"

class Shape
{
public:
    explicit Shape(const int ColorParam, const int SizeParam, const Point PositionParam) : Color_{ ColorParam }, Size_{ 1 }, Position_{ PositionParam }
    {
    }
public:
    void SetColor(const int ColorParam)
    {
        Color_ = ColorParam;
    }
    [[nodiscard]] int GetColor() const
    {
        return Color_;
    }
public:
    void SetSize(const int SizeParam)
    {
        Size_ = SizeParam;
    }
public:
    void SetPosition(const Point PositionParam)
    {
        Position_ = PositionParam;
    }
    void AddPosition(const Point PositionParam)
    {
        SetPosition({ PositionParam.GetXCoordinate() + Position_.GetXCoordinate(), PositionParam.GetYCoordinate() + Position_.GetYCoordinate()});
    }
protected:
    int Color_;
    int Size_;
    Point Position_;
public:
    void SetSetShapeColorToSubShape(const bool SetShapeColorToSubShapeParam)
    {
        SetShapeColorToSubShape = SetShapeColorToSubShapeParam;
    }
    void SetSetShapePositionToSubShape(const bool SetShapePositionToSubShapeParam)
    {
        SetShapePositionToSubShape = SetShapePositionToSubShapeParam;
    }
protected:
    bool SetShapeColorToSubShape = false;
    bool SetShapePositionToSubShape = false;
};

class UndoableDrawShapeCommand: public UndoableCommand, public Shape
{
public:
    explicit UndoableDrawShapeCommand(const int ColorParam, const int SizeParam, const Point PositionParam) : Shape(ColorParam, SizeParam, PositionParam)
    {
    }
};

using DrawShapeCommandPtr = std::shared_ptr<UndoableDrawShapeCommand>;