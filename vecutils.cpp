

#include<math.h>


struct vec3
{
    float x, y, z;
};

struct point3
{
    float x, y, z;
};


float calculateVectorLength(vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}


float calculateTriangleBase(vec3 v1, vec3 v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

void normaliseVector(vec3& v)
{
    float length = calculateVectorLength(v);
    if (length)
    {
        v.x = v.x / length;
        v.y = v.y / length;
    }
}


float calculatePoint3Distance(point3 a, point3 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}


float calculateVec3Length(vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}