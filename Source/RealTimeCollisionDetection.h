#ifndef REALTIMECOLLISION_H
#define REALTIMECOLLISION_H

#include <glm/glm.hpp>

/**
 * A collection of collision detection functions and structs from
 *
 * "Real Time Collision Detection" by Christer Ericson
 *
 */
namespace rtcd {

	static const float EPSILON = 0.0001f;

	// Region R = { x | (x - [a + (b - a)*t])^2 <= r }, 0 <= t <= 1
	struct Capsule {
		glm::vec3 a; // Medial line segment start point
		glm::vec3 b; // Medial line segment endpoint
		float r; // Radius
	};

	/**
	 * Returns true if the two capsules collide, otherwise false
	 */
	bool TestCapsuleCapsule(const Capsule& capsule1, const Capsule& capsule2);

	/**
	 * Computes closest points C1 and C2 of S1(s)=P1+s*(Q1-P1) and
	 * S2(t)=P2+t*(Q2--P2), returning s and t. Function result is suqared
	 * distance between S1(s) and S2(t)
	 */
	float ClosestPtSegmentSegment(
		const glm::vec3& p1, const glm::vec3& q1,
		const glm::vec3& p2, const glm::vec3& q2,
		float& s, float& t,
		glm::vec3& c1, glm::vec3& c2);
};

enum BoundingVolumeType {
	NIL_BV,
	// SPHERE,
	CAPSULE,
};

const char* BoundingVolumeTypeToStr[];

class BoundingVolume {

public:
	BoundingVolume() : mBoundingVolumeType(NIL_BV), mData(nullptr) {};

	BoundingVolumeType GetBoundingVolumeType() const { return mBoundingVolumeType; }
	void* GetData() const { return mData; }

	void setCapsule(const rtcd::Capsule& capsule) { mBoundingVolumeType = CAPSULE; mData = (void*) &capsule; }
private:
	BoundingVolumeType mBoundingVolumeType;
	void* mData;
};

/**
* Returns true if two bounding volumes intersect, otherwise false
*/
bool TestBoundingVolumes(const BoundingVolume& b1, const BoundingVolume& b2);

#endif