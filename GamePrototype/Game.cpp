#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }, m_EnemyVector{}, m_EnemySpawnDelay{3.f}, m_EnemySpawnDelayDecrease{0.01f}, m_EnemySpawnCounter{0.f}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pPlayer = new Player(Rectf{50.f, GetViewPort().height/2, 20.f, 20.f}, 10, GetViewPort().height);
	m_pBackGroundMusic = new SoundStream("Music.mp3");
	m_pBackGroundMusic->Play(true);
	SoundStream::SetVolume(5);
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
	m_EnemySpawnDelay -= m_EnemySpawnDelayDecrease * elapsedSec;

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

void Game::Draw( ) const
{
	ClearBackground( );

	m_pPlayer->Draw();

	for (int index{ 0 }; index < m_EnemyVector.size(); ++index)
	{
		m_EnemyVector[index]->Draw();;
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pPlayer->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	m_pPlayer->ProcessKeyUpEvent(e);
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
