#pragma once

#define SNULL " "

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace rsge
{
	class Settings
	{
	public:
		Settings(std::string pathToFile = SNULL);
		~Settings();
		//set
		void setPathToFile(std::string pathToFile);
		void setKeyValue(std::string keyName, std::string value);
		//get
		std::string& getPathToFile() { return mPathToFile; }
		std::string getKeyValue(std::string keyName);
		//other
		void removeKey(std::string keyName);

	private:
		std::string mPathToFile;
		std::string getKeyName(std::string line);

	protected:
	};
}