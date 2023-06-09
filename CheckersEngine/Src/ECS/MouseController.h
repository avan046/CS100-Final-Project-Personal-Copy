#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class MouseController : public Component
{
public:
	TransformComponent* transform;
	ColliderComponent* collider;
	bool isMouseDragging;
	int lastMouseX, lastMouseY;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		collider = &entity->getComponent<ColliderComponent>();
		isMouseDragging = false;
		lastMouseX = 0;
		lastMouseY = 0;
	}

	void update() override
	{
		bool isMouseOver = isMouseWithinComponent();

		if (isMouseOver && Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			isMouseDragging = true;
			lastMouseX = Game::event.button.x;
			lastMouseY = Game::event.button.y;
		}

		if (Game::event.type == SDL_MOUSEBUTTONUP)
		{
			isMouseDragging = false;
		}

		if (isMouseDragging && Game::event.type == SDL_MOUSEMOTION)
		{
			int mouseX = Game::event.motion.x;
			int mouseY = Game::event.motion.y;
			int dx = mouseX - lastMouseX;
			int dy = mouseY - lastMouseY;
			transform->position.x += dx;
			transform->position.y += dy;
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}
	}

	bool isMouseWithinComponent(Entity* component)
	{
		
		int mouseX = Game::event.motion.x;
		int mouseY = Game::event.motion.y;
		int componentX = static_cast<int>(component->getComponent<TransformComponent>().position.x);
		int componentY = static_cast<int>(component->getComponent<TransformComponent>().position.y);
		int componentWidth = component->getComponent<TransformComponent>().width;
		int componentHeight = component->getComponent<TransformComponent>().height;

		return (mouseX >= componentX && mouseX < componentX + componentWidth &&
			mouseY >= componentY && mouseY < componentY + componentHeight);
	}

private:
	bool isMouseWithinComponent() const
	{
		int mouseX = Game::event.motion.x;
		int mouseY = Game::event.motion.y;
		int componentX = static_cast<int>(transform->position.x);
		int componentY = static_cast<int>(transform->position.y);
		int componentWidth = transform->width;
		int componentHeight = transform->height;

		return (mouseX >= componentX && mouseX < componentX + componentWidth &&
			mouseY >= componentY && mouseY < componentY + componentHeight);
	}

	
	
};