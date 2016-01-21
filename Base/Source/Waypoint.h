#ifndef _WAYPOINT_H
#define _WAYPOINT_H_

#include "GameObject2D.h"
#include <vector>

using std::vector;

class Waypoint : public GameObject2D
{

private:
	vector<Waypoint*> m_next;
	string m_id;

public:
	Waypoint(string id = "", Vector2 pos = Vector2::ZERO_VECTOR, Mesh* mesh = nullptr);
	virtual ~Waypoint();

	void SetPos(Vector2 pos);
	Vector2 GetPos();

	vector<Waypoint*>& GetNext();

	bool AddToNext(Waypoint* next);
};

#endif