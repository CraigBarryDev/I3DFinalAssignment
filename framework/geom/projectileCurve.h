#include "../projectileMotion.h"

#ifndef PROJECTILE_CURVE_H
#define PROJECTILE_CURVE_H

typedef struct {
	vectorf* points;
	vectorf* normals;
	vectorf* tangents;
}projectileCurve;

projectileCurve genProjectileCurveParametric(const projectile* p, int nVertices);

void drawProjectileCurve(projectileCurve* p);
void destroyProjectileCurve(projectileCurve* p);

#endif