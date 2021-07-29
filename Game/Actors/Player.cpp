#include "Player.h"
#include "Projectiles.h"
#include "Engine.h"
#include "Enemy.h"
#include <memory>

Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed }
{

}

void Player::Initialize()
{
	std::unique_ptr engine = std::make_unique<Actor>(nc::Transform{}, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("engine.txt"));
	engine->transform.localPosition = nc::Vector2{ 8 , 0 }; //position of projectile
	AddChild(std::move(engine));

	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ -8 , 0 }; //position of projectile
	locator->transform.localRotation = nc::DegToRad(180);
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0 , 5 }; //position of projectile
	AddChild(std::move(locator));

	locator = std::make_unique<Actor>();
	locator->transform.localPosition = nc::Vector2{ 0 , -5 }; //position of projectile
	AddChild(std::move(locator));
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//rotates constantly
	children[0]->transform.localRotation += 10 * dt;

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= -5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	if (Core::Input::IsPressed(VK_SHIFT)) thrust *= 2;

	nc::Vector2 acceleration = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust;
	velocity += acceleration * dt;

	//pulls to center (doesnt work)
	//nc::Vector2 gravity = (nc::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	//nc::Vector2 gravity = nc::Vector2::down * 200;
	//acceleration += gravity;

	velocity *= 0.99f;

	transform.position += velocity * dt;
	transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

	fireTimer -= dt;
	immunityTime -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;

		{
		std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
		std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>(points, nc::Color{ 17, 16, 25 });

		nc::Transform t = children[1]->transform;
		t.scale = 0.5;

		std::unique_ptr<Projectiles> projectile = std::make_unique<Projectiles>(t, shape, 200); // engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("projectile.txt")
		projectile->tag = "Player";
		scene->AddActor(std::move(projectile));
		}

		//double bullets
		//{
		//	std::vector<nc::Vector2> points = { {-5, -5}, {5, -5}, {0, 5}, {-5, -5} };
		//	std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>(points, nc::Color{ 17, 16, 25 });

		//	nc::Transform t = children[2]->transform;
		//	t.scale = 0.5;

		//	std::unique_ptr<Projectiles> projectile = std::make_unique<Projectiles>(t, shape, 100); // engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("projectile.txt")
		//	projectile->tag = "Player";
		//	scene->AddActor(std::move(projectile));
		//}

		scene->engine->Get<nc::AudioSystem>()->PlayAudio("PlayerShoot");

	}

	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::purple };

	//scene->engine->Get<nc::ParticleSystem>()->Create(children[1]->transform.position, 3, 2, colors , 50, children[1]->transform.rotation, nc::DegToRad(30));
}

void Player::OnCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor) && immunityTime <= 0)
	{
		//destroy = true;
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 1, nc::Color::purple, 50);
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");

		nc::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes I died");
		scene->engine->Get<nc::EventSystem>()->Notify(event);
		immunityTime = immuneRate;
	}
}
