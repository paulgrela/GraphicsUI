#pragma once

#include "Command.h"
#include <stack>

class CommandProcessor
{
public:
    bool Execute(const CommandPtr& Command)
    {
        if (Command->Execute())
        {
            CommandHistory.push(Command);
            return true;
        }

        return false;
    }

    void UndoLastCommand()
    {
        if (CommandHistory.empty())
            return;

        CommandHistory.top()->Undo();
        CommandHistory.pop();
    }

private:
    std::stack<std::shared_ptr<Revertable>> CommandHistory;
};
