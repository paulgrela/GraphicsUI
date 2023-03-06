#pragma once

#define UNIX_PLATFORM

#include "TerminalColorsUtils.h"

#include <set>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace terminal_colors_utils;

class Canvas
{
private:
    int Color_;
    bool UndoMode_;
    uint64_t SizeX_;
    uint64_t SizeY_;
    std::vector<std::vector<int>> Buffer_;
    std::vector<Point> DrawedPointsToEaraseLastShapeInCaseOfConflict;
public:
    Canvas(const uint64_t SizeXParam, const uint64_t SizeYParam, const int ColorParam) : SizeX_(SizeXParam), SizeY_(SizeYParam), Color_{ColorParam}
    {
        UndoMode_ = false;
        Buffer_ = std::vector<std::vector<int>>(SizeY_);
        for (auto& Line : Buffer_)
        {
            Line = std::vector<int>(SizeX_);
            for (auto& Char : Line)
                Char = Color_;
        }
    }
public:
    void ClearDrawedPointsToEaraseLastShapeInCaseOfConflict()
    {
        DrawedPointsToEaraseLastShapeInCaseOfConflict.clear();
        DrawedPointsToEaraseLastShapeInCaseOfConflict.reserve(1024 * 1024);
    }

    bool SetPoint(const int X, const int Y, int Color)
    {
        if (X > 0 && X < SizeX_ && Y > 0 && Y < SizeY_)
        {
            if (Buffer_[Y][X] == Color_ || UndoMode_)
            {
                Buffer_[Y][X] = Color;
                DrawedPointsToEaraseLastShapeInCaseOfConflict.emplace_back(Y, X);
            }
            else
            if (!UndoMode_)
            {
                for (const auto& PointObject : DrawedPointsToEaraseLastShapeInCaseOfConflict)
                    Buffer_[PointObject.GetXCoordinate()][PointObject.GetYCoordinate()] = Color_;

                DrawedPointsToEaraseLastShapeInCaseOfConflict.clear();

                return false;
            }
        }

        return true;
    }
public:
    void SetUndoMode(const bool UndoModeParam)
    {
        UndoMode_ = UndoModeParam;
    }
public:
    [[nodiscard]] int GetColor() const
    {
        return Color_;
    }
public:
    void DrawCanvas()
    {
        for (const auto& Line : Buffer_)
        {
            for (const auto& Char : Line)
            {
                switch (Char)
                {
                    case '1' : cout << red; break;
                    case '2' : cout << green; break;
                    case '3' : cout << blue; break;
                    case '4' : cout << magneta; break;
                    case '5' : cout << cyan; break;
                    case '7' : cout << red; break;
                    case '8' : cout << green; break;
                    case '9' : cout << blue; break;
                    default : break;
                }
                cout << static_cast<char>(Char);
                cout << background_black;
            }

            cout << std::endl;
        }

        cout << endl;
    };
};