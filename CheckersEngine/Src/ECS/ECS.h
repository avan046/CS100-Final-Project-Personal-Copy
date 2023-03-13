#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponenets = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponenets>;
using GroupBitset = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponenets>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector <std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componenetBitSet;
	GroupBitset groupBitset;

public:
	Entity(Manager& mManager): manager(mManager){}
	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw()
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() const{ return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}

	template <typename T> bool hasComponenet() const
	{
		return componenetBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		auto c = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
		c->entity = this;

		T& result = *c;
		components.push_back(std::move(c));

		componentArray[getComponentTypeID<T>()] = &result;
		componenetBitSet[getComponentTypeID<T>()] = true;

		result.init();
		return result;

	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	

};

class Manager
{
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		auto e = std::make_unique<Entity>(*this);
		Entity& result = *e;
		entities.push_back(std::move(e));
		return result;
	}
};