#ifndef GOBJECT_H
#define GOBJECT_H

#include "Vector3.h"
#include "Mesh.h"

/******************************************************************************/
/*!
		Struct Transform:
\brief	Consists of 3 Vector3 that control Transformation (Translate, Rotate, Scale)
*/
/******************************************************************************/
struct Transform
{
	Vector3 Translation;			// Translate Vector
	Vector3 Rotation;				// Rotate Vector
	Vector3 Scale;					// Scale Vector

	Transform(void)
	{
		Scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	Transform(Vector3 translate, Vector3 rotate, Vector3 scale = Vector3(1.0f, 1.0f, 1.0f))
		: Translation(translate)
		, Rotation(rotate)
		, Scale(scale)
	{
	}

	bool operator==(Transform rhs)
	{
		return (Translation == rhs.Translation && Rotation == rhs.Rotation && Scale == rhs.Scale);
	}
};

class GameObject2D
{
protected:	// Variables
	Transform m_transforms;			// Stores this object's Transforms info
	Mesh* m__mesh;					// Stores this object's mesh
	int m_meshSpriteID;				// Stores the position of the sprite on a spritesheet. If -1, this is ignored.
	bool m_active;					// Controls if this object can be collided with

public:		// Functions
	GameObject2D(void);
	virtual ~GameObject2D(void);
	
	void Init(Mesh* mesh, Transform t);

	/*
	* Setters
	*/
	void SetPos(const Vector3 pos);
	void SetRot(const Vector3 rot);
	void SetScale(const Vector3 scale);
	void SetMesh(Mesh* _mesh);
	void SetActive(bool active);
	void SetMeshSpriteID(int id);

	/*
	* Getters
	*/
	Transform GetTransform(void) const;
	Mesh* GetMesh(void) const;
	bool GetActive(void) const;
	int GetMeshSpriteID(void) const;
};

#endif