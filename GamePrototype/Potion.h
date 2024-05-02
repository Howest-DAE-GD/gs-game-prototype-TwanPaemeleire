#pragma once
#include "Vector2f.h"
class Potion
{
public:
	Potion(const Vector2f& pos, const Vector2f& destPos, int dmg);

	void Update(float elapsedSec);
	void Draw() const;

	int GetDamage();
	bool HasReachedMaxDistance();
	Rectf m_HitBox;

private:
	Vector2f m_DestPosition;
	Vector2f m_Velocity;
	float m_DistanceTarget;

	int m_Damage;
	float m_MaxSizeIncrease;
	float m_DefaultSize;
	float m_MovementSpeed;

	float m_SecondsToArrive;
	bool m_HasReachedMaxDistance;
};

