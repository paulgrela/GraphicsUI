#pragma once

#define UNIX_PLATFORM

#include "Point.h"
#include "DrawingCanvas.h"
#include "TerminalColorsUtils.h"

#include <set>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class DrawingProcessor
{
private:
    Canvas& Canvas_;

public:
    explicit DrawingProcessor(Canvas& CanvasParam) : Canvas_(CanvasParam)
    {
    }

public:
    bool DrawCircle(const Point& CenterPoint, const double Radius, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        for (int w = 0; w < Radius * 2; w++)
            for (int h = 0; h < Radius * 2; h++)
            {
                int dx = static_cast<int>(Radius) - w;
                int dy = static_cast<int>(Radius) - h;
                if ((dx*dx + dy*dy) <= (Radius * Radius))
                    if (!Canvas_.SetPoint(CenterPoint.GetXCoordinate() + dx, CenterPoint.GetYCoordinate() + dy, Color))
                        return false;
            }

        return true;
    };

    void EraseCircle(const Point& CenterPoint, const double Radius)
    {
        Canvas_.SetUndoMode(true);
        DrawCircle(CenterPoint, Radius, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };

public:
    bool DrawRectangle(const Point& CornerPoint, const int Width, const int Height, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        for (int y = CornerPoint.GetYCoordinate(); y < CornerPoint.GetYCoordinate() + Height; y++)
            for (int x = CornerPoint.GetXCoordinate(); x < CornerPoint.GetXCoordinate() + Width; x++)
                if (!Canvas_.SetPoint(x, y, Color))
                    return false;

        return true;
    };

    void EraseRectangle(const Point& CornerPoint, const int Width, const int Height)
    {
        Canvas_.SetUndoMode(true);
        DrawRectangle(CornerPoint, Width, Height, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };

protected:
    bool DrawHorizontalLine(const int XStart, const int XEnd, const int Y, const int Color)
    {
        for (int x = XStart; x < XEnd; x++)
            if (!Canvas_.SetPoint(x, Y, Color))
                return false;

        return true;
    }

    bool FillBottomFlatTriangle(const Point& CornerPoint1, const Point& CornerPoint2, const Point& CornerPoint3, const int Color)
    {
        double Invslope1 = static_cast<double>(CornerPoint2.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint2.GetYCoordinate() - CornerPoint1.GetYCoordinate());
        double Invslope2 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate());

        double Curx1 = CornerPoint1.GetXCoordinate();
        double Curx2 = CornerPoint1.GetXCoordinate();

        for (int ScanLineY = CornerPoint1.GetYCoordinate(); ScanLineY <= CornerPoint2.GetYCoordinate(); ScanLineY++)
        {
            if (!DrawHorizontalLine(static_cast<int>(Curx1), static_cast<int>(Curx2), ScanLineY, Color))
                return false;

            Curx1 += Invslope1;
            Curx2 += Invslope2;
        }

        return true;
    }

    bool FillTopFlatTriangle(const Point& CornerPoint1, const Point& CornerPoint2, const Point& CornerPoint3, const int Color)
    {
        double Invslope1 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate());
        double Invslope2 = static_cast<double>(CornerPoint3.GetXCoordinate() - CornerPoint2.GetXCoordinate()) / static_cast<double>(CornerPoint3.GetYCoordinate() - CornerPoint2.GetYCoordinate());

        double Curx1 = CornerPoint3.GetXCoordinate();
        double Curx2 = CornerPoint3.GetXCoordinate();

        for (int ScanLineY = CornerPoint3.GetYCoordinate(); ScanLineY > CornerPoint1.GetYCoordinate(); ScanLineY--)
        {
            if (!DrawHorizontalLine(static_cast<int>(Curx1), static_cast<int>(Curx2), ScanLineY, Color))
                return false;

            Curx1 -= Invslope1;
            Curx2 -= Invslope2;
        }

        return true;
    }

public:
    bool DrawTriangle(Point& CornerPoint1, Point& CornerPoint2, Point& CornerPoint3, const int Color)
    {
        Canvas_.ClearDrawedPointsToEaraseLastShapeInCaseOfConflict();

        vector<Point> Vtemp = {CornerPoint1, CornerPoint2, CornerPoint3};
        sort(begin(Vtemp), end(Vtemp), [](const Point x1, const Point x2){ return x1.GetYCoordinate() < x2.GetYCoordinate(); });
        CornerPoint1 = Vtemp[0];
        CornerPoint2 = Vtemp[1];
        CornerPoint3 = Vtemp[2];

        if (CornerPoint2.GetYCoordinate() == CornerPoint3.GetYCoordinate())
        {
            if (!FillBottomFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Color))
                return false;
        }
        else
        if (CornerPoint1.GetYCoordinate() == CornerPoint2.GetYCoordinate())
        {
            if (!FillTopFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Color))
                return false;
        }
        else
        {
            Point CornerPoint4(static_cast<int>(static_cast<double>(CornerPoint1.GetXCoordinate()) + ((float)(CornerPoint2.GetYCoordinate() - CornerPoint1.GetYCoordinate()) / (float)(CornerPoint3.GetYCoordinate() - CornerPoint1.GetYCoordinate())) * static_cast<float>(CornerPoint3.GetXCoordinate() - CornerPoint1.GetXCoordinate())), CornerPoint2.GetYCoordinate());
            if (!FillBottomFlatTriangle(CornerPoint1, CornerPoint2, CornerPoint4, Color))
                return false;
            if (!FillTopFlatTriangle(CornerPoint2, CornerPoint4, CornerPoint3, Color))
                return false;
        }

        return true;
    };

    void EraseTriangle(Point& CornerPoint1, Point& CornerPoint2, Point& CornerPoint3)
    {
        Canvas_.SetUndoMode(true);
        DrawTriangle(CornerPoint1, CornerPoint2, CornerPoint3, Canvas_.GetColor());
        Canvas_.SetUndoMode(false);
    };
};
