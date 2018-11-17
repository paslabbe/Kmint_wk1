#pragma once
#include "kmint/map/map.hpp"
#include "PriorityQueue.h"
#include <map>

//#include "kmint/play/map.hpp"

class dijkstra
{
	kmint::map::map_graph& graph_;
public:
	dijkstra(kmint::map::map_graph& graph) : graph_(graph)
	{
	}

	PriorityQueue<const kmint::map::map_node*, double> dijkstra_search(
		const kmint::map::map_node& start, const kmint::map::map_node& goal,
		std::map<const kmint::map::map_node*, const kmint::map::map_node*>& came_from,
		std::map<const kmint::map::map_node*, double>& cost_so_far);

private:
	//double heuristic(kmint::math::vector2d& a, kmint::math::vector2d& b);

	/*PriorityQueue<kmint::map::map_node*, double> astarsearch(kmint::map::map_node* start, kmint::map::map_node* goal,
		std::map<kmint::map::map_node*, kmint::map::map_node*>&
		came_from,
		std::map<kmint::map::map_node*, double>& cost_so_far);*/
};

