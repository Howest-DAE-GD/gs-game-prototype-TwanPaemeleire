#pragma once
class Enemy
{
public:
	Enemy(const Point2f& pos, int health);

	void Update(float elaspedSec);
	void Draw() const;

	Rectf GetEnemyRect() const;
	int health;
private:


	Rectf m_EnemyRect;
	float m_MoveSpeed;
	bool m_MovesVertically;

	float m_TraveledVerticalDistance;
	float m_VerticalSpeed;
};

