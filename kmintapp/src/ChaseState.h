#pragma once
#include "IState.h"
#include "cow.h"

class ChaseState : IState
{
	public:
	ChaseState(cow& cow) : cow(cow){}
		void act(kmint::delta_time dt) override;
		void next(kmint::delta_time dt) override;
private:
	cow& cow;
};
