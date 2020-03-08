#include "Scene.h"

namespace ToyRenderer {
    Scene::Scene()
	{
		renderer = new Renderer();
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
}
