#pragma once



struct vec3
{
    float x, y, z;
};

typedef vec3 point3;

struct angle
{
    float pitch, yaw;
};


float calculateVec3BaseLength(vec3 v);
float calculateTriangleBase(point3 v1, point3 v2);
void normaliseVector(vec3& v);
float calculatePoint3Distance(point3 a, point3 b);
float calculateVec3Length(vec3 v);
