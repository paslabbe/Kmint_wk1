#include "kmint/ui/drawable.hpp"
#include "hello_actor.h"

const kmint::ui::drawable& hello_actor::drawable() const
{
	return drawable_;
}

void hello_actor::move(kmint::math::vector2d delta)
{
	location(location() + delta);
}
