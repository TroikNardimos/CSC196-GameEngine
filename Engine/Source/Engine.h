#pragma once
#include "Renderer.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Vector2.h"
#include "Input.h"
#include "Model.h"
#include "Transform.h"
#include "Audio.h"

#include <fmod.hpp>
#include <SDL.h>

#define RENDERER g_engine.GetRenderer()
#define INPUT g_engine.GetInput()
#define AUDIO g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

public:
	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };

	static Engine ms_engine;
};

extern Engine g_engine;