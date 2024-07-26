#include "../../Engine/Source/Engine.h"
#include "../../Engine/Source/Scene.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include "../../Engine/Source/Font.h"
#include "../../Engine/Source/Text.h"

//GitHub: https://github.com/TroikNardimos/CSC196-GameEngine

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	// add audio sounds
	g_engine.GetAudio().AddSound("background-music-space.mp3");
	g_engine.GetAudio().AddSound("rocket.wav");
	g_engine.GetAudio().AddSound("laser.wav");
	g_engine.GetAudio().AddSound("ship-death.wav");
	g_engine.GetAudio().PlaySound("background-music-space.mp3");

	Time time;

	std::vector<Particle> particles;

	//int state = 0;

	float offset = 0;

	std::vector<Vector2> playerPoints;
	playerPoints.push_back(Vector2{ 5, 0});
	playerPoints.push_back(Vector2{ 1, 2});
	playerPoints.push_back(Vector2{ 2, 3});
	playerPoints.push_back(Vector2{ -3, 4});
	playerPoints.push_back(Vector2{ -4, 2});
	playerPoints.push_back(Vector2{ -2, 0});
	playerPoints.push_back(Vector2{ -4, -2});
	playerPoints.push_back(Vector2{ -3, -4});
	playerPoints.push_back(Vector2{ 2, -3});
	playerPoints.push_back(Vector2{ 1, -2});
	playerPoints.push_back(Vector2{ 5, 0});
	Model* playerModel = new Model{ playerPoints, Colour{ 0, 0, 1 } };

	std::vector<Vector2> enemyPoints;
	enemyPoints.push_back(Vector2{ 3, 0 });
	enemyPoints.push_back(Vector2{ -1, 2 });
	enemyPoints.push_back(Vector2{ -3, 1 });
	enemyPoints.push_back(Vector2{ -1, 0 });
	enemyPoints.push_back(Vector2{ -3, -1 });
	enemyPoints.push_back(Vector2{ -1, -2 });
	enemyPoints.push_back(Vector2{ 3, 0 });
	Model* enemyModel = new Model{ enemyPoints, Colour{ 1, 0, 0 } };

	Scene scene;

	Transform transform{ Vector2{ 400, 300}, 0, 5};
	auto player = std::make_unique<Player>(900, transform, playerModel);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene.AddActor(std::move(player));

	Font* font = new Font();
	font->Load("ArcadeClassic.ttf", 40);

	Text* scoreText = new Text(font);
	Text* livesText = new Text(font);
	Text* startText = new Text(font);

	Font* largeFont = new Font();
	largeFont->Load("ArcadeClassic.ttf", 70);

	Text* loseText = new Text(largeFont);
	Text* titleText = new Text(largeFont);


	// main loop
	bool start = true;
	bool quit = false;
	bool lose = false;
	while (!quit)
	{
		g_engine.GetAudio().Update();

		time.Tick();

		// input
		// update
		// draw

		// INPUT
		g_engine.GetInput().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		scene.Update(time.GetDeltaTime());

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();

		if (!start)
		{
			Enemy* pEnemy = scene.GetActor<Enemy>();
			if (pEnemy == nullptr && !lose)
			{
				for (int i = 0; i < random(1, 4); i++)
				{
					Transform transform{ Vector2{ randomf(0,800), randomf(0,600)}, 0, 5 };
					auto enemy = std::make_unique<Enemy>(300, transform, enemyModel);
					enemy->SetDamping(2.0f);
					enemy->SetTag("Enemy");
					scene.AddActor(std::move(enemy));
				}
			}

			Player* pPlayer = scene.GetActor<Player>();
			if (pPlayer != nullptr)
			{
				scoreText->Create(g_engine.GetRenderer(), "SCORE " + std::to_string(pPlayer->GetScore()), Colour{ 1, 1, 1, 1 });
				livesText->Create(g_engine.GetRenderer(), "LIVES " + std::to_string(pPlayer->GetLives()), Colour{ 1, 1, 1, 1 });
			}
			else
			{
				loseText->Create(g_engine.GetRenderer(), "YOU LOSE", Colour{ 1, 1, 1, 1 });
				lose = true;
			}
		}
		else
		{
			titleText->Create(g_engine.GetRenderer(), "SHIP SHAPE!", Colour{ 1, 1, 1, 1 });
			startText->Create(g_engine.GetRenderer(), "SPACE TO START", Colour{ 1, 1, 1, 1 });
			if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{
				start = false;
			}
		}

		particles.push_back(Particle{ {400,300}, randomOnUnitCircle() * randomf(50, 300), 5});

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
		}


		// DRAW
		//// clear screen
		g_engine.GetRenderer().SetColour(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetRenderer().SetColour(255, 255, 255, 0);

		g_engine.GetRenderer().SetColour(255, 255, 255, 0);
		scene.Draw(g_engine.GetRenderer());

		for (Particle particle : particles)
		{
			g_engine.GetRenderer().SetColour(255, 255, 255, 0);

			particle.Draw(g_engine.GetRenderer());
		}

		if (start)
		{
			titleText->Draw(g_engine.GetRenderer(), 200, 100);
			startText->Draw(g_engine.GetRenderer(), 250, 400);
		}
		else if (lose)
		{
			scene.RemoveAll();
			loseText->Draw(g_engine.GetRenderer(), 250, 100);
		}
		else
		{
			scoreText->Draw(g_engine.GetRenderer(), 40, 40);
			livesText->Draw(g_engine.GetRenderer(), 600, 40);
		}

		//// show screen
		g_engine.GetRenderer().EndFrame();
	}

	return 0;
}