#include "Actor.h"
#include "Graphics/Shape.h"

namespace nc
{
	void Actor::Update(float dt)
	{
		transform.Update();
		std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
		
	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		if (shape)
		{
			shape->Draw(graphics, transform);
		}
		//Tiny Fighter
		std::for_each(children.begin(), children.end(), [graphics](auto& child) mutable { if (child->shape) child->shape->Draw(graphics, child->transform); });
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale.x;
	}

	void Actor::AddChild(std::unique_ptr<Actor> actor)
	{
		actor->parent = this;
		children.push_back(std::move(actor));
	}
}