#include "../../Engine/Source/Renderer.h"
#include "../../Engine/Source/Particle.h"
#include "../../Engine/Source/Random.h"
#include "../../Engine/Source/ETime.h"
#include "../../Engine/Source/MathUtils.h"
#include "../../Engine/Source/Vector2.h"
#include "../../Engine/Source/Input.h"
#include "../../Engine/Source/Model.h"
#include "../../Engine/Source/Transform.h"

#include <iostream>
#include <SDL.h>
#include <vector>
#include <stdlib.h>
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

	//FMOD::Sound* sound = nullptr;
	//std::vector<FMOD::Sound*> sounds;

	//audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	//audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	//audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	//audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	//audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	//audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	//sounds.push_back(sound);

	Input input;
	input.Initialize();

	Time time;

	std::vector<Particle> particles;

	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0});
	points.push_back(Vector2{ -5, -5});
	points.push_back(Vector2{ -5, 5});
	points.push_back(Vector2{ 5, 0});
	Model model{ points, Colour{ 1, 0, 0 } };
	Transform transform{ {renderer.GetWidth() >> 1, renderer.GetHeight() >> 1}, 0, 5};

	// 0001 = 1
	// 0010 = 2
	// 0100 = 4
	// 1000 = 8
	// 1000 >> 1 = 0100
	// 0100 << 1 = 1000

	// main loop
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

		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) thrust = 400;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -400;

		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) transform.rotation -= Math::DegToRad(100) * time.GetDeltaTime();
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) transform.rotation += Math::DegToRad(100) * time.GetDeltaTime();

		Vector2 velocity = Vector2{ thrust, 0.0f}.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.GetWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.GetHeight());
		//transform.rotation = velocity.Angle();//rotation + time.GetDeltaTime();

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();

		if (input.GetMouseButtonDown(0))
		{
			particles.push_back(Particle{ {mousePosition}, randomOnUnitCircle() * randomf(50, 300), randomf(1 ,3)});
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
			if (particle.position.y > 600) particle.position.y = 0;
			if (particle.position.y < 0) particle.position.y = 600;
		}

		//if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		//{
		//	audio->playSound(sounds[0], nullptr, false, nullptr);
		//}
		//if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		//{
		//	audio->playSound(sounds[1], nullptr, false, nullptr);
		//}
		//if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		//{
		//	audio->playSound(sounds[2], nullptr, false, nullptr);
		//}
		//if (input.GetKeyDown(SDL_SCANCODE_R) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		//{
		//	audio->playSound(sounds[3], nullptr, false, nullptr);
		//}
		//if (input.GetKeyDown(SDL_SCANCODE_T) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		//{
		//	audio->playSound(sounds[4], nullptr, false, nullptr);
		//}
		//if (input.GetKeyDown(SDL_SCANCODE_Y) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		//{
		//	audio->playSound(sounds[5], nullptr, false, nullptr);
		//}

		// DRAW
		//// clear screen
		renderer.SetColour(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColour(255, 255, 255, 0);

		float radius = 100;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 30)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.01f) * radius;

			renderer.SetColour(rand() % 256, rand() % 256, rand() % 256, 0);
			//renderer.DrawRect(400 + x, 300 + y, randomf(1, 40), randomf(1, 40));
		}

		//draw particles
		for (Particle particle : particles)
		{
			renderer.SetColour(rand() % 256, rand() % 256, rand() % 256, 0);

			particle.Draw(renderer);
		}

		renderer.SetColour(255, 255, 255, 0);
		model.Draw(renderer, transform);

		//// show screen
		renderer.EndFrame();
	}

	return 0;
}