#pragma once

#include "Shape.h"

#include <ranges>
#include <vector>

class CompositeDrawShapeCommand final : public UndoableDrawShapeCommand
{
public:
    explicit CompositeDrawShapeCommand(const int ColorParam, const int SizeParam, const Point PositionParam) : UndoableDrawShapeCommand(ColorParam, SizeParam, PositionParam)
    {
    }
public:
    void AddCommand(const DrawShapeCommandPtr& Command)
    {
        Commands.push_back(Command);
    }

    bool Execute() override
    {
        bool Result = false;

        for (const auto& Command : Commands)
        {
            if (SetShapeColorToSubShape)
                Command->SetColor(Color_);
            if (SetShapeSizeToSubShape)
                Command->SetSize(Size_);
            if (SetShapePositionToSubShape)
                Command->AddPosition(Position_);

            if (Command->Execute())
                Result = true;
        }

        return Result;
    }

    void Undo() override
    {
        const auto& CommandsInReverseOrder = std::ranges::reverse_view(Commands);

        for (const auto& Command : CommandsInReverseOrder)
            Command->Undo();
    }

    void UndoLastCommand()
    {
        if (Commands.empty())
            return;

        Commands.back()->Undo();
        Commands.pop_back();
    }

    DrawShapeCommandPtr GetCommand(uint64_t ShapeNumber)
    {
        if (ShapeNumber < Commands.size())
            return Commands[ShapeNumber];
        else
            return nullptr;
    }

private:
    std::vector<DrawShapeCommandPtr> Commands;
};
