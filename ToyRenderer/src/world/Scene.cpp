#include "Scene.h"

namespace ToyRenderer {
    Scene::Scene()
	{
		renderer = new Renderer();
	}
	Scene::~Scene()
	{
		for (std::vector<GameObject*>::iterator i = sceneObjects.begin(); i != sceneObjects.end(); ++i)
			delete *i;
		sceneObjects.clear();
	}
	void Scene::OnStart() const
	{
		for (std::vector<GameObject*>::size_type i = 0; i != sceneObjects.size(); i++) {

			sceneObjects[i]->OnStart();
		}
	}
	void Scene::OnUpdate(float deltaTime) const
	{
		for (std::vector<GameObject*>::size_type i = 0; i != sceneObjects.size(); i++) {
			
			sceneObjects[i]->OnUpdate(deltaTime);
		}

	}
	void Scene::OnRender() const
	{
		for (std::vector<GameObject*>::size_type i = 0; i != sceneObjects.size(); i++) {

			sceneObjects[i]->OnRender();
		}
	}
	void Scene::OnGUI() const
	{
		for (std::vector<GameObject*>::size_type i = 0; i != sceneObjects.size(); i++) {

			sceneObjects[i]->OnGUI();
		}
	}
	void Scene::AddGameObject(GameObject* toAdd)
	{
		sceneObjects.push_back(toAdd);
	}
}
