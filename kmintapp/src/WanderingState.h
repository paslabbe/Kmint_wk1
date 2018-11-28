#pragma once
#include "IState.h"
#include "hare.h"

class WanderingState : IState
{
public:
	WanderingState(hare& hare): hare(hare){}
	void act(kmint::delta_time dt) override;
	void next(kmint::delta_time dt) override;
private:
	hare& hare;
};
