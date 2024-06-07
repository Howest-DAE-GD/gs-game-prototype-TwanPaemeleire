#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <stdlib.h> 
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window },m_EnemyVector{}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup();
}

void Game::Initialize( )
{
	
	m_EnemySpawnDelay= 3.f;
	m_EnemySpawnDelayDecrease= 0.06f ;
	m_EnemySpawnCounter= 0.f ;
	m_pPlayer = new Player(Rectf{50.f, GetViewPort().height/2, 20.f, 20.f}, 5, GetViewPort().height);
	m_Currency = 0;
	m_upgradeCost = 10;
	m_State = GameState::inGame;
	m_Deaths = 0;

	std::cout << "Press/Hold W and S to move.\nPress/Hold SPACE to shoot.\nEliminate the incoming enemies(red squares) before they steal your milk(white squares)!";
}

void Game::Cleanup( )
{
	delete m_pPlayer;

	for(int index{0}; index < m_EnemyVector.size(); ++index)
	{
		delete m_EnemyVector[index];
	}
}

void Game::Update( float elapsedSec )
{
	if (m_State == GameState::inGame)
	{
		if (m_EnemySpawnDelay > 0.2f - m_Deaths *0.005)
		{
			m_EnemySpawnDelay -= m_EnemySpawnDelayDecrease * elapsedSec;
		}	
		if (!Collisions())
		{
			m_EnemySpawnCounter += elapsedSec;
			if (m_EnemySpawnCounter >= m_EnemySpawnDelay)
			{
				m_EnemySpawnCounter = 0.f;
				int randomY = rand() % 440;
				int lives{ (m_Deaths > 0) ? 2 : 1 };
				m_EnemyVector.push_back(new Enemy(Point2f{ 850.f, float(randomY) }, lives));

			}

			m_pPlayer->Update(elapsedSec);

			for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
			{
				m_EnemyVector[index]->Update(elapsedSec);
			}
		}

		else {
			for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
			{
				delete m_EnemyVector[index];
				m_EnemyVector.erase(m_EnemyVector.begin() + index);
			}
		}
		
	}

	else if (m_State == GameState::menu) ManageMenu();

	else if (m_State == GameState::lost)
	{
		/*for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
		{
			delete m_EnemyVector[index];
			m_EnemyVector.erase(m_EnemyVector.begin() + index);
		}*/

		++m_Deaths;
		m_pPlayer->Reset();
		ResetEnemies();
		system("cls");
		std::cout << "Upgrades:" << std::endl;
		std::cout << "J to upgrade fireRate\nK to upgrade Speed" << std::endl;
		std::cout << "X in menu to return to the game" << std::endl;
		std::cout << "Currency: " << m_Currency << std::endl;
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
				if (m_pPlayer->m_AttackDelay > 0.3f)
				{
					m_pPlayer->m_AttackDelay -= 0.02f;
					m_Currency -= m_upgradeCost;
				}
				system("cls");
				std::cout << "Upgrades:" << std::endl;
				std::cout << "J to upgrade fireRate\nK to upgrade Speed" << std::endl;
				std::cout << "X in menu to return to the game" << std::endl;
				std::cout << "Currency: " << m_Currency << std::endl;
				std::cout << "Upgraded FireRate" << std::endl;
			}

			break;
		case SDLK_k:
			if (m_Currency >= m_upgradeCost)
			{
				if (m_pPlayer->m_SpeedY < 280.f)
				{
					m_pPlayer->m_SpeedY += 5.f;
					m_Currency -= m_upgradeCost;
				}
				system("cls");
				std::cout << "Upgrades:" << std::endl;
				std::cout << "J to upgrade fireRate\nK to upgrade Speed" << std::endl;
				std::cout << "X in menu to return to the game" << std::endl;
				std::cout << "Currency: " << m_Currency << std::endl;
				std::cout << "Upgraded Speed" << std::endl;
			}
			break;
		case SDLK_x:
			for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
			{
				delete m_EnemyVector[index];
				m_EnemyVector.erase(m_EnemyVector.begin() + index);
			}
			m_EnemySpawnDelay = 3.f;
			m_EnemySpawnCounter = 0.f;
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


bool Game::Collisions()
{
	for (int index{ 0 }; index < m_pPlayer->m_PotionVector.size(); ++index)
	{
		for (int enemyIndex{ 0 }; enemyIndex < m_EnemyVector.size(); ++enemyIndex)
		{
			if (utils::IsOverlapping(m_EnemyVector[enemyIndex]->GetEnemyRect(), m_pPlayer->m_PotionVector[index]->m_HitBox))
			{
				--m_EnemyVector[enemyIndex]->health;
				if (m_EnemyVector[enemyIndex]->health <= 0)
				{
					delete m_EnemyVector[enemyIndex];
					m_EnemyVector.erase(m_EnemyVector.begin() + enemyIndex);
					m_Currency += 5;
				}
				delete m_pPlayer->m_PotionVector[index];
				m_pPlayer->m_PotionVector.erase(m_pPlayer->m_PotionVector.begin() + index);
				break;
			}
		}
	}

	for (int enemyIndex{ 0 }; enemyIndex < m_EnemyVector.size(); ++enemyIndex)
	{
			if (m_EnemyVector[enemyIndex]->GetEnemyRect().left + m_EnemyVector[enemyIndex]->GetEnemyRect().width <= 0.f)
			{
				delete m_EnemyVector[enemyIndex];
				m_EnemyVector.erase(m_EnemyVector.begin() + enemyIndex);


				bool hasRemainingHealth{ false };
				for (int healthIdx{ 0 }; healthIdx < m_pPlayer->m_MaxHealth; ++healthIdx)
				{
					if (m_pPlayer->m_HealthBoxes[healthIdx].width > 0.f)
					{
						m_pPlayer->m_HealthBoxes[healthIdx] = Rectf{ 0.f, 0.f, 0.f, 0.f };
						hasRemainingHealth = true;
						if (healthIdx == m_pPlayer->m_MaxHealth - 1) hasRemainingHealth = false;
						break;
					}
				}
				if (!hasRemainingHealth)
				{
					m_State = GameState::lost;
					return true;
				}
				break;

			}
		}
	return false;
}

void Game::ManageMenu()
{
	//getch();
	
}

void Game::ResetEnemies()
{
	m_EnemySpawnDelay = 3.f;
	m_EnemySpawnCounter = 0.f;

	
}
