#include "dijkstra.h";
#include <map>
#include "PriorityQueue.h"
#include <windows.h>
#include "kmint/graph/graph.hpp"
#include "kmint/play/map.hpp"
#include "kmint/ui/events/event.hpp"

void dijkstra::dijkstra_search
(const kmint::map::map_node& start,
	const kmint::map::map_node& goal,
	std::map<const kmint::map::map_node*, const kmint::map::map_node*>& came_from,
	std::map<const kmint::map::map_node*, double>& cost_so_far)
{
	PriorityQueue<const kmint::map::map_node*, double> queue;
	queue.put(&start, 0);

	came_from[&start] = &start;
	cost_so_far[&start] = 0;

	graph_.untag_all();
	while (!queue.empty()) {
		const kmint::map::map_node& current = *queue.get();
		graph_[current.node_id()].tagged(true);

		if (current.node_id() == goal.node_id()) {
			break;
		}

		for (size_t i = 0; i < current.num_edges(); i++)
		{
			const float weight = current[i].weight();
			const double new_cost = cost_so_far[&current] + weight;
			const kmint::map::map_node& neighbor = current[i].to();

			if (cost_so_far.find(&neighbor) == cost_so_far.end()
				|| new_cost < cost_so_far[&neighbor]) {
				cost_so_far[&neighbor] = new_cost;
				queue.put(&neighbor, new_cost);
				came_from[&neighbor] = &current;
			}
		}
	}
}

std::vector<const kmint::map::map_node*> dijkstra::reconstruct_path(const kmint::map::map_node* start,
	const kmint::map::map_node* goal, std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from)
{
	std::vector<const kmint::map::map_node*> path;
	const kmint::map::map_node* current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // optional
	std::reverse(path.begin(), path.end());
	return path;
}

void dijkstra::a_star_search
(const kmint::map::map_node& start,
	const kmint::map::map_node& goal,
	std::map<const kmint::map::map_node*, const kmint::map::map_node*>& came_from,
	std::map<const kmint::map::map_node*, double>& cost_so_far)
{
	PriorityQueue<const kmint::map::map_node*, double> queue;
	queue.put(&start, 0);

	came_from[&start] = &start;
	cost_so_far[&start] = 0;

	graph_.untag_all();
	while (!queue.empty()) {
		const kmint::map::map_node& current = *queue.get();
		graph_[current.node_id()].tagged(true);
		
		if (current.node_id() == goal.node_id()) {
			break;
		}

		for (size_t i = 0; i < current.num_edges(); i++)
		{
			const float weight = current[i].weight();
			const double new_cost = cost_so_far[&current] + weight;
			const kmint::map::map_node& neighbor = current[i].to();

			if (cost_so_far.find(&neighbor) == cost_so_far.end()
				|| new_cost < cost_so_far[&neighbor]) {
				cost_so_far[&neighbor] = new_cost;
				double priority = new_cost + heuristic(neighbor, goal);
				queue.put(&neighbor, priority);
				came_from[&neighbor] = &current;
			}
		}
	}
}

double dijkstra::heuristic(const kmint::map::map_node& a, const kmint::map::map_node& b)
{
	return std::abs(a.location().x() - b.location().x()) + std::abs(a.location().y() - b.location().y());
}



