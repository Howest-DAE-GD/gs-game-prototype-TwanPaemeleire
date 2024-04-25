#pragma once
#include "Vector2f.h"
#include "Potion.h"
#include <vector>
class Player
{
public:
	Player(const Rectf& playerRect,int health, float windowHeight);
	
	void Update(float elapsedSec);
	void Draw() const;
	void Attack();

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
private:

	Vector2f m_Velocity;
	Rectf m_PlayerRect;

	int m_MaxHealth;
	Rectf m_HealthBoxes[10];

	Color4f m_Color;

	float m_AttackCounter;
	float m_AttackDelay;
	bool m_CanShoot;

	std::vector<Potion*> m_PotionVector;
};

