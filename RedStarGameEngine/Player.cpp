#include "Engine.h"

namespace rsge
{
	void Player::toDamage(unsigned int amountOfDamage)
	{
		if (mHealthPoints == 0)
			return;

		mHealthPoints -= amountOfDamage;
	}
}