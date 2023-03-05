
#include "CommandProcessor.h"
#include "CompositeCommand.h"
#include "DrawCircleCommand.h"
#include "DrawRectangleCommand.h"
#include "DrawTriangleCommand.h"
#include "DrawingProcessor.h"

int main()
{
    CommandProcessor CommandProcessorObject{ };

    Canvas CanvasObject{ 100, 20 };

    CanvasObject.DrawCanvas();

    DrawingProcessor DrawingProcessorObject{ CanvasObject };

    auto MacroRecorderPtr = std::make_shared<CompositeCommand>();

    CommandPtr DrawCircleCommandPtr = std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 17, 7 }, 5);
    CommandProcessorObject.Execute(DrawCircleCommandPtr);
    MacroRecorderPtr->AddCommand(DrawCircleCommandPtr);

    CanvasObject.DrawCanvas();

    CommandPtr DrawRectangleCommandPtr = std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, Point{30, 10 }, 10, 5);
    CommandProcessorObject.Execute(DrawRectangleCommandPtr);
    MacroRecorderPtr->AddCommand(DrawRectangleCommandPtr);

    CanvasObject.DrawCanvas();

    CommandPtr DrawTriangleCommandPtr = std::make_shared<DrawTriangleCommand>(DrawingProcessorObject, Point{50, 5 }, Point{45, 10 }, Point{65, 15 });
    CommandProcessorObject.Execute(DrawTriangleCommandPtr);
    MacroRecorderPtr->AddCommand(DrawTriangleCommandPtr);

    CanvasObject.DrawCanvas();

    CommandProcessorObject.Execute(MacroRecorderPtr);
    CommandProcessorObject.UndoLastCommand();

    return 0;
}
