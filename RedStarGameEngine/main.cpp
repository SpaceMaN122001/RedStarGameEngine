#include "Engine.h"

using namespace rsge;
using namespace std;

class A : public Engine
{
public:
	A() 
	{
		create(sf::VideoMode(1280, 720), "123", ScreenMode::FixedSize);
		sf::Image icon;
		icon.loadFromFile("Main.png");
		setIcon(256, 256, icon.getPixelsPtr());
		connect(sf::Event::KeyPressed, &A::keyBoardEvent);
		connect(sf::Event::MouseMoved, &A::movePlayer);
		setScene("E:\\repos 2020\\RedStarGameEngine\\RedStarGameEngine\\scene1.dat", "E:\\repos 2020\\RedStarGameEngine\\RedStarGameEngine");
		setPlayer("E:\\repos 2020\\RedStarGameEngine\\RedStarGameEngine\\player.dat");
	}
	~A() {}

	void drawing()
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(player().getHealthPoints(), 20));
		rectangle.setFillColor(sf::Color::Red);
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.setOutlineThickness(5);
		rectangle.setPosition(10, 20);
		draw(rectangle);
	}

	void drawing1()
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(player().getHealthPoints(), 20));
		rectangle.setFillColor(sf::Color::Blue);
		rectangle.setOutlineColor(sf::Color::Black);
		rectangle.setOutlineThickness(5);
		rectangle.setPosition(200, 20);
		draw(rectangle);
	}

	void keyBoardEvent(Message msg)
	{
		if (msg.key == sf::Keyboard::Escape) {

			connectDraw(&A::drawing);
			connectDraw(&A::drawing1);
		}

		if (msg.key == sf::Keyboard::Enter) {

			disconnect(&A::drawing);
			disconnect(&A::drawing1);
		}
	}

	void movePlayer(Message msg)
	{
		scene()["object"]->setPosition(msg.mouseXPosition, msg.mouseYPosition);
	}
};

int main()
{
	A a;
	a.exec();

	system("pause");
	return 0;
}