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
                        // sample
                        // how to monte-carlo-integration?
                        const vec3 w_o = -ray.dir;
                        const vec3 w_i_tangent_space = uniform_sample_hemisphere(RNG::uniform<vec2>());
                        const vec3 w_i = tangent_to_world(hit.N, w_i_tangent_space);
                        const float cos_i = glm::max(0.f, dot(hit.N, w_i));
                    
                        // - draw a uniform random sample on the hemisphere in tangent space and transform it into world-space
                        // - intersect the ray with the scene and check if you hit a light source
                        Ray secondary_ray(hit.P, w_i);
                        const SurfaceHit hit = scene.intersect(secondary_ray);
                        if (hit.valid && hit.is_light()) {
                            // - if a light source was hit, compute the irradiance via the given equation
                            L = hit.Le() * hit.f(w_o, w_i) *  cos_i / uniform_hemisphere_pdf();
                        }
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
