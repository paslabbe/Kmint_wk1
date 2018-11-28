#include "ChaseState.h";
#include "kmint/graph/graph.hpp"
#include <chrono>
#include <chrono>
#include <chrono>
#include <chrono>
#include <chrono>
#include <chrono>
#include <chrono>

void ChaseState::act(kmint::delta_time dt)
{
	cow.t_passed_ += dt;
	if (kmint::to_seconds(cow.t_passed_) >= 0.1) {
		if (!cow.path_.empty()) {
			for (size_t i = 0; i < cow.node().num_edges(); i++)
			{
				const auto neighbor = cow.node()[i].to().node_id();
				const auto path = cow.path_.front()->node_id();
				if (neighbor == path)
				{
					cow.node(cow.node()[i].to());
					break;
				}
			}

			cow.path_.pop();
			cow.t_passed_ = kmint::from_seconds(0);
		}
		else
		{
			cow.set_path();
		}
	}
}

void ChaseState::next(kmint::delta_time dt)
{
	//not implemented
}
