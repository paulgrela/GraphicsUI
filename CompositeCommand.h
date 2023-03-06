#pragma once

#include "Command.h"
#include <ranges>
#include <vector>

class CompositeCommand final : public UndoableCommand
{
public:
    void AddCommand(const CommandPtr& Command)
    {
        Commands.push_back(Command);
    }

    bool Execute() override
    {
        bool Result = false;

        for (const auto& Command : Commands)
            if (Command->Execute())
                Result = true;

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

private:
    std::vector<CommandPtr> Commands;
};
