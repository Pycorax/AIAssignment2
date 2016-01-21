#include "Waypoint.h"

Waypoint::Waypoint(string id, Vector2 pos, Mesh* mesh) : m_next(NULL), m_id(id)
{
	SetMesh(mesh);
	m_transforms.Translation = pos;
}


Waypoint::~Waypoint()
{
}

void Waypoint::SetPos(Vector2 pos)
{
	GameObject2D::SetPos(pos);
}

Vector2 Waypoint::GetPos()
{
	return m_transforms.Translation;
}

vector<Waypoint*>& Waypoint::GetNext()
{
	return m_next;
}

bool Waypoint::AddToNext(Waypoint * next)
{
	if (next == this) // Cannot add itself
	{
		return false;
	}
	m_next.push_back(next);
	return true;
}
