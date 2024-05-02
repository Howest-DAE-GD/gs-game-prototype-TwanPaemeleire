#pragma once
#include "Vector2f.h"
#include "Potion.h"
#include <vector>
class Player
{
public:
	Player(const Rectf& playerRect,int health, float windowHeight);
	~Player();


	void Update(float elapsedSec);
	void Draw() const;
	void Attack();

	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void Reset();

	std::vector<Rectf> m_HealthBoxes;
	std::vector<Potion*> m_PotionVector;

	int m_MaxHealth;
	float m_SpeedY;
	float m_AttackDelay;

private:

	Vector2f m_Velocity;
	Rectf m_PlayerRect;

	
	

	Color4f m_Color;

	float m_AttackCounter;
	
	bool m_CanShoot;

	
};

