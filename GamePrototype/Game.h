#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "Enemy.h"
class Game : public BaseGame
{
public:
	enum class GameState {
		menu, inGame, lost
	};

	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	GameState m_State;

	Player* m_pPlayer;

	std::vector<Enemy*> m_EnemyVector;

	float m_EnemySpawnDelay;
	float m_EnemySpawnDelayDecrease;
	float m_EnemySpawnCounter;
	int m_Deaths;

	// FUNCTIONS
	void Collisions();
	void ResetEnemies();

	void ManageMenu();
	int m_Currency;
	int m_upgradeCost;

	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};