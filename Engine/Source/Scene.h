#pragma once

#include <memory>
#include <list>

class Renderer;
class Actor;

class Scene
{
public:
	Scene() = default;

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);

	void RemoveAll();

	template<typename T>
	T* GetActor();
	
protected:
	std::list<std::unique_ptr<Actor>> m_actors;

private:

};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}

	return nullptr;
}
