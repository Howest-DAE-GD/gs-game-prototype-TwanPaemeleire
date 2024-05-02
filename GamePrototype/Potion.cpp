#include "pch.h"
#include "Potion.h"
#include "utils.h"

Potion::Potion(const Vector2f& pos, const Vector2f& destPos, int dmg)
	:m_HitBox{ pos.x, pos.y, 30.f, 30.f }, m_DestPosition{ destPos }, m_Damage{ dmg },
	m_SecondsToArrive{ 2.f }, m_DefaultSize{30.f}, m_MaxSizeIncrease{60.f}, m_HasReachedMaxDistance{false}
{
	m_DistanceTarget = m_DestPosition.x - m_HitBox.left;
	m_MovementSpeed = m_DistanceTarget / m_SecondsToArrive;
}

void Potion::Update(float elapsedSec)
{
	m_HitBox.left += m_MovementSpeed* elapsedSec;
	m_DistanceTarget = m_DestPosition.x - m_HitBox.left;
 	if (m_HitBox.left > m_DestPosition.x) m_HasReachedMaxDistance=true;
}

void Potion::Draw() const
{
	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	utils::DrawRect(m_HitBox);
}

int Potion::GetDamage()
{
	return m_Damage;
}

bool Potion::HasReachedMaxDistance()
{
	return m_HasReachedMaxDistance;
}
