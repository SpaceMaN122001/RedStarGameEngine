#include "Engine.h"

namespace rsge
{
	void Scene::loadObjects()
	{
		std::vector<std::string> objectFromSceneList;
		std::ifstream sceneFile(mPathToScene);
		std::string line = SNULL;

		sceneFile.is_open();

		while (std::getline(sceneFile, line)) {

			int lineIndex = 0;
			std::string objectId = SNULL;

			for (char symbol : line) {

				if (lineIndex >= 8) {

					objectId += symbol;
				}

				lineIndex++;
			}

			objectId.erase(std::remove(objectId.begin(), objectId.end(), ' '), objectId.end());
			objectFromSceneList.push_back(objectId);
		}

		sceneFile.close();

		for (std::string& value : objectFromSceneList) {

			Object* object = new Object();
			object->setTextureFromFile(Object::getObjectProperty(mPathToObjects + "\\" + value + ".dat", "@Texture"));
			object->setPosition(std::stoi(Object::getObjectProperty(mPathToObjects + "\\" + value + ".dat", "@XPos")), std::stoi(Object::getObjectProperty(mPathToObjects + "\\" + value + ".dat", "@YPos")));
			object->setId(Object::getObjectProperty(mPathToObjects + "\\" + value + ".dat", "@Id"));

			if (Object::getObjectProperty(mPathToObjects + "\\" + value + ".dat", "@IsRender") == "False")
				object->setRenderState(false);

			/*std::cout << object->getId() << std::endl;
			std::cout << object->getPathToTexture() << std::endl;
			std::cout << object->getPosition().x << std::endl;
			std::cout << object->getPosition().y << std::endl;*/

			mObjects.push_back(object);
		}
	}

	void Scene::clear()
	{
		for (Object*& object : mObjects) {

			delete object;
		}

		mObjects.clear();
	}
}