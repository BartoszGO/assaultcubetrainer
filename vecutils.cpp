
#include "vecutils.h"
#include<math.h>





float calculateVec3BaseLength(vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}


float calculateTriangleBase(point3 v1, point3 v2)
{
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

void normaliseVector(vec3& v)
{
    float length = calculateVec3Length(v);
    if (length)
    {
        v.x = v.x / length;
        v.y = v.y / length;
        v.z = v.z / length;
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