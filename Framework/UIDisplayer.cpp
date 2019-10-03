#include "UIDisplayer.h"

#include "Debug.h"

#include <typeinfo>

UIDisplayer::UIDisplayer() :
	Component(),
	parentDisplayer(0)
{
	localColor.r = localColor.g = localColor.b = localColor.a = 255;
}

UIDisplayer::~UIDisplayer()
{
	Component::~Component();

	parentDisplayer = 0;
}

void UIDisplayer::Init()
{
	Component::Init();

	// Traverse upwards and find parent displayer
	GameObject* obj = gameObject;
	while (parentDisplayer == 0)
	{
		obj = obj->GetParent();
		if (obj == 0)
			break;
		parentDisplayer = obj->GetComponent<UIDisplayer>();
	}
}

void UIDisplayer::SetAlpha(Uint8 alpha) { localColor.a = alpha; }

void UIDisplayer::SetAlpha(float alpha)
{
	if (alpha < 0)
		alpha = 0;
	else if (alpha > 1)
		alpha = 1;
	SetAlpha((Uint8)(alpha * 255.0f));
}

void UIDisplayer::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	localColor.r = r;
	localColor.g = g;
	localColor.b = b;
}

void UIDisplayer::SetColor(SDL_Color* color) { SetColor(color->r, color->g, color->b); }

Uint8 UIDisplayer::GetColorR() { return localColor.r; }
Uint8 UIDisplayer::GetColorG() { return localColor.g; }
Uint8 UIDisplayer::GetColorB() { return localColor.b; }
Uint8 UIDisplayer::GetAlpha() { return localColor.a; }

float UIDisplayer::GetAlphaF() { return localColor.a / 255.0f; }

Uint8 UIDisplayer::GetWorldAlpha() { return (Uint8)(GetWorldAlphaF() * 255.0f); }

float UIDisplayer::GetWorldAlphaF()
{
	if (parentDisplayer == 0)
		return localColor.a / 255.0f;
	return parentDisplayer->GetWorldAlphaF() * (localColor.a / 255.0f);
}

SDL_Color UIDisplayer::GetLocalColor() { return localColor; }

SDL_Color UIDisplayer::GetWorldColor() { return { localColor.r, localColor.g, localColor.b, GetWorldAlpha() }; }