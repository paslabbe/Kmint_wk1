#include "kmint/main.hpp"          // voor de main loop
#include "kmint/graphics.hpp"      // kleuren en afbeeldingen
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
#include "hello_actor.h"
#include "kmint/map/map.hpp"
#include "cow.h"
#include "hare.h"
#include "dijkstra.h"

using namespace kmint; // alles van libkmint bevindt zich in deze namespace

PriorityQueue<const kmint::map::map_node*, double> queue;

const map::map_node &find_cow_node(const map::map_graph &graph) {
	for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
		if (graph[i].node_info().kind == 'C') {
			return graph[i];
		}
	}
	throw "could not find starting point";
}

int main()
{
	// een app object is nodig om
	ui::app app{};

	//  maak een venster aan
	ui::window window{ app.create_window({1024, 768}, "hello") };

	// maak een podium aan
	play::stage s{};

	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};

	//Create map description
	static const char* map_description =
		R"graph(32 24 32
	resources/firstmap.png
	G 1 1
	C 1 1
	H 1 1
	W 0 0
	B 1 8

	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
	WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
	WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
	WWWGGGGGBBBBBBBGCGGGGGGGGGGGGWWW
	WWWGGGGGGWWWWWGGGGWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWGGBGWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGWWWWWWWBWWWWWWGGGGGGWWW
	WWWGGGGGGGGGGGGGBGGGGGGGGGGGGWWW
	WWWGGGGGGGGGGGGGGGGGGGGGGGGGGWWW
	WWWHGGGGGGGGGGGGGGGGGGGGGGGGHWWW
	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	)graph";

	//Create map
	map::map m{ map::read_map(map_description) };

	//Define graph
	auto &graph = m.graph();

	//Create background
	s.build_actor<play::background>(
		math::size(1024, 768),
		graphics::image{ m.background_image() });

	//Create grid
	s.build_actor<play::map_actor>(
		math::vector2d{ 0.0f, 0.0f },
		m.graph());

	//Create playable actor in center
	math::vector2d center{ 512.0, 384.0 };
	auto& my_actor = s.build_actor<hello_actor>(center);

	//Create dijkstra
	dijkstra dijkstra{ graph };

	//create cow
	auto &cow_node = find_cow_node(m.graph());
	auto &my_cow = s.build_actor<cow>(m.graph(), cow_node, dijkstra);

	//create hare
	auto &my_hare = s.build_actor<hare>(m.graph());
	my_hare.set_cow(my_cow);
	my_cow.set_hare_location(my_hare.node());

	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls& ctl)
	{
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.
		for (ui::events::event& e : event_source)
		{
			// event heeft een methjode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//

			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
			e.handle_key_up([&my_actor](ui::events::key_event k)
			{
				switch (k.key)
				{
				case ui::events::key::up:
					my_actor.move({ 0, -5.0f });
					break;
				case ui::events::key::down:
					my_actor.move({ 0, 5.0f });
					break;
				case ui::events::key::left:
					my_actor.move({ -5.0f, 0 });
					break;
				case ui::events::key::right:
					my_actor.move({ 5.0f, 0 });
					break;
				default:
					break;
				}
			});
		}
	});
}



