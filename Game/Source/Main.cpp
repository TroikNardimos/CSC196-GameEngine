#include "../../Engine/Source/Renderer.h"
#include "../../Engine/Source/Particle.h"
#include "../../Engine/Source/Random.h"
#include "../../Engine/Source/ETime.h"
#include <SDL.h>
#include <stdlib.h>
#include <iostream>
#include "../../Engine/Source/Vector2.h"
#include <vector>
#include "../../Engine/Source/Input.h"
#include <fmod.hpp>

//GitHub: https://github.com/TroikNardimos/CSC196-GameEngine

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	FMOD::Sound* sound = nullptr;
	std::vector<FMOD::Sound*> sounds;

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	Input input;
	input.Initialize();

	Time time;

	//std::vector<Particle> particles;
	//for (int i = 0; i < 0000; i++)
	//{
	//	particles.push_back(Particle{ {rand() % 800, rand() % 600}, { randomf(100, 300), 0.0 }});
	//}

	//Vector2 v1{ 400, 300 };
	//Vector2 v2{ 700, 500 };

	//std::vector<Vector2> points;

	//for (int i = 0; i < 100; i++)
	//{
	//	points.push_back(Vector2{ rand() % 800, rand() % 600});
	//}

	bool quit = false;
	while (!quit)
	{
		audio->update();

		time.Tick();
		//std::cout << time.GetTime() << std::endl;

		// input
		// update
		// draw

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();

		//if (input.GetMouseButtonDown(0))
		//{
		//	particles.push_back(Particle{ {mousePosition}, { randomf(-10, 10), randomf(-10, 10) }, randomf(20)});
		//}

		//for (Particle& particle : particles)
		//{
		//	particle.Update(time.GetDeltaTime());
		//	/*if (particle.position.x > 800) particle.position.x = 0;
		//	if (particle.position.x < 0) particle.position.x = 800;*/
		//}

		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
		//if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		//{
		//	std::cout << "mouse pressed\n";
		//	points.push_back(mousePosition);
		//}
		//if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		//{
		//	float distance = (points.back() - mousePosition).Lenght();
		//	if (distance > 10) points.push_back(mousePosition);
		//}

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			audio->playSound(sounds[0], nullptr, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[1], nullptr, false, nullptr);
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[2], nullptr, false, nullptr);
		}

		// [p, p, p, p]
		//Vector2 speed{ 0.1f, -0.1f };
		//for (Vector2& point : points)
		//{
		//	point = point + 0.002f;
		//}

		// DRAW
		//// clear screen
		renderer.SetColour(0, 0, 0, 0);
		renderer.BeginFrame();

		//// draw line
		renderer.SetColour(255, 255, 255, 0);
		//renderer.DrawLine(0, 0, 800, 600);

		//for (Particle particle : particles)
		//{
		//	renderer.SetColour(rand() % 256, rand() % 256, rand() % 256, 0);

		//	particle.Draw(renderer);
		//}

		//// draw square
		//renderer.SetColour(255, 255, 255, 0);
		//renderer.DrawLine(300, 200, 500, 200);
		//renderer.DrawLine(500, 200, 500, 400);
		//renderer.DrawLine(500, 400, 300, 400);
		//renderer.DrawLine(300, 400, 300, 200);
		//renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		//draw random Vector2
		//renderer.SetColour(255, 255, 255, 0);
		//for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		//{
		//	renderer.SetColour(rand() % 256, rand() % 256, rand() % 256, 0);
		//	renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		//}

		////draw random
		//for (int i = 0; i < 100; i++)
		//{
		//	renderer.SetColour(rand() % 256, rand() % 256, rand() % 256, 0);
		//	renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600);
		//	renderer.DrawPoint(rand() % 800, rand() % 600);
		//}

		//// show screen
		renderer.EndFrame();
	}

	return 0;
}