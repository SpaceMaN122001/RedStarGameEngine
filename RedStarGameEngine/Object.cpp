#include "Engine.h"

namespace rsge
{
	void Object::setTextureFromFile(std::string pathToTexture)
	{
		mTexture.loadFromFile(pathToTexture);
		setTexture(mTexture);
		mPathToTexture = pathToTexture;
	}

	std::vector<std::string> Object::getObjectsList(std::string pathToObjects)
	{
		std::vector<std::string> objectNames;

		std::string filesFilter = "\\*.dat";
		pathToObjects += filesFilter;
		WIN32_FIND_DATA findFileData;
		HANDLE file = FindFirstFile(pathToObjects.c_str(), &findFileData);

		if (file != INVALID_HANDLE_VALUE) {

			do {

				std::string fileName(findFileData.cFileName);

				objectNames.push_back(fileName);

			} while (FindNextFile(file, &findFileData) != NULL);

			FindClose(file);
		}

		return objectNames;
	}

	std::string Object::getObjectProperty(std::string pathToObject, std::string propertyName)
	{
		auto getPropertyName = [](std::string& line) -> std::string
		{
			int lineIndex = 0;
			std::string propertyValue;
			std::string propertyName;

			for (char symbol : line) {

				if (symbol == '=') {

					break;
				}

				propertyName += symbol;
				lineIndex++;
			}

			return propertyName;
		};

		std::ifstream objectFile(pathToObject);
		std::string line = SNULL;
		std::string propertyValue = SNULL;
		int indexLine = 0;

		objectFile.is_open();

		while (std::getline(objectFile, line)) {

			std::string propertyName_ = getPropertyName(line);

			if (propertyName_ == propertyName) {

				for (char symbol : line) {

					if (indexLine >= propertyName_.size() + 1) {

						propertyValue += symbol;
					}

					indexLine++;
				}
			}
		}

		objectFile.close();
		propertyValue.erase(std::remove(propertyValue.begin(), propertyValue.end(), ' '), propertyValue.end());

		return propertyValue;
	}
}