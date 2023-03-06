
#include "CommandProcessor.h"
#include "CompositeCommand.h"
#include "DrawShapesCommands.h"
#include "DrawingProcessor.h"
#include "DrawingCanvas.h"

int main()
{
    Canvas CanvasObject{ 100, 20, static_cast<int>('0')};
    CanvasObject.DrawCanvas();

    DrawingProcessor DrawingProcessorObject{ CanvasObject };

    auto MacroRecorderPtr = std::make_shared<CompositeCommand>();

    CommandPtr DrawCircleCommandPtr = std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 17, 7 }, 5, static_cast<int>('2'));
    MacroRecorderPtr->AddCommand(DrawCircleCommandPtr);

    CanvasObject.DrawCanvas();

    CommandPtr DrawRectangleCommandPtr = std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, Point{30, 10 }, 10, 5, static_cast<int>('4'));
    MacroRecorderPtr->AddCommand(DrawRectangleCommandPtr);

    CanvasObject.DrawCanvas();

    CommandPtr DrawTriangleCommandPtr = std::make_shared<DrawTriangleCommand>(DrawingProcessorObject, Point{45, 10 }, Point{65, 15 }, Point{50, 5 }, static_cast<int>('9'));
    MacroRecorderPtr->AddCommand(DrawTriangleCommandPtr);

    CanvasObject.AddShapeCommand(MacroRecorderPtr);

    CanvasObject.DrawCanvas();

    CommandPtr DrawTriangleCommandPtr1 = std::make_shared<DrawTriangleCommand>(DrawingProcessorObject, Point{28, 10 }, Point{65, 15 }, Point{50, 5 }, static_cast<int>('9'));
    CanvasObject.AddShapeCommand(DrawTriangleCommandPtr1);

    CommandPtr DrawCircleCommandPtr1 = std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 50, 5 }, 7, static_cast<int>('2'));
    CanvasObject.AddShapeCommand(DrawCircleCommandPtr1);

    CommandPtr DrawRectangleCommandPtr1 = std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, Point{85, 10 }, 5, 5, static_cast<int>('4'));
    CanvasObject.AddShapeCommand(DrawRectangleCommandPtr1);

    CanvasObject.DrawCanvas();

    CanvasObject.UndoLastCommand();

    CanvasObject.DrawCanvas();

    CanvasObject.UndoLastCommand();

    CanvasObject.DrawCanvas();

    return 0;
}
