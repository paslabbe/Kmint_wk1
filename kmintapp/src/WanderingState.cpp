#include "WanderingState.h";
#include "FleeState.h"
#include <chrono>

void WanderingState::act(kmint::delta_time dt)
{
}

void WanderingState::next(kmint::delta_time dt)
{
	FleeState fleeState(this->hare);
	fleeState.act(dt);
}
