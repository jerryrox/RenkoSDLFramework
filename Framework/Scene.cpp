#include "Scene.h"

// Framework
#include "Debug.h"
#include "Input.h"
#include "Buffer.h"
#include "Transform.h"
#include "UIOverlayController.h"
#include "UIScreenController.h"

// Screens and Overlays


Scene::Scene() :
	GameObject("scene")
{
}

Scene::~Scene()
{
	GameObject::~GameObject();
}

void Scene::Init()
{
	GameObject::Init();

	AdjustScreen();

	// Show splash view.
	//UIScreenController::GetInstance()->ShowView<SplashScreen>();
}

void Scene::Update(float deltaTime)
{
	if (Input::IsKeyDown(SDLK_F11))
	{
		Buffer::GetInstance()->SetFullScreen(!Buffer::GetInstance()->IsFullScreen());
		AdjustScreen();
	}
}

void Scene::AdjustScreen()
{
	// Retrieve display mode information to fit the screen.
	int screenWidth = 0;
	int screenHeight = 0;
	if (!Buffer::GetInstance()->IsFullScreen())
	{
		screenWidth = Buffer::Width;
		screenHeight = Buffer::Height;
	}
	else
	{
		SDL_GetRendererOutputSize(Buffer::GetInstance()->GetRenderer(), &screenWidth, &screenHeight);
	}

	// Calculate scale factor
	float baseRatio = (float)Buffer::Width / (float)Buffer::Height;
	float ratio = (float)screenWidth / (float)screenHeight;
	float scaleFactor = 1.0f;
	// If content is longer than screen
	if (ratio < baseRatio)
		scaleFactor = (float)screenWidth / (float)Buffer::Width;
	else
		scaleFactor = (float)screenHeight / (float)Buffer::Height;

	// Make all direct children's (0, 0) point to the center of screen.
	transform->SetLocalPosition((float)screenWidth / 2.0f, (float)screenHeight / 2.0f);
	transform->SetLocalScale(scaleFactor, scaleFactor);
}