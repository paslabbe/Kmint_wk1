#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

class cow;

class hare : public kmint::play::map_bound_actor {
	kmint::play::image_drawable drawable_;
	cow *cow_;
public:
	hare(kmint::map::map_graph const &g);
	void act(kmint::delta_time dt) override;
	kmint::ui::drawable const &drawable() const override { return drawable_; }
	void set_cow(cow &c) { cow_ = &c; }
	bool incorporeal() const override { return false; }
	kmint::scalar radius() const override { return 16.0; }
};