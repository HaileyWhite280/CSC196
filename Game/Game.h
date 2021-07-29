#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel1,
		StartLevel2,
		StartLevelBoss,
		PlayLevel1,
		PlayLevel2,
		PlayLevelBoss,
		Game,
		GameOver

	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

	private:
		void UpdateTitle(float dt);
		void UpdateLevelStart(float dt);
		void UpdateLevel2Start(float dt);
		void UpdateLevelBossStart(float dt);

		void OnAddPoints(const nc::Event& event);
		void OnPlayerDead(const nc::Event& event);

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t lives = 0;
};