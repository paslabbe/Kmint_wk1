#include "cow.h"
using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(map::map_graph const &g, map::map_node const &initial_node, dijkstra& dijkstra, IState& state)
	: kmint::play::map_bound_actor{g, initial_node}, drawable_{*this, kmint::graphics::image{cow_image, 0.1}},
	  dijkstra_{&dijkstra}, currentState(state)
{
}

void cow::act(delta_time dt) {
	currentState.act(dt);
}

void cow::set_path()
{
	path_ = dijkstra_->a_star_search(node(), *hare_location_);
}
