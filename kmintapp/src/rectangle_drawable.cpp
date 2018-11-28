#include "kmint/graphics/color.hpp"
#include "kmint/ui/window.hpp"
#include "rectangle_drawable.h"

void rectangle_drawable::draw(kmint::ui::frame &f) const {
	f.draw_rectangle(actor_->location(), { 10.0, 10.0 }, kmint::graphics::colors::white);
}
