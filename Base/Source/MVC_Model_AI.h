#ifndef MVC_MODEL_AI_H
#define MVC_MODEL_AI_H

// Inheritance Includes
#include "MVC_Model.h"

// Other Includes
#include "Guard.h"
#include "SpyNPC.h"
#include "Car.h"

class MVC_Model_AI : public MVC_Model
{
private:
	enum E_ENV_OBJECT
	{
		EO_ROAD,
		EO_BUILDING_LEFT,
		EO_BUILDING_MID,
		EO_BUILDING_RIGHT,
		EO_ROAD_STRIP_1,
		EO_ROAD_STRIP_2,
		EO_ROAD_STRIP_3,
		EO_TOTAL
	};

	enum E_TEXT_OBJECT
	{
		TO_SPY_STATE,
		TO_GUARD_STATE,
		TO_BOMB_COUNT,
		TO_TOTAL
	};

private:
	// Text Output
	TextObject* m_textObjects[TO_TOTAL];

	// Environment Objects
	GameObject2D* m_envObjects[EO_TOTAL];

	// Target
	GameObject2D* m_bombSite;

	// Guards
	static const int S_MAX_GUARDS;
	vector<Guard*> m_guardList;
	vector<Waypoint*> m_spawnPoints;
	vector<Waypoint*> m_waypointList;
	Waypoint* m_worldMap;
	bool m_showWaypoints;
	float m_toggleWaypointTimer;
	static const float S_TIME_TILL_TOGGLE_WAYPOINT;

	// Spy
	SpyNPC m_spy;

	// Car
	NPCCar m_car;

public:
	MVC_Model_AI(string configSONFile);
	~MVC_Model_AI();

	void Init(void);
	void Update(double dt);
	void Exit(void);
	void Reset(void);

	void InitGuards(void); // Init guards
	void InitWaypointMap(void); // Init waypoint map

private:
	void initText(void);
	void initEnvironment(void);

	// Input
	void processKeyAction(double dt);
	// Resizing Code
	void onResolutionChanged(int oldViewWidth, int oldViewHeight);

	//bool lineCircle(Guard* go1, Guard* go2);
	//bool lineLine(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2);
};

#endif