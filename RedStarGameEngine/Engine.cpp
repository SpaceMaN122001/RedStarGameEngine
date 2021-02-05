#include "Engine.h"

namespace rsge
{
	Engine* gEngine = NULL;

	Engine::Engine()
	{
		mainScene = Scene();
		mPlayer = Player();
		gEngine = this;
	}

	void Engine::exec()
	{
		while (isOpen()) {

			sf::Event event;

			while (pollEvent(event)) {

				if (event.type == sf::Event::Closed)
					close();

				if (event.type == sf::Event::Resized) {

					setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
					setSize(sf::Vector2u(event.size.width, event.size.height));
				}

				if (mMessages[event.type] != NULL) {

					Message msg;
					msg.width = event.size.width;
					msg.height = event.size.height;
					msg.keyboardKeyText = static_cast<char>(event.text.unicode);
					msg.key = event.key.code;
					msg.mouseButton = event.mouseButton.button;
					
					if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {

						msg.mouseXPosition = event.mouseButton.x;
						msg.mouseYPosition = event.mouseButton.y;

					} else if (event.type == sf::Event::MouseMoved) {

						msg.mouseXPosition = event.mouseMove.x;
						msg.mouseYPosition = event.mouseMove.y;
					}

					(this->*mMessages[event.type])(msg);
				}
			}

			renderGame();
		}
	}

	void Engine::renderGame()
	{
		clear(sf::Color::White);

		for (Object*& object : mainScene.getObjects()) {

			if (object->isRender())
				draw(*object);
		}

		for (void(Engine::*func)() : mDrawFunctions) {

			if (func != NULL)
				(this->*func)();
		}

		if (mPlayer.isRender())
			draw(mPlayer);

		display();
	}

	void Engine::setScene(std::string pathToScene, std::string pathToObjects)
	{
		mainScene.clear();
		mainScene.setPathToScene(pathToScene);
		mainScene.setPathToObjects(pathToObjects);
		mainScene.loadObjects();
	}

	void Engine::setPlayer(std::string pathToPlayer)
	{
		mPlayer.setId(Object::getObjectProperty(pathToPlayer, "@Id"));
		mPlayer.setPosition(std::stoi(Object::getObjectProperty(pathToPlayer, "@XPos")), std::stoi(Object::getObjectProperty(pathToPlayer, "@YPos")));
		mPlayer.setTextureFromFile(Object::getObjectProperty(pathToPlayer, "@Texture"));
		mPlayer.setHealthPoints(std::stoi(Object::getObjectProperty(pathToPlayer, "@Health")));

		if (Object::getObjectProperty(pathToPlayer, "@IsRender") == "False")
			mPlayer.setRenderState(false);

		/*std::cout << mPlayer.getId() << std::endl;
		std::cout << mPlayer.getPosition().x << std::endl;
		std::cout << mPlayer.getPosition().y << std::endl;
		std::cout << mPlayer.getPathToTexture() << std::endl;*/
		//std::cout << mPlayer.getHealthPoints() << std::endl;
	}

	void Engine::pause()
	{
	}

	void Engine::resume()
	{
	}
}