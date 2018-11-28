#pragma once
#include "kmint/play/graph_bound_actor.hpp"

class IState
{
public:
	virtual ~IState() = default;
	virtual void next(kmint::delta_time dt);
	virtual void act(kmint::delta_time dt);
};
