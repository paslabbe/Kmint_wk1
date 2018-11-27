#include "dijkstra.h"
#include <map>
#include "PriorityQueue.h"
#include "kmint/graph/graph.hpp"
#include <stack>

std::queue<const kmint::map::map_node*> dijkstra::dijkstra_search(
	const kmint::map::map_node& start, const kmint::map::map_node& goal) const
{
	PriorityQueue<const kmint::map::map_node*, double> queue;
	std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from;
	std::map<const kmint::map::map_node*, double> cost_so_far;
	queue.put(&start, 0);

	came_from[&start] = &start;
	cost_so_far[&start] = 0;

	while (!queue.empty()) {
		const kmint::map::map_node& current = *queue.get();

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

	return reconstruct_path(&start, &goal, came_from);
}

std::queue<const kmint::map::map_node*> dijkstra::a_star_search(const kmint::map::map_node& start,
	const kmint::map::map_node& goal) const
{
	PriorityQueue<const kmint::map::map_node*, double> queue;
	std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from;
	std::map<const kmint::map::map_node*, double> cost_so_far;
	queue.put(&start, 0);

	came_from[&start] = &start;
	cost_so_far[&start] = 0;

	while (!queue.empty()) {
		const kmint::map::map_node& current = *queue.get();

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
				const double priority = new_cost + heuristic(neighbor, goal);
				queue.put(&neighbor, priority);
				came_from[&neighbor] = &current;
			}
		}
	}

	return reconstruct_path(&start, &goal, came_from);
}

std::queue<const kmint::map::map_node*> dijkstra::reconstruct_path(
	const kmint::map::map_node* start,
	const kmint::map::map_node* goal,
	std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from) const
{
	std::queue<const kmint::map::map_node*> path;
	const kmint::map::map_node* current = goal;
	while (current != start) {
		path.push(current);
		current = came_from[current];
	}

	std::stack<const kmint::map::map_node*> stack;
	graph_.untag_all();
	while (!path.empty()) {
		graph_[path.front()->node_id()].tagged(true);
		stack.push(path.front());
		path.pop();
	}
	while (!stack.empty()) {
		path.push(stack.top());
		stack.pop();
	}

	return path;
}

double dijkstra::heuristic(const kmint::map::map_node& a, const kmint::map::map_node& b) const
{
	return std::abs(a.location().x() - b.location().x()) + std::abs(a.location().y() - b.location().y());
}



