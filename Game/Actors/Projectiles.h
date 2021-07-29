#pragma once
#include "Base/Actor.h"

class Projectiles : public nc::Actor
{
public:
	Projectiles(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 1 };
	float speed = 300;
};