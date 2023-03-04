#pragma once

#include "Point.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

#define UNIX_PLATFORM

#include "TerminalColorsUtils.h"

using namespace std;
using namespace terminal_colors_utils;

class Canvas
{
private:
    uint64_t SizeX_;
    uint64_t SizeY_;
    std::vector<std::vector<int>> Buffer_;
public:
    Canvas(const uint64_t SizeXParam, const uint64_t SizeYParam) : SizeX_(SizeXParam), SizeY_(SizeYParam)
    {
        Buffer_ = std::vector<std::vector<int>>(SizeX_);
        for (auto& Line : Buffer_)
        {
            Line = std::vector<int>(SizeY_);
            for (auto& Char : Line)
                Char = '0';
        }
    }
public:
    void DrawCanvas()
    {
        for (const auto& Line : Buffer_)
        {
            for (const auto& Char : Line)
                std::cout << static_cast<char>(Char);
            std::cout << std::endl;
        }
    };
};

class DrawingProcessor
{
private:
    Canvas Canvas_;
public:
    DrawingProcessor(Canvas& CanvasParam) : Canvas_(CanvasParam)
    {
    }

    void DrawCircle(const Point& CenterPoint, const double Radius)
    {
        std::cout << blue << "DrawCircle" << std::endl;
    };

    void EraseCircle(const Point& CenterPoint, const double Radius)
    {
        std::cout << red << "EraseCircle" << std::endl;
    };

    void DrawRectangle(const Point& CenterPoint, const int Width, const int Height)
    {
        std::cout << green << "DrawRectangle" << std::endl;
    };

    void EraseRectangle(const Point& CenterPoint, const int Width, const int Height)
    {
        std::cout << red << "EraseRectangle" << std::endl;
    };
};
