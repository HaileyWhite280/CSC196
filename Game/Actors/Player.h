#pragma once
#include "Base/Actor.h"

class Player : public nc::Actor
{
public:
	Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer = 0;
	float fireRate = 0.2f;
	float speed = 1000;
	nc::Vector2 velocity;

	float immuneRate = 1.0f;
	float immunityTime = immuneRate;
};