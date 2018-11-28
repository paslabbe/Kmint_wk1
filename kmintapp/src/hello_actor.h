#pragma once
#include "rectangle_drawable.h"
#include "kmint/play/free_roaming_actor.hpp"

class hello_actor : public kmint::play::free_roaming_actor {

	rectangle_drawable drawable_;
public:
	hello_actor(kmint::math::vector2d location)
		: kmint::play::free_roaming_actor{ location }, drawable_{ *this } {}

	const kmint::ui::drawable& drawable() const override;
	void move(kmint::math::vector2d delta);
};
