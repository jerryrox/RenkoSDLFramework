#ifdef _DEBUG

#include "FrameworkTest.h"

#include "FrameworkTestScreen.h"
#include "UIScreenController.h"
#include "MusicController.h"
#include "RenkoFramework.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "AudioClips.h"
#include "Transform.h"
#include "Atlas.h"
#include "Input.h"

FrameworkTest::FrameworkTest()
{

}

FrameworkTest::~FrameworkTest()
{
	RenkoFramework::Destroy();
}

void FrameworkTest::Entry()
{
	root = new GameObject("Root");

	RenkoFramework::Initialize(60);
	RenkoFramework::GetInstance()->SetRootObject(root);
	Input::SetCloseListener([&]() {
		RenkoFramework::GetInstance()->Shutdown();
	});

	// Load texture assets
	Atlas::GetInstance()->LoadTexture("tests\\box", ".png", 1, 1, 1, 1);
	Atlas::GetInstance()->LoadTexture("tests\\round-box", ".png", 16, 16, 32, 32);
	Atlas::GetInstance()->LoadTexture("tests\\button", ".png");

	// Load audio assets
	auto clips = AudioManager::GetInstance()->GetClips();
	clips->LoadClip("tests\\hit", ".wav", false);
	clips->LoadClip("tests\\click", ".wav", false);

	// Load bgm
	clips->LoadClip("tests\\bgm", ".mp3", true);
	AudioManager::GetInstance()->GetMusicController()->MountMusic(clips->GetClip("tests\\bgm"));

	// Initialize the root.
	root->Init();
	root->GetTransform()->SetLocalPosition(640, 360);

	// Show test screen.
	UIScreenController::GetInstance()->ShowView<FrameworkTestScreen>();

	// Start framework
	RenkoFramework::GetInstance()->Start();
}

#endif