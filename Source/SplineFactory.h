#ifndef SPLINEFACTORY_H
#define SPLINEFACTORY_H

#include <glm/vec2.hpp>
#include "ParsingHelper.h"
#include "SplineModel.h"

class SplineFactory {

public:
	static SplineModel* LoadSpline(ci_istringstream& iss);

private:

	/**
	 * Random control points count variation of y (used as max) - x (used as min)
	 */
	static const glm::vec2 controlPointsCount;

	/**
	 * Random control points minimum x and y variation
	 */
	static const glm::vec2 deltaMinControlPoint;
	
	/**
	 * Random control points maximum x and y variation
	 */
	static const glm::vec2 deltaMaxControlPoint;

	/**
	 * Create random control points for the spline
	 */
	static void makeControlPoints(SplineModel& spline);

	/**
	 * The number of triangle strips per segment.
	 *
	 * A segment is control points i,i+1,..,i+3 and variable t
	 * where 0 <= t <= 1.
	 */
	static const int triangleStripSegmentCount;

	/***
	 * The width of the spline track.
	 */
	static const float trackWidth;

	/**
	 * Create the triangle strip for the spline.
	 */
	static void makeTriangleStrip(SplineModel& spline);
};

#endif