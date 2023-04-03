#pragma once


struct vec3
{
    float x, y, z;
};

struct point3
{
    float x, y, z;
};

struct angle
{
    float pitch, yaw;
};


float calculateVec3BaseLength(vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float calculateTriangleBase(point3 v1, point3 v2);
void normaliseVector(vec3& v);
float calculatePoint3Distance(point3 a, point3 b);
float calculateVec3Length(vec3 v);
