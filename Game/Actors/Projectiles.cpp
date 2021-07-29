#include "Projectiles.h"
#include "Engine.h"

void Projectiles::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	if (lifetime <= 0) destroy = true;

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * speed * dt; //fix
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::blue };
	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 30, 0.5, colors[nc::randomRangeInt(0, colors.size())], 10);
}