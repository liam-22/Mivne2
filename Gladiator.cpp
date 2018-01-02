#include<cstdlib>
#include "Gladiator.h"

Gladiator :: Gladiator() : ID(0), level(0),pTrainer(NULL){}

Gladiator::Gladiator(int ID, int level, Trainer* pTrainer)
{
    SetID(ID);
    SetLevel(level);
    SetTrainer(pTrainer);
}

Gladiator::Gladiator(const Gladiator& glad): ID(glad.ID), level(glad.level),pTrainer(glad.pTrainer){}

void Gladiator::SetID(int ID)
{
    this->ID=ID;
}
void Gladiator::SetLevel(int level)
{
    this->level=level;
}
void Gladiator::SetTrainer( Trainer* pTrainer)
{
    this->pTrainer=pTrainer;
}
