#include "pch.h"
#include "Player.h"
#include "utils.h"

Player::Player(const Rectf& playerRect,int health, float windowHeight)
	:m_PlayerRect{playerRect}, m_MaxHealth{health}, m_PotionVector{}, m_AttackCounter{0.f}, m_AttackDelay{1.f},
	m_CanShoot{true}, m_SpeedY{200.f}
{
	m_Color = Color4f{ 0.f, 1.f, 0.f, 1.f };
	m_Velocity = Vector2f{0.f, 0.f};

	for (int rectIdx{ 0 }; rectIdx < m_MaxHealth; ++rectIdx)
	{
		float yPos{30 + 25.f * rectIdx + 80.f *rectIdx};
	
		m_HealthBoxes.push_back(Rectf{5.f, yPos, 30, 30});
	}
}

Player::~Player()
{
}

void Player::Update(float elapsedSec)
{
	if (!m_CanShoot) m_AttackCounter += elapsedSec;
	if (m_AttackCounter >= m_AttackDelay)
	{
		m_CanShoot = true;
		m_AttackCounter = 0.f;
	}

	m_PlayerRect.bottom += m_Velocity.y * elapsedSec;
	if (m_PlayerRect.bottom + m_PlayerRect.height < 0.f)
	{
		m_PlayerRect.bottom = 500.f - m_PlayerRect.height;
	}

	else if (m_PlayerRect.bottom > 500.f)
	{
		m_PlayerRect.bottom = 0.f;
	}

	for (int index{ 0 }; index < m_PotionVector.size(); ++index)
	{
		m_PotionVector[index]->Update(elapsedSec);
		if (m_PotionVector[index]->HasReachedMaxDistance())
		{
			delete m_PotionVector[index];
			m_PotionVector.erase(m_PotionVector.begin() + index);
		}
	}
	ProcessKeyDownEvent();
}

void Player::Draw() const
{

	for (int index{ 0 }; index < m_PotionVector.size(); ++index)
	{
		m_PotionVector[index]->Draw();
	}

	utils::SetColor(m_Color);
	utils::DrawRect(m_PlayerRect);

	utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });

	for (int rectIdx{ 0 }; rectIdx < m_MaxHealth; ++rectIdx)
	{
		utils::FillRect(m_HealthBoxes[rectIdx]);
	}
}

void Player::Attack()
{
	m_PotionVector.push_back(new Potion(Vector2f{ m_PlayerRect.left + m_PlayerRect.width, m_PlayerRect.bottom }, Vector2f{ 846.f, m_PlayerRect.bottom }, 20));
	m_CanShoot = false;
}

void Player::ProcessKeyDownEvent()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	bool isPressingUp{ bool(pStates[SDL_SCANCODE_W]) };
	bool isPressingDown{ bool(pStates[SDL_SCANCODE_S]) };
	bool isPressingShoot{ bool(pStates[SDL_SCANCODE_SPACE]) };

	if(isPressingUp) m_Velocity.y = m_SpeedY;
	if(isPressingDown) m_Velocity.y = -m_SpeedY;
	if(isPressingShoot) if (m_CanShoot) Attack();

}

void Player::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_w:
		m_Velocity.y = 0.f;
		break;

	case SDLK_s:
		m_Velocity.y = 0.f;
		break;

	}
}

void Player::Reset()
{
	m_HealthBoxes.clear();
	for (int rectIdx{ 0 }; rectIdx < m_MaxHealth; ++rectIdx)
	{
		float yPos{ 30 + 25.f * rectIdx + 80.f * rectIdx };
		m_HealthBoxes.push_back(Rectf{ 5.f, yPos, 30, 30 });
	}
}
