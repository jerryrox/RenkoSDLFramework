#include "CursorInteractible.h"

#include "Input.h"
#include "Anime.h"
#include "UIWidget.h"
#include "Animator.h"

CursorInteractible::CursorInteractible() :
	GameObject(),
	isPressing(false),
	isCursorOver(false)
{
	cursorArea = { 0, 0, 100, 100 };
}

CursorInteractible::~CursorInteractible()
{
	GameObject::~GameObject();

	targetWidget = 0;
}

void CursorInteractible::Update(float deltaTime)
{
	if (targetWidget != 0)
	{
		Vector2 widgetPos = targetWidget->GetDrawPosition();
		Vector2 widgetSize = targetWidget->GetActualSize();
		SetCursorAreaPos((int)widgetPos.x, (int)widgetPos.y);
		SetCursorAreaSize((int)widgetSize.x, (int)widgetSize.y);
	}
}

bool CursorInteractible::UpdateInput()
{
	if (!isPressing)
	{
		if (IsCursorOnArea())
		{
			if (!isCursorOver)
			{
				isCursorOver = true;
				OnCursorOver();
			}
			if (Input::IsMouseDown())
			{
				isPressing = true;
				OnCursorPress();
			}
		}
		else
		{
			if (isCursorOver)
			{
				isCursorOver = false;
				OnCursorOut();
			}
		}
	}

	if(isPressing)
	{
		if (Input::IsMouseUp())
		{
			isPressing = false;
			OnCursorRelease();

			if (!IsCursorOnArea())
			{
				isCursorOver = false;
				OnCursorOut();
			}
			else
			{
				OnCursorClick();
			}
		}
		// Mouse exited from area while pressing.
		// This should release both pressing and cursor over state.
		else if(isCursorOver && !IsCursorOnArea())
		{
			isPressing = false;
			OnCursorRelease();
			isCursorOver = false;
			OnCursorOut();
		}
	}

	//return !isCursorOver && !isPressing && GameObject::OnUpdateInput();
	return true;
}

void CursorInteractible::SetCursorArea(int x, int y, int w, int h)
{
	SetCursorAreaPos(x, y);
	SetCursorAreaSize(w, h);
}

inline void CursorInteractible::SetCursorAreaPos(int x, int y)
{
	cursorArea.x = x;
	cursorArea.y = y;
}

inline void CursorInteractible::SetCursorAreaSize(int w, int h)
{
	cursorArea.w = w;
	cursorArea.h = h;
}

void CursorInteractible::SetTarget(UIWidget* target)
{
	targetWidget = target;
}

UIWidget* CursorInteractible::GetTarget() { return targetWidget; }

void CursorInteractible::OnCursorOver() {}

void CursorInteractible::OnCursorOut() {}

void CursorInteractible::OnCursorPress() {}

void CursorInteractible::OnCursorRelease() {}

void CursorInteractible::OnCursorClick() { Clicked.Invoke(); }

bool CursorInteractible::IsCursorOnArea()
{
	auto mousePos = Input::GetMousePosition();
	return mousePos.x > cursorArea.x &&
		mousePos.y > cursorArea.y &&
		mousePos.x < cursorArea.x + cursorArea.w &&
		mousePos.y < cursorArea.y + cursorArea.h;

}