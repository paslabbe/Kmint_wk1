#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "IState.h"

class cow;

class hare : public kmint::play::map_bound_actor {
	kmint::play::image_drawable drawable_;
	cow *cow_;
	IState currentState;
	int view_range;
public:
	hare(kmint::map::map_graph const &g);
	hare(kmint::map::map_graph const& g, IState state);
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const &drawable() const override { return drawable_; }
	void set_cow(cow &c) { cow_ = &c; }
	bool incorporeal() const override { return false; }
	kmint::scalar radius() const override { return 16.0; }
};