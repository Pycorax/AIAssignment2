#ifndef _RAYCAST_H_
#define _RAYCAST_H_

#include"Guard.h"

namespace Raycast
{
	bool lineLine(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2)
	{
		// Store the values for fast access and easy
		// equations-to-code conversion
		float x1 = a1.x, x2 = a2.x, x3 = b1.x, x4 = b2.x;
		float y1 = a1.y, y2 = a2.y, y3 = b1.y, y4 = b2.y;

		float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		// If d is zero, there is no intersection
		if (d == 0)
		{
			return false;
		}
		// Get the x and y
		float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
		float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
		float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

		// Check if the x and y coordinates are within both lines
		if (x < Math::Min(x1, x2) || x > Math::Max(x1, x2) ||
			x < Math::Min(x3, x4) || x > Math::Max(x3, x4)) return false;
		if (y < Math::Min(y1, y2) || y > Math::Max(y1, y2) ||
			y < Math::Min(y3, y4) || y > Math::Max(y3, y4)) return false;

		// Return the point of intersection
		return true;
	}

	bool lineCircle(Guard * caster, GameObject2D * target, GameObject2D** envObjList, int size) // go1 is the caster, go2 is the target
	{
		/*E is the starting point of the ray,
		L is the end point of the ray,
		C is the center of sphere you're testing against
		r is the radius of that sphere*/

		Vector3 E = caster->GetTransform().Translation; // Start point of ray
		Vector3 L = E + (caster->GetLookDir() * caster->GetView()->GetTransform().Scale.x * 0.5f); // End point of ray
		Vector3 C = target->GetTransform().Translation; // Center of sphere you're testing against
		float r = target->GetTransform().Scale.x * 0.5f; // Radius of sphere you're testing against

		bool hit = false;

		Vector3 d = L - E; // Dir of ray from start to end
		Vector3 f = E - C; // Vector from center sphere to ray start

		float a = d.Dot(d);
		float b = 2 * f.Dot(d);
		float c = f.Dot(f) - r*r;

		float discriminant = b*b - 4 * a*c;

		if (discriminant < 0)
		{
			// no intersection
			hit ;
		}
		else
		{
			// Ray didn't totally miss sphere, so there is a solution to the equation
			discriminant = sqrt(discriminant);

			// either solution may be on or off the ray so need to test both
			// t1 is always the smaller value, because BOTH discriminant and
			// a are nonnegative.
			float t1 = (-b - discriminant) / (2 * a);
			float t2 = (-b + discriminant) / (2 * a);

			// 3x HIT cases:
			//          -o->             --|-->  |            |  --|->
			// Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit), 

			// 3x MISS cases:
			//       ->  o                     o ->              | -> |
			// FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

			if (t1 >= 0 && t1 <= 1)
			{
				// t1 is the intersection, and it's closer than t2
				// (since t1 uses -b - discriminant)
				// Impale, Poke
				hit = true;
			}

			// here t1 didn't intersect so we are either started
			// inside the sphere or completely past it
			if (t2 >= 0 && t2 <= 1)
			{
				// ExitWound
				hit = true;
			}

			// no intn: FallShort, Past, CompletelyInside
			// hit = false; // Commented as it is already set and this would override data from above conditions
		}


		// Check for obstacle
		float distFromTarget = (caster->GetTransform().Translation - target->GetTransform().Translation).LengthSquared();
		for (int i = 0; i < size; ++i)
		{
			GameObject2D* e = envObjList[i];

			float distFromEO = (caster->GetTransform().Translation - e->GetTransform().Translation).LengthSquared();
			if (distFromEO > distFromTarget || e == envObjList[0]) // If EO is further away than target, don't check
			{
				continue;
			}

			Vector2 pos = e->GetTransform().Translation;
			Vector2 halfScale = e->GetTransform().Scale * 0.5f;

			Vector2 topLeftPoint(pos.x - halfScale.x, pos.y + halfScale.y); // Assuming no rotation, top left point
			Vector2 topRightPoint(pos.x + halfScale.x, pos.y + halfScale.y);
			Vector2 bottomLeftPoint(pos.x - halfScale.x, pos.y - halfScale.y);
			Vector2 bottomRightPoint(pos.x + halfScale.x, pos.y - halfScale.y);

			// If true, line is blocking target so no point checking further
			if (lineLine(E, L, topLeftPoint, topRightPoint)) // Top line check
			{
				return false;
			}
			if (lineLine(E, L, bottomLeftPoint, bottomRightPoint)) // Bottom line check
			{
				return false;
			}
			if (lineLine(E, L, topLeftPoint, bottomLeftPoint)) // Left line check
			{
				return false;
			}
			if (lineLine(E, L, topRightPoint, bottomRightPoint)) // Right line check
			{
				return false;
			}
		}

		return hit;
	}
}

#endif