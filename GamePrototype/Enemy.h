#pragma once
class Enemy
{
public:
	Enemy(const Point2f& pos);

	void Update(float elaspedSec);
	void Draw() const;

	Rectf GetEnemyRect() const;
private:
	Rectf m_EnemyRect;
	float m_MoveSpeed;
};

