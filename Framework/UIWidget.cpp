#include "UIWidget.h"

#include "Transform.h"

UIWidget::UIWidget() :
	UIDisplayer(),
	width(100),
	height(100),
	customScale(1),
	drawPos(0, 0),
	actualSize(0, 0),
	pivot(Pivot::Pivot_Center)
{
}

UIWidget::~UIWidget()
{
	UIDisplayer::~UIDisplayer();
}

void UIWidget::SetWidth(int width) { SetSize(width, height); }

void UIWidget::SetHeight(int height) { SetSize(width, height); }

void UIWidget::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

int UIWidget::GetWidth() { return width; }

int UIWidget::GetHeight() { return height; }

Vector2 UIWidget::GetDrawPosition() { return drawPos; }

Vector2 UIWidget::GetActualSize() { return actualSize; }

void UIWidget::SetPivot(Pivot pivot) { this->pivot = pivot; }

Pivot UIWidget::GetPivot() { return pivot; }

void UIWidget::Render(Buffer* buffer)
{
	Transform* transform = GetTransform();
	drawPos = transform->GetWorldPosition();
	Vector2 scale = transform->GetWorldScale();
	actualSize.x = width * scale.x * customScale;
	actualSize.y = height * scale.y * customScale;

	switch (pivot)
	{
	case Pivot_TopLeft: break;
	case Pivot_Top:
		drawPos.x -= actualSize.x / 2;
		break;
	case Pivot_TopRight:
		drawPos.x -= actualSize.x;
		break;
	case Pivot_Left:
		drawPos.y -= actualSize.y / 2;
		break;
	case Pivot_Center:
		drawPos.x -= actualSize.x / 2;
		drawPos.y -= actualSize.y / 2;
		break;
	case Pivot_Right:
		drawPos.x -= actualSize.x;
		drawPos.y -= actualSize.y / 2;
		break;
	case Pivot_BottomLeft:
		drawPos.y -= actualSize.y;
		break;
	case Pivot_Bottom:
		drawPos.x -= actualSize.x / 2;
		drawPos.y -= actualSize.y;
		break;
	case Pivot_BottomRight:
		drawPos.x -= actualSize.x;
		drawPos.y -= actualSize.y;
		break;
	}

	// Let the derived classes handle their own drawing stuffs.
	Draw(buffer, scale);
}