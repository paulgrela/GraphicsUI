
#include "CommandProcessor.h"
#include "CompositeDrawShapeCommand.h"
#include "DrawShapesCommands.h"
#include "DrawingProcessor.h"
#include "DrawingCanvas.h"

int main()
{
    cout << blue << "Canvas created - size 100 x 20 filled with color '0'" << endl;

    Canvas CanvasObject{ 100, 20, static_cast<int>('0')};
    CanvasObject.Draw();

    DrawingProcessor DrawingProcessorObject{ CanvasObject };

    cout << blue << "Create one batch with 3 shapes as draw shape command nr 0" << endl;
    auto MacroRecorderPtr = std::make_shared<CompositeDrawShapeCommand>('3', 1, Point{1, 1});

    MacroRecorderPtr->AddCommand(std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 17, 7 }, 5, static_cast<int>('2')));
    MacroRecorderPtr->AddCommand(std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, Point{ 30, 10 }, 10, 5, static_cast<int>('4')));
    MacroRecorderPtr->AddCommand(std::make_shared<DrawTriangleCommand>(DrawingProcessorObject, Point{ 45, 10 }, Point{65, 15 }, Point{50, 5 }, static_cast<int>('9')));

    CanvasObject.AddShapeCommand(MacroRecorderPtr);

    CanvasObject.Draw();

    cout << blue << "Next shape will be not drawn since it collides with previous shapes" << endl;
    CanvasObject.AddShapeCommand(std::make_shared<DrawTriangleCommand>(DrawingProcessorObject, Point{ 28, 10 }, Point{65, 15 }, Point{50, 5 }, static_cast<int>('9')));

    cout << blue << "Next shape will be not drawn since it collides with previous shapes" << endl;
    CanvasObject.AddShapeCommand(std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 50, 5 }, 7, static_cast<int>('2')));

    cout << blue << "New shape will be drawn" << endl;
    CanvasObject.AddShapeCommand(std::make_shared<DrawCircleCommand>(DrawingProcessorObject, Point{ 85, 10 }, 5, static_cast<int>('4')));

    cout << blue << "New shape will be drawn" << endl;
    CanvasObject.AddShapeCommand(std::make_shared<DrawRectangleCommand>(DrawingProcessorObject, Point{ 93, 10 }, 4, 4, static_cast<int>('4')));

    CanvasObject.Draw();

    cout << blue << "Change color of shape 1" << endl;
    CanvasObject.ChangeSelectedShapeColor(1, static_cast<int>('1'));

    CanvasObject.Draw();

    cout << blue << "Change color of composed shape 0" << endl;
    CanvasObject.ChangeSelectedShapeColor(0, static_cast<int>('5'));

    CanvasObject.Draw();

    cout << blue << "Change position of shape 1" << endl;
    CanvasObject.ChangeSelectedShapePosition(1, { 75,7 });

    CanvasObject.Draw();

    cout << blue << "Change position of shape 2" << endl;
    CanvasObject.ChangeSelectedShapePosition(2, { 90,15 });

    CanvasObject.Draw();

    cout << blue << "Change position of composed shape 0" << endl;
    CanvasObject.ChangeSelectedShapePosition(0, { 3,3 });

    CanvasObject.Draw();

    cout << blue << "Change size of shape 1 - smaller circle" << endl;
    CanvasObject.ChangeSelectedShapeSize(1, 2);

    CanvasObject.Draw();

    cout << blue << "Undo last command" << endl;
    CanvasObject.UndoLastCommand();

    CanvasObject.Draw();

    cout << blue << "Undo last command" << endl;
    CanvasObject.UndoLastCommand();

    CanvasObject.Draw();

    cout << blue << "Undo last command" << endl;
    CanvasObject.UndoLastCommand();

    CanvasObject.Draw();

    return 0;
}
