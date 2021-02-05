#include "Settings.h"

namespace rsge
{
	Settings::Settings(std::string pathToFile) : mPathToFile(pathToFile)
	{
	}

	Settings::~Settings()
	{
	}

	void Settings::setPathToFile(std::string pathToFile)
	{
		mPathToFile = pathToFile;
	}

	void Settings::setKeyValue(std::string keyName, std::string value)
	{
		std::ifstream file(mPathToFile);
		std::string line = SNULL;
		std::vector<std::string> fileContent;
		bool iskeyFind = false;

		file.is_open();

		while (std::getline(file, line)) {

			fileContent.push_back(line);
		}

		file.close();

		for (std::string& line : fileContent) {

			if (getKeyName(line) == keyName) {

				line = getKeyName(line) + '=' + value;
				iskeyFind = true;

				break;
			}
		}

		if (!iskeyFind)
			fileContent.push_back(keyName + '=' + value);

		std::ofstream out(mPathToFile);
		out.is_open();

		for (std::string& line : fileContent) {

			out << line << std::endl;
		}

		out.close();
	}

	std::string Settings::getKeyValue(std::string keyName)
	{
		std::ifstream file(mPathToFile);
		std::string line = SNULL;
		int lineIndex = 0;
		int index = 0;
		std::string keyValue = SNULL;

		file.is_open();

		while (std::getline(file, line)) {

			if (getKeyName(line) == keyName) {

				for (char symbol : line) {

					if (symbol == '=')
						break;

					lineIndex++;
				}

				for (char symbol : line) {

					if (index >= lineIndex + 1) {

						keyValue += symbol;
					}

					index++;
				}
			}
		}

		file.close();
		keyValue.erase(std::remove(keyValue.begin(), keyValue.end(), ' '), keyValue.end());

		return keyValue;
	}

	std::string Settings::getKeyName(std::string line)
	{
		int lineIndex = 0;
		int index = 0;
		std::string keyName = SNULL;

		for (char symbol : line) {

			if (symbol == '=')
				break;

			lineIndex++;
		}

		for (char symbol : line) {

			if (index <= lineIndex - 1) {

				keyName += symbol;
			}

			index++;
		}

		keyName.erase(std::remove(keyName.begin(), keyName.end(), ' '), keyName.end());

		return keyName;
	}

	void Settings::removeKey(std::string keyName)
	{
		std::ifstream file(mPathToFile);
		std::string line = SNULL;
		std::vector<std::string> fileContent;

		file.is_open();

		while (std::getline(file, line)) {

			if (getKeyName(line) != keyName) {

				fileContent.push_back(line);
			}
		}

		file.close();

		std::ofstream out(mPathToFile);
		out.is_open();

		for (std::string& line : fileContent) {

			out << line << std::endl;
		}

		out.close();
	}
}