#include "dijkstra.h";
#include <map>
#include "PriorityQueue.h"
#include <windows.h>
#include "kmint/graph/graph.hpp"

double dijkstra::heuristic(kmint::math::vector2d& a, kmint::math::vector2d& b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

PriorityQueue<kmint::map::map_node*, double> dijkstra::dijkstraSearch
(kmint::map::map_node* start,
 kmint::map::map_node* goal,
 std::map<kmint::map::map_node*, kmint::map::map_node*>& came_from,
 std::map<kmint::map::map_node*, double>& cost_so_far)
{
	PriorityQueue<kmint::map::map_node*, double> queue;
	queue.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!queue.empty()) {
		kmint::map::map_node* current = queue.get();
		
		if (current->node_id() == goal->node_id()) {
			break;
		}

		for (int i = 0; i < current->num_edges(); i++)
		{
			kmint::map::map_node& curr = *current;
			auto &edge = curr[i];
			float weight = edge.weight();
			
			double new_cost = cost_so_far[current] + weight;
		
			auto next = static_cast<kmint::map::map_node*>(std::addressof(current[i]));
			next->tagged(true);
		
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				queue.put(next, new_cost);
			}
		}
	}
	return queue;
}

PriorityQueue<kmint::map::map_node*, double> dijkstra::astarsearch
(kmint::map::map_node* start,
	kmint::map::map_node* goal,
	std::map<kmint::map::map_node*, kmint::map::map_node*>& came_from,
	std::map<kmint::map::map_node*, double>& cost_so_far)
{
	PriorityQueue<kmint::map::map_node*, double> queue;
	queue.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!queue.empty()) {
		kmint::map::map_node* current = queue.get();

		if (current->node_id() == goal->node_id()) {
			break;
		}

		for (int i = 0; i < current->num_edges(); i++)
		{
			kmint::map::map_node& curr = *current;
			auto &edge = curr[i];
			float weight = edge.weight();

			double new_cost = cost_so_far[current] + weight;

			auto next = static_cast<kmint::map::map_node*>(std::addressof(current[i]));
			next->tagged(true);

			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				came_from[next] = current;
				//this is added
				double priority = new_cost + heuristic(next->location(), goal->location());
				//------------
				queue.put(next, new_cost);
			}
		}
	}
	return queue;
}
