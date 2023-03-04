#pragma once

#include "Command.h"
#include <stack>

class CommandProcessor
{
public:
    void Execute(const CommandPtr& Command)
    {
        Command->Execute();
        CommandHistory.push(Command);
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
