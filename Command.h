#pragma once

#include <memory>

class Command
{
public:
    virtual ~Command() = default;
    virtual bool Execute() = 0;
};

class Revertable
{
public:
    virtual ~Revertable() = default;
    virtual void Undo() = 0;
};

class UndoableCommand : public Command, public Revertable
{
};

using CommandPtr = std::shared_ptr<UndoableCommand>;
