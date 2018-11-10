#pragma once
#include "kmint/map/map.hpp"
#include <map>
#include "PriorityQueue.h"
#include "kmint/play/map.hpp"

class dijkstra
{
public:


private:
	double heuristic(kmint::math::vector2d& a, kmint::math::vector2d& b);
	PriorityQueue<kmint::map::map_node*, double> dijkstraSearch(
		kmint::map::map_node* start, kmint::map::map_node* goal,
		std::map<kmint::map::map_node*, kmint::map::map_node*>& came_from,
		std::map<kmint::map::map_node*, double>& cost_so_far);
	PriorityQueue<kmint::map::map_node*, double> astarsearch(kmint::map::map_node* start, kmint::map::map_node* goal,
	                                                         std::map<kmint::map::map_node*, kmint::map::map_node*>&
	                                                         came_from,
	                                                         std::map<kmint::map::map_node*, double>& cost_so_far);
};
