#pragma once

#include "Point.h"
#include "Command.h"

class Shape
{
public:
    explicit Shape(const int ColorParam) : Color_{ ColorParam }, Size_{ 1 }, Position_{1, 1}
    {
    }
public:
    void SetColor(int ColorParam)
    {
        Color_ = ColorParam;
    }
protected:
    int Color_;
    int Size_;
    Point Position_;
};

class UndoableDrawShapeCommand: public UndoableCommand, public Shape
{
public:
    explicit UndoableDrawShapeCommand(const int ColorParam) : Shape(ColorParam)
    {
    }
};

using DrawShapeCommandPtr = std::shared_ptr<UndoableDrawShapeCommand>;