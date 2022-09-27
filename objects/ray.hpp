#pragma once

#include "object3d.hpp"
#include "sphere.hpp"

namespace g {
    class ray : public object3d {
    public:
        vector3f dir;

        ray(vector3f c, vector3f d, g::material m) : object3d(c, m), dir(d)
        {
            dir = dir.normalize();
        }

        ray(vector3f centr, float a, float b, float c, g::material m) : object3d(centr, m)
        {
            dir = {a, b, c};
            dir = dir.normalize();
        }

        float traverse(const sphere &s)
        {
            g::vector3f norm = s.center - center;
            float normDist = norm.dot(dir);
            float rayDist = norm.dot(norm);
            rayDist -= normDist * normDist;

            if (rayDist > s.rad * s.rad)
                return NAN;

            float insideDist = std::sqrt(s.rad * s.rad - rayDist);

            if (normDist - insideDist >= EPS)
                return normDist - insideDist;
            if (normDist + insideDist >= EPS)
                return normDist + insideDist;

            return NAN;
        }
    };
}
