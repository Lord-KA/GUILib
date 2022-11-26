#pragma once

#include "ray.hpp"

namespace g {
    class sphere : public object3d {
    public:
        float rad;

        sphere(vector3f c, float r, g::material m) : object3d(c, m), rad(r) {}

        color trace(const ray &r) const override
        {
            if (material.isLumen)
                return material.color * material.intence;

            vector3f normal = (r.contact - center).normalize();
            vector3f reflected = (r.dir - 2 * normal * r.dir.dot(normal)).normalize();

            float cosAlpha = std::max(normal.dot(r.dir), 0.f);
            float sq_tgAlpha = (1 - cosAlpha * cosAlpha) / (cosAlpha * cosAlpha);

            float coeff = material.restit / r.material.restit;    // Brewster's angle coeff

            if (sq_tgAlpha < coeff * coeff)
                return ray(r, reflected).trace();

            float sinBeta = std::sqrt(1 - cosAlpha * cosAlpha) * r.material.restit / material.restit;
            float cosBeta = std::sqrt(1 - sinBeta * sinBeta);

            float refl = material.reflect(r.material);
            assert(0 <= refl && refl <= 1);

            return refl * ray(r, reflected).trace() + (1 - refl) * ray(r, r.dir, material).trace(); //TODO add refl angle
        }

        float traverse(const ray &r) const override
        {
            float discr = (r.dir.dot(r.base - center));
            discr *= discr;
            discr -= ((r.base - center).dot(r.base - center) - rad * rad);
            if (discr < 0)
                return NAN;
            float dist = (-1 * (r.dir.dot(r.base - center)) - std::sqrt(discr));
            return dist;
        }
    };
}
