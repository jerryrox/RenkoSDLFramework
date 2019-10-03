#pragma once

#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "Component.h"
#include "Vector2.h"

class Transform :
	public Component
{
public:
	Transform(Transform* parent = 0);
	~Transform() override;

	// Sets the local position of the transform.
	void SetLocalPosition(Vector2 pos);
	// Sets the local position of the transform.
	void SetLocalPosition(float x, float y);

	// Sets the local scale of the transform.
	void SetLocalScale(Vector2 scale);
	// Sets the local scale of the transform.
	void SetLocalScale(float x, float y);

	// Returns the local position of the transform.
	Vector2 GetLocalPosition();

	// Returns the local scale of the transform.
	Vector2 GetLocalScale();

	// Returns the world position of the transform.
	Vector2 GetWorldPosition();

	// Returns the world scale of the transform.
	Vector2 GetWorldScale();

	// Converts the specified world position to local position.
	Vector2 InverseTransformPoint(Vector2 point);

	// Converts the specified local position to world position.
	Vector2 TransformPoint(Vector2 point);

	void Update(float deltaTime) override;

private:
	// Local position of the object.
	Vector2 localPosition;
	// World position of the object.
	Vector2 worldPosition;
	// Local scale of the object.
	Vector2 localScale;
	// World scale of the object.
	Vector2 worldScale;

	// Transform component of the parent.
	Transform* parent;

	// Whether the world transform values should be recalculated.
	bool rebuildWorldTransform;


	// Signals the top-most parent who needs to refresh world transform for calculation now.
	void SignalParentForWorldTransform();

	// Calculates world transform values of thie transform.
	void CalculateWorldTransform();
};

#endif