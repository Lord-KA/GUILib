#include "sdlPlain.hpp"
#include "vector3f.hpp"
#include "color.hpp"

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

class sphere {
private:
    g::plain *window;
    g::vector3f Lumen;
    g::vector3f Viewer;
    bool alive;

    g::color calcColor(g::vector3f pos)
    {
        g::vector3f Normal = pos.normalize();
        g::vector3f LumNorm = Lumen.normalize();
        g::vector3f ViewNorm = Viewer.normalize();

        float cosAlpha = std::max(Normal.dot(LumNorm), 0.f);

        g::vector3f Relf = (2.f * cosAlpha * Normal - LumNorm).normalize();

        float cosBeta = std::max(ViewNorm.dot(Relf), 0.f);

        float specular = std::pow(cosBeta, specularN);

        float light = cosAlpha * LumIntence +
                      MaterialDiffuse * Ambiance +
                      specular;

        light = std::min(light, 1.f);

        return LumColor * light;
    }

public:
    sphere()
    {
        window = new g::sdlPlain(wWidth, wHeigth, g::color::black);
        assert(window);
        Lumen = g::vector3f(300, 300, 300);
        Viewer = g::vector3f(200, 80, 80);
        alive = true;
    }

    ~sphere()
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
                if ((xC - x) * (xC - x) + (yC - y) * (yC - y) < sRad * sRad) {  //
                    int z = std::sqrt(sRad * sRad - (xC - x) * (xC - x) - (yC - y) * (yC - y));
                    g::vector3f pos(x, y, z);
                    (*window)(x, y) = calcColor(pos);
                } else {
                    (*window)(x, y) = g::color::gray;
                }
            }
        }
        window->render();

        Lumen.rotZ(0.001);

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                alive = false;
        }
    }
};
