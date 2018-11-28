#include "FleeState.h"
#include "kmint/graph/graph.hpp"
#include <chrono>

void FleeState::next(kmint::delta_time dt)
{
	WanderingState wanderingState(hare);
	wanderingState.act(dt);
}

void FleeState::act(kmint::delta_time dt)
{
	for (std::size_t i = 0; i < num_colliding_actors(); ++i) {
		auto &a = colliding_actor(i);
		if (&a == cow_) {
			kmint::graph::node(random_hare_node(kmint::graph::graph()));
			cow_->set_hare_location(kmint::graph::node());
		}
	}
}
