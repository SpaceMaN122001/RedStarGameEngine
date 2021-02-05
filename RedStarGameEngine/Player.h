#pragma once

namespace rsge
{
	class Player : public Object
	{
	public:
		Player() {}
		~Player() {}
		void killPlayer() { mHealthPoints = 0; }
		void toDamage(unsigned int amountOfDamage);
		bool isDead() { if (mHealthPoints == 0) return true; else false; }
		//set
		void setHealthPoints(unsigned int healthPoints) { mHealthPoints = healthPoints; }
		//get
		unsigned int& getHealthPoints() { return mHealthPoints; }

	private:
		unsigned int mHealthPoints = 100;

	protected:
	};
}