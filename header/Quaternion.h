#pragma once


typedef struct {
	float t, x, y, z;
} qtrn;

const float qThreshold = (float)1.0e-5;

qtrn qFromAngleAxis(float theta, vec4 axis);
void qToAngleAxis(const qtrn& q, float& theta, vec4& axis);
void qClean(qtrn& q);
float qQuadrance(const qtrn& q);
float qNorm(const qtrn& q);
qtrn qNormalize(const qtrn& q);
qtrn qConjugate(const qtrn& q);
qtrn qInverse(const qtrn& q);
qtrn qMultiply(const qtrn& q, const float s);
qtrn qMultiply(const qtrn& q0, const qtrn& q1);
void qGLRotationMatrix(const qtrn& q, mat4 matrix);
qtrn qLerp(const qtrn& q0, const qtrn& q1, float k);
qtrn qSlerp(const qtrn& q0, const qtrn& q1, float k);
bool qEqual(const qtrn& q0, const qtrn& q1);
void qPrint(const std::string& s, const qtrn& q);
void qPrintAngleAxis(const std::string& s, const qtrn& q);
