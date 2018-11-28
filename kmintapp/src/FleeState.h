#pragma once
#include "IState.h"
#include "WanderingState.h"
#include "hare.h"

class FleeState : IState
{
public:
	FleeState(hare& hare) : hare(hare){}
	void act(kmint::delta_time dt) override;
	void next(kmint::delta_time dt) override;
private:
	hare& hare;
};
