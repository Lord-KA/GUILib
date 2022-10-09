#include "sdlPlain.hpp"
#include "vector3f.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sphere.hpp"

#include <vector>

static const int wHeigth = 400;
static const int wWidth  = 600;
static const int sRad = 120;

static const int xC = wWidth / 2;
static const int yC = wHeigth / 2;

static const float LumIntence = 0.5;
static const float MaterialDiffuse = 0.7;
static const float Ambiance = 0.01;

static const size_t specularN = 10;


static const g::color LumColor = g::color::yellow;

class raytracer {
private:
    g::plain *window;
    g::vector3f Viewer;
    std::vector<g::object3d*> Objects;
    bool alive;

    g::material universe = {g::color::gray, 1, 0, 0, 0, 0};

public:
    raytracer()
    {
        window = new g::sdlPlain(wWidth, wHeigth, g::color::black);
        assert(window);
        Viewer = g::vector3f(0, 0, -100);
        g::material LumMaterial = {g::color::yellow, 1, 0, 0, 0, 1};
        g::sphere *Lum = new g::sphere({0, 0, -300}, 150, LumMaterial);
        Objects.push_back(Lum);

        g::material m1 = {g::color::blue, 1, 0.5, 0.4, 1.3, 0};
        g::sphere *s1 = new g::sphere({300, 300, 150}, 150, m1);
        Objects.push_back(s1);

        g::material m2 = {g::color::red, 1, 0.5, 0.7, 1.3, 0};
        g::sphere *s2 = new g::sphere({300, 300, 300}, 400, m2);
        Objects.push_back(s2);

        alive = true;
    }

    ~raytracer()
    {
        assert(window);
        delete window;
    }

    bool isAlive()
    {
        return alive;
    }

    void update()
    {
        for (int x = 0; x < wWidth; ++x) {
            for (int y = 0; y < wHeigth; ++y) {
                g::ray r(Viewer, x, y, 90, universe, Objects);
                (*window)(x, y) = r.trace();
            }
        }
        std::cerr << "HERE!\n";
        window->render();

        // Lumen.rotZ(0.001);

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                alive = false;
        }
    }
};
