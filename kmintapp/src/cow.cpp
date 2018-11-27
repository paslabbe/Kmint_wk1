#include "cow.h"
using namespace kmint;

static const char *cow_image = "resources/cow.png";
cow::cow(map::map_graph const &g, map::map_node const &initial_node, dijkstra& dijkstra)
	: kmint::play::map_bound_actor{g, initial_node}, drawable_{*this, kmint::graphics::image{cow_image, 0.1}},
	  dijkstra_{&dijkstra}
{
}

void cow::act(delta_time dt) {
	t_passed_ += dt;
	if (to_seconds(t_passed_) >= 0.1) {
		if (!path_.empty()) {
			for(size_t i = 0; i < this->node().num_edges(); i++)
			{
				const auto neighbor = this->node()[i].to().node_id();
				const auto path = path_.front()->node_id();
				if(neighbor == path)
				{
					this->node(node()[i].to());
					break;
				}
			}
			
			path_.pop();
			t_passed_ = from_seconds(0);
		}
		else
		{
			set_path();
		}
	}
}

void cow::set_path()
{
	path_ = dijkstra_->a_star_search(node(), *hare_location_);
}
