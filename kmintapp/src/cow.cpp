#include "cow.h"
#include "kmint/random.hpp"
#include "PriorityQueue.h"
#include "kmint/graph/graph.hpp"
using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(map::map_graph const &g, map::map_node const &initial_node)
: play::map_bound_actor{ g, initial_node }, drawable_{ *this,
														kmint::graphics::image{
															cow_image, 0.1} } {}

void cow::act(delta_time dt, std::vector<const map::map_node*> path) {
	t_passed_ += dt;
	int next_index = 0;
	const map::map_node& current = this->node();

	while (!path.empty()) {
		for (int i = 0; i < current.num_edges(); i++)
		{
			if (current[i].to().node_id() == path.at(0)->node_id())
			{
				next_index = i;
				break;
			}
		}

		if (to_seconds(t_passed_) >= 1) {
			// pick random edge
			//int next_index = random_int(0, node().num_edges());
			this->node(node()[next_index].to());
			t_passed_ = from_seconds(0);
		}
		path.erase(path.begin(), path.begin() + 1);
	}
}