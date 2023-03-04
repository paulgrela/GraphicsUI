
#include "CommandProcessor.h"
#include "CompositeCommand.h"
#include "DrawCircleCommand.h"
#include "DrawRectangleCommand.h"
#include "DrawingProcessor.h"

int main()
{
    CommandProcessor CommandProcessorObject{ };

    Canvas CanvasObject{ 20, 100 };
    CanvasObject.DrawCanvas();
    DrawingProcessor DrawingProcessorObject{ CanvasObject };

    auto MacroRecorderPtr = std::make_shared<CompositeCommand>();

    Point CircleCenterPoint{ 20, 20 };
    CommandPtr DrawCircleCommandPtr = std::make_shared<DrawCircleCommand>(DrawingProcessorObject, CircleCenterPoint, 10);
    CommandProcessorObject.Execute(DrawCircleCommandPtr);
    MacroRecorderPtr->AddCommand(DrawCircleCommandPtr);

    Point RectangleCenterPoint{ 30, 10 };
    CommandPtr DrawRectangleCommandPtr = std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, RectangleCenterPoint, 5, 8);
    CommandProcessorObject.Execute(DrawRectangleCommandPtr);
    MacroRecorderPtr->AddCommand(DrawRectangleCommandPtr);

    CommandProcessorObject.Execute(MacroRecorderPtr);
    CommandProcessorObject.UndoLastCommand();

  return 0;
}
