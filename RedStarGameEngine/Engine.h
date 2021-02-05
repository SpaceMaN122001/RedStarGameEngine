#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <functional>
#include <iostream>
#include <fstream>

extern "C" {
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

#ifdef _WIN32
#include <Windows.h>
#elif __linux__

#endif

#include "Settings.h"
#include "Script.h"
#include "Object.h"
#include "Scene.h"
#include "Player.h"

namespace rsge
{
	struct Message
	{
		int width;
		int height;
		char keyboardKeyText;
		sf::Keyboard::Key key;
		sf::Mouse::Button mouseButton;
		int mouseXPosition;
		int mouseYPosition;
	};

	enum ScreenMode
	{
		FixedSize = 1 | 4
	};

	class Engine : public sf::RenderWindow
	{
		typedef void(Engine::*DrawFuncPointer)();
		typedef void(Engine::*ConnectFuncPointer)(Message);
	public:
		Engine();
		~Engine() {}
		//set
		void setScene(std::string pathToScene, std::string pathToObjects);
		void setPlayer(std::string pathToPlayer);
		template<typename T>
		void connectDraw(void(T::*function)()) { mDrawFunctions.push_back(reinterpret_cast<DrawFuncPointer>(function)); }
		template<typename T>
		void connect(sf::Event::EventType eventType, void(T::*function)(Message msg))
		{
			mMessages[eventType] = reinterpret_cast<ConnectFuncPointer>(function);
		}
		void disconnect(sf::Event::EventType eventType) { mMessages.erase(eventType); }
		template<typename T>
		void disconnect(void(T::*function)())
		{
			int i = 0;

			for (DrawFuncPointer func : mDrawFunctions) {

				if (func == reinterpret_cast<DrawFuncPointer>(function)) {

					mDrawFunctions.erase(mDrawFunctions.begin() + i);

					return;
				}

				i++;
			}
		}
		//get
		Scene& scene() { return mainScene; }
		Player& player() { return mPlayer; }
		//other
		void exec();
		void pause();
		void resume();

	private:
		void renderGame();

	private:
		std::map<sf::Event::EventType, ConnectFuncPointer> mMessages;
		Scene mainScene;
		std::vector<DrawFuncPointer> mDrawFunctions;
		Player mPlayer;
	};

	extern Engine* gEngine;
}