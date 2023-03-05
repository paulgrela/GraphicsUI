#pragma once

#include "Point.h"

#include <set>
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

class DrawingProcessor
{
private:
    Canvas& Canvas_;

public:
    explicit DrawingProcessor(Canvas& CanvasParam) : Canvas_(CanvasParam)
    {
    }

public:
    void DrawCircle(const Point& CenterPoint, const double Radius, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        for (int w = 0; w < Radius * 2; w++)
            for (int h = 0; h < Radius * 2; h++)
            {
                int dx = static_cast<int>(Radius) - w;
                int dy = static_cast<int>(Radius) - h;
                if ((dx*dx + dy*dy) <= (Radius * Radius))
                    if (!Canvas_.SetPoint(CenterPoint.GetXCoordinate() + dx, CenterPoint.GetYCoordinate() + dy, Color))
                        return;
            }
    };

    void EraseCircle(const Point& CenterPoint, const double Radius)
    {
        Canvas_.SetUndoMode(true);
        DrawCircle(CenterPoint, Radius, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };

public:
    void DrawRectangle(const Point& CornerPoint, const int Width, const int Height, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        for (int y = CornerPoint.GetYCoordinate(); y < CornerPoint.GetYCoordinate() + Height; y++)
            for (int x = CornerPoint.GetXCoordinate(); x < CornerPoint.GetXCoordinate() + Width; x++)
                if (!Canvas_.SetPoint(x, y, Color))
                    return;
    };

    void EraseRectangle(const Point& CornerPoint, const int Width, const int Height)
    {
        Canvas_.SetUndoMode(true);
        DrawRectangle(CornerPoint, Width, Height, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };

protected:
    void DrawHorizontalLine(const int XStart, const int XEnd, const int Y, const int Color)
    {
        for (int x = XStart; x < XEnd; x++)
            Canvas_.SetPoint(x, Y, Color);
    }

    void FillBottomFlatTriangle(const Point& CornerPoint1, const Point& CornerPoint2, const Point& CornerPoint3, const int Color)
    {
        double Invslope1 = static_cast<double>(CornerPoint2.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint2.GetYCoordinate() - CornerPoint1.GetYCoordinate());
        double Invslope2 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate());

        double Curx1 = CornerPoint1.GetXCoordinate();
        double Curx2 = CornerPoint1.GetXCoordinate();

        for (int ScanLineY = CornerPoint1.GetYCoordinate(); ScanLineY <= CornerPoint2.GetYCoordinate(); ScanLineY++)
        {
            DrawHorizontalLine(static_cast<int>(Curx1), static_cast<int>(Curx2), ScanLineY, Color);
            Curx1 += Invslope1;
            Curx2 += Invslope2;
        }
    }

    void FillTopFlatTriangle(const Point& CornerPoint1, const Point& CornerPoint2, const Point& CornerPoint3, const int Color)
    {
        double Invslope1 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate());
        double Invslope2 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint2.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint2.GetYCoordinate());

        double Curx1 = CornerPoint3.GetXCoordinate();
        double Curx2 = CornerPoint3.GetXCoordinate();

        for (int ScanLineY = CornerPoint3.GetYCoordinate(); ScanLineY > CornerPoint1.GetYCoordinate(); ScanLineY--)
        {
            DrawHorizontalLine(static_cast<int>(Curx1), static_cast<int>(Curx2), ScanLineY, Color);
            Curx1 -= Invslope1;
            Curx2 -= Invslope2;
        }
    }

public:
    void DrawTriangle(Point& CornerPoint1, Point& CornerPoint2, Point& CornerPoint3, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        vector<Point> Vtemp = {CornerPoint1, CornerPoint2, CornerPoint3};
        sort(begin(Vtemp), end(Vtemp), [](const Point x1, const Point x2){ return x1.GetYCoordinate() < x2.GetYCoordinate(); });
        CornerPoint1 = Vtemp[0];
        CornerPoint2 = Vtemp[1];
        CornerPoint3 = Vtemp[2];

        if (CornerPoint2.GetYCoordinate() == CornerPoint3.GetYCoordinate())
            FillBottomFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Color);
        else
        if (CornerPoint1.GetYCoordinate() == CornerPoint2.GetYCoordinate())
            FillTopFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Color);
        else
        {
            Point CornerPoint4(static_cast<int>(static_cast<double>(CornerPoint1.GetXCoordinate()) + ((float)(CornerPoint2.GetYCoordinate() - CornerPoint1.GetYCoordinate()) / (float)(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate())) * static_cast<float>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate())), CornerPoint2.GetYCoordinate());
            FillBottomFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint4, Color);
            FillTopFlatTriangle(CornerPoint2, CornerPoint4, CornerPoint3, Color);
        }
    };

    void EraseTriangle(Point& CornerPoint1, Point& CornerPoint2, Point& CornerPoint3)
    {
        Canvas_.SetUndoMode(true);
        DrawTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };
};
