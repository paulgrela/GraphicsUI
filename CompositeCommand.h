#pragma once

#include "Command.h"
#include <ranges>
#include <vector>

class CompositeCommand final : public UndoableCommand
{
public:
    void AddCommand(CommandPtr& Command)
    {
        Commands.push_back(Command);
    }

    void Execute() override
    {
        for (const auto& Command : Commands)
            Command->Execute();
    }

    void Undo() override
    {
        const auto& CommandsInReverseOrder = std::ranges::reverse_view(Commands);
        for (const auto& Command : CommandsInReverseOrder)
            Command->Undo();
    }

private:
    std::vector<CommandPtr> Commands;
};
