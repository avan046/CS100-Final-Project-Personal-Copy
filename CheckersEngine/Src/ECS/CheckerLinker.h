#pragma once
#include "ECS.h"
#include "Components.h"

#include "../Game.h"
#include "../GameLogic/GameLogic.h"
#include <iostream>
using namespace std;


class CheckerLinker : public Component
{
private:
    Checker* piece;
    
public:


    CheckerLinker(Checker* piece)
    {
        this->piece = piece;
    }

    Checker* getPiece() const
    {
        return piece;
    }
};
