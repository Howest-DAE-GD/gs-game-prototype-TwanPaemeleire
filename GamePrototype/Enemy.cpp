#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Point2f& pos, int health)
	: m_EnemyRect{ pos.x, pos.y, 50.f, 50.f }, m_MoveSpeed{ -200.f }, m_TraveledVerticalDistance{ 0.f }
	,m_VerticalSpeed{200.f}, health{health}
{
	int random = rand()% 2;
	if (random == 0) m_MovesVertically = true;
	else m_MovesVertically = false;
}

void Enemy::Update(float elaspedSec)
{
	m_EnemyRect.left += m_MoveSpeed * elaspedSec;
	if (m_MovesVertically)
	{
		m_EnemyRect.bottom += m_VerticalSpeed * elaspedSec;
		m_TraveledVerticalDistance += abs(m_VerticalSpeed * elaspedSec);
		if (m_TraveledVerticalDistance > 100.f)
		{
			m_VerticalSpeed *= -1;
			m_TraveledVerticalDistance = 0.f;
		}
	}
}

void Enemy::Draw() const
{
	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::FillRect(m_EnemyRect);
}

Rectf Enemy::GetEnemyRect() const
{
	return m_EnemyRect;
}
