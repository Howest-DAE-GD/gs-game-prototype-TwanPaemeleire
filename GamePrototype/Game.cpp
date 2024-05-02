#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window },m_EnemyVector{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
	m_EnemySpawnDelay= 3.f;
	m_EnemySpawnDelayDecrease= 0.01f ;
	m_EnemySpawnCounter= 0.f ;
	m_pPlayer = new Player(Rectf{50.f, GetViewPort().height/2, 20.f, 20.f}, 1, GetViewPort().height);
	m_pBackGroundMusic = new SoundStream("Music.mp3");
	m_pBackGroundMusic->Play(true);
	SoundStream::SetVolume(5);
	m_Currency = 0;
	m_upgradeCost = 10;
	m_State = GameState::inGame;

	std::cout << "Upgrades:" << std::endl;
	std::cout << "J to upgrade fireRate\nK to upgrade Speed" << std::endl;
	std::cout << "SPACE in menu to return to the game" << std::endl;
}

void Game::Cleanup( )
{
	delete m_pPlayer;

	for(int index{0}; index < m_EnemyVector.size(); ++index)
	{
		delete m_EnemyVector[index];
	}

	delete m_pBackGroundMusic;
}

void Game::Update( float elapsedSec )
{
	if (m_State == GameState::inGame)
	{
		m_EnemySpawnDelay -= m_EnemySpawnDelayDecrease * elapsedSec;
		Collisions();

		m_EnemySpawnCounter += elapsedSec;
		if (m_EnemySpawnCounter >= m_EnemySpawnDelay)
		{
			m_EnemySpawnCounter = 0.f;
			int randomY = rand() % 440;
			m_EnemyVector.push_back(new Enemy(Point2f{ 850.f, float(randomY) }));
		}

		m_pPlayer->Update(elapsedSec);

		for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
		{
			m_EnemyVector[index]->Update(elapsedSec);
		}
	}

	else if (m_State == GameState::menu) ManageMenu();

	else if (m_State == GameState::lost)
	{
		for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
		{
			delete m_EnemyVector[index];
			m_EnemyVector.erase(m_EnemyVector.begin() + index);
		}
		m_pPlayer->Reset();
		m_State = GameState::menu;
	}
}

void Game::Draw( ) const
{
	ClearBackground( );

	if (m_State == GameState::inGame)
	{
		m_pPlayer->Draw();

		for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
		{
			m_EnemyVector[index]->Draw();
		}
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pPlayer->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->ProcessKeyUpEvent(e);
	if (m_State == GameState::menu)
	{
		switch (e.keysym.sym)
		{
		case SDLK_j:
			if (m_Currency >= m_upgradeCost)
			{
				m_pPlayer->m_AttackDelay -= 0.1f;
				m_Currency -= m_upgradeCost;
				std::cout << "Upgraded FireRate" << std::endl;
			}

			break;
		case SDLK_k:
			if (m_Currency >= m_upgradeCost)
			{
				m_pPlayer->m_SpeedY += 20.f;
				m_Currency -= m_upgradeCost;
				std::cout << "Upgraded FireRate" << std::endl;
			}
			break;
		case SDLK_SPACE:
			m_State = GameState::inGame;
			break;
		}
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}


void Game::Collisions()
{
	for (int index{ 0 }; index < m_pPlayer->m_PotionVector.size(); ++index)
	{
		for (int enemyIndex{ 0 }; enemyIndex < m_EnemyVector.size(); ++enemyIndex)
		{
			if (utils::IsOverlapping(m_EnemyVector[enemyIndex]->GetEnemyRect(), m_pPlayer->m_PotionVector[index]->m_HitBox))
			{
				delete m_EnemyVector[enemyIndex];
				m_EnemyVector.erase(m_EnemyVector.begin() + enemyIndex);
				delete m_pPlayer->m_PotionVector[index];
				m_pPlayer->m_PotionVector.erase(m_pPlayer->m_PotionVector.begin() + index);
				m_Currency += 5;
				break;
			}
		}
	}

	for (int enemyIndex{ 0 }; enemyIndex < m_EnemyVector.size(); ++enemyIndex)
	{
		for (int healthIdx{ 0 }; healthIdx < m_pPlayer->m_MaxHealth; ++healthIdx)
		{
			if (utils::IsOverlapping(m_EnemyVector[enemyIndex]->GetEnemyRect(), m_pPlayer->m_HealthBoxes[healthIdx]))
			{
				delete m_EnemyVector[enemyIndex];
				m_EnemyVector.erase(m_EnemyVector.begin() + enemyIndex);

				m_pPlayer->m_HealthBoxes[healthIdx] = Rectf{ 0.f, 0.f, 0.f, 0.f };

				bool hasRemainingHealth{ false };

				for (int healthIdx{ 0 }; healthIdx < m_pPlayer->m_MaxHealth; ++healthIdx)
				{
					if (m_pPlayer->m_HealthBoxes[healthIdx].width > 0.f)
					{
						hasRemainingHealth = true;
						break;
					}
				}

				if (!hasRemainingHealth) m_State = GameState::lost;
				break;
			}
		}
	}

}

void Game::ManageMenu()
{

}
