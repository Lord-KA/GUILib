#pragma once

#include "vector3f.hpp"
#include "material.hpp"

#include <vector>

namespace g {

    static const size_t MAX_REFL_CNT = 6;

    class ray;

    class object3d {
    public:
        g::vector3f center;
        g::material material;

        object3d(g::vector3f c, g::material m) : center(c), material(m) {}

        // virtual void setPosition(g::vector3f pos) = 0;
        // virtual void move(g::vector3f delta) = 0;

        // virtual void outline() const = 0;

        virtual g::color trace(const ray &r) const = 0;
        virtual float traverse(const ray &r) const = 0;
    };

    class ray {
    public:
        vector3f base;
        vector3f dir;

        g::material material;
        vector3f contact;
        size_t refl_cnt = 0;
        const std::vector<g::object3d *> &objects;

        ray(vector3f b, vector3f d, size_t r, g::material m, const std::vector<object3d*> &o) : base(b), dir(d), refl_cnt(r), material(m), objects(o)
        {
            dir = dir.normalize();
        }

        ray(vector3f base, float a, float b, float c, g::material m, const std::vector<object3d*> &o) : base(base), material(m), objects(o)
        {
            dir = {a, b, c};
            dir = dir.normalize();
        }

        ray(const ray &other, vector3f newDir) : dir(newDir.normalize()), base(other.contact), objects(other.objects), material(other.material), refl_cnt(other.refl_cnt + 1) {}

        ray(const ray &other, vector3f newDir, g::material m) : dir(newDir.normalize()), base(other.contact), objects(other.objects), material(m), refl_cnt(other.refl_cnt + 1) {}

        g::color trace()
        {
            if (refl_cnt > MAX_REFL_CNT)
                return material.color * material.intence;

            float minDist = NAN;
            size_t objId = -1;
            for (size_t id = 0; id < objects.size(); ++id) {
                float contactDist = objects[id]->traverse(*this);
                if (isnan(contactDist) or contactDist < 0)
                    continue;
                if (isnan(minDist) or minDist > contactDist) {
                    minDist = contactDist;
                    objId = id;
                }
            }
            if (objId == -1)
                return material.color * material.intence;

            contact = base + minDist * dir;
            return objects[objId]->trace(*this) + (minDist * material.absorb * material.intence) * material.color;
        }
    };
}
