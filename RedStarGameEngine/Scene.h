#pragma once

namespace rsge
{
	class Scene
	{
	public:
		Scene(std::string pathToScene, std::string pathToObjects) : mPathToScene(pathToScene), mPathToObjects(pathToObjects) {}
		Scene() {}
		void setPathToScene(std::string pathToScene) { mPathToScene = pathToScene; }
		void setPathToObjects(std::string pathToObjects) { mPathToObjects = pathToObjects; }
		void loadObjects();
		void clear();
		std::vector<Object*>& getObjects() { return mObjects; }
		Object*& operator [](std::string id)
		{
			for (Object*& object : mObjects) {

				if (object->getId() == id)
					return object;
			}
		}

	private:
		std::string mPathToScene;
		std::string mPathToObjects;
		std::vector<Object*> mObjects;
	protected:
	};
}