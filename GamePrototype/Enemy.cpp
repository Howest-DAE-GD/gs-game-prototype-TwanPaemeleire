#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy(const Point2f& pos)
	: m_EnemyRect{pos.x, pos.y, 50.f, 50.f}, m_MoveSpeed{-200.f}
{
}

void Enemy::Update(float elaspedSec)
{
	m_EnemyRect.left += m_MoveSpeed * elaspedSec;
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
