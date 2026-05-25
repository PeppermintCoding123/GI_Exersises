#include "driver/context.h"
#include "gi/algorithm.h"
#include "gi/hit.h"
#include "gi/light.h"
#include "gi/random.h"
#include "gi/ray.h"
#include "gi/scene.h"

using namespace std;
using namespace glm;

struct BRDFImportance : public Algorithm {
    inline static const std::string name = "BRDFImportance";

    void sample_pixel(Context& context, uint32_t x, uint32_t y, uint32_t samples) {
        // some shortcuts
        Camera& cam = context.cam;
        Scene& scene = context.scene;
        Framebuffer& fbo = context.fbo;
        size_t w = fbo.width(), h = fbo.height();

        for (uint32_t i = 0; i < samples; ++i) {
            vec3 L(0);
            // setup view ray
            Ray ray = cam.view_ray(x, y, w, h, RNG::uniform<vec2>(), RNG::uniform<vec2>());
            // intersect main ray with scene
            const SurfaceHit hit = scene.intersect(ray);
            // check if a hit was found
            if (hit.valid) {
                if (hit.is_light())
                    L = hit.Le();
                else {
                    constexpr bool UNIFORM = true;
                    if (UNIFORM) {
                        // TODO ASSIGNMENT2
                        // implement Monte Carlo integration via uniform hemisphere sampling here
                        // - draw a uniform random sample on the hemisphere in tangent space and transform it into
                        // world-space
                        // - intersect the ray with the scene and check if you hit a light source
                        // - if a light source was hit, compute the irradiance via the given equation
                        L = hit.albedo();
                    } else {
                        // TODO ASSIGNMENT2
                        // implement Monte Carlo integration via BRDF imporance sampling here
                        // - sample the brdf (BRDF::sample) for a outgoing direction instead of uniform sampling of the
                        // hemisphere
                        // - intersect the ray with the scene and check if you hit a light source
                        // - if a light source was hit, compute the irradiance via the given equation
                        L = hit.albedo();
                    }
                }
            } else // ray esacped the scene
                L = scene.Le(ray);
            // add result to framebuffer
            fbo.add_sample(x, y, L);
        }
    }
};

static AlgorithmRegistrar<BRDFImportance> registrar;
