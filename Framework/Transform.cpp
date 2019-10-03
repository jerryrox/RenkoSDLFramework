#include "Transform.h"

#include "GameObject.h"

Transform::Transform(Transform* parent) :
	localPosition(0, 0),
	worldPosition(0, 0),
	localScale(1, 1),
	worldScale(1, 1),
	parent(0)
{
	this->parent = parent;
}

Transform::~Transform()
{
	parent = 0;
}

void Transform::SetLocalPosition(Vector2 pos) { SetLocalPosition(pos.x, pos.y); }
void Transform::SetLocalPosition(float x, float y)
{
	if (localPosition.x != x || localPosition.y != y)
	{
		localPosition.x = x;
		localPosition.y = y;
		rebuildWorldTransform = true;
	}
}

void Transform::SetLocalScale(Vector2 scale) { SetLocalScale(scale.x, scale.y); }
void Transform::SetLocalScale(float x, float y)
{
	if (localScale.x != x || localScale.y != y)
	{
		localScale.x = x;
		localScale.y = y;
		rebuildWorldTransform = true;
	}
}

Vector2 Transform::GetLocalPosition() { return localPosition; }

Vector2 Transform::GetLocalScale() { return localScale; }

Vector2 Transform::GetWorldPosition()
{
	if (rebuildWorldTransform)
		SignalParentForWorldTransform();
	return worldPosition;
}

Vector2 Transform::GetWorldScale()
{
	if (rebuildWorldTransform)
		SignalParentForWorldTransform();
	return worldScale;
}

Vector2 Transform::InverseTransformPoint(Vector2 point)
{
	Vector2 newPoint(point.x, point.y);
	newPoint.x -= worldPosition.x;
	newPoint.y -= worldPosition.y;
	newPoint.x /= worldScale.x;
	newPoint.y /= worldScale.y;
	return newPoint;
}

Vector2 Transform::TransformPoint(Vector2 point)
{
	Vector2 newPoint(point.x, point.y);
	newPoint.x *= worldScale.x;
	newPoint.y *= worldScale.y;
	newPoint.x += worldPosition.x;
	newPoint.y += worldPosition.y;
	return newPoint;
}

void Transform::Update(float deltaTime)
{
	if (rebuildWorldTransform)
		CalculateWorldTransform();
}

void Transform::SignalParentForWorldTransform()
{
	Transform* target = this;
	Transform* checking = target;
	while (true)
	{
		checking = checking->parent;
		if (checking == 0 || checking == target)
			break;
		if (checking->rebuildWorldTransform)
			target = checking;
	}
	if (target != 0)
		target->CalculateWorldTransform();
}

void Transform::CalculateWorldTransform()
{
	rebuildWorldTransform = false;

	// Apply parent's transform values.
	if (parent != 0)
	{
		Vector2 pwp = parent->worldPosition;
		Vector2 pws = parent->worldScale;

		worldPosition.x = pwp.x;
		worldPosition.y = pwp.y;
		worldScale.x = pws.x;
		worldScale.y = pws.y;

		worldPosition.x += localPosition.x * pws.x;
		worldPosition.y += localPosition.y * pws.y;
		worldScale.x *= localScale.x;
		worldScale.y *= localScale.y;
	}
	else
	{
		worldPosition.x = localPosition.x;
		worldPosition.y = localPosition.y;
		worldScale.x = localScale.x;
		worldScale.y = localScale.y;
	}

	// Signal children as well.
	auto children = gameObject->GetChildren();
	for(int i=0; i<(int)children->size(); i++)
		children->at(i)->GetTransform()->CalculateWorldTransform();
}