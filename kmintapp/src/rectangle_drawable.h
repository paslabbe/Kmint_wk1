#pragma once
#include "kmint/ui/window.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/ui/drawable.hpp"

class rectangle_drawable : public kmint::ui::drawable {

	kmint::play::actor const *actor_;
public:
	rectangle_drawable(kmint::play::actor const &actor) : drawable{}, actor_{ &actor } {}
	void draw(kmint::ui::frame &f) const override;
};
