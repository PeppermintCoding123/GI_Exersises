#include "driver/context.h"
#include "gi/algorithm.h"
#include "gi/color.h"
#include "gi/light.h"
#include "gi/material.h"
#include "gi/mesh.h"
#include "gi/random.h"
#include "gi/ray.h"
#include "gi/timer.h"

using namespace std;
using namespace glm;

struct NaivePathtracer : public Algorithm {
    inline static const std::string name = "NaivePathtracer";

    void sample_pixel(Context& context, uint32_t x, uint32_t y, uint32_t samples) {
    vec3 accum = vec3(0.f);

    for (uint32_t s = 0; s < samples; ++s) {
                
        // TODO ASSIGNMENT4
        // - implement a (naive) pathtracer using BRDF sampling
        // - add russian roulette
        
        // set up ray
        // bounce through scene with BRDF
        // do until hit.is_light() == true
        // -> compute transported radiance with throughput & hit.Le() or Light:: Le()
        // Terminate when max depth or light
        
        // setup view ray
        Ray ray = context.cam.view_ray(
                    x, y, context.fbo.width(), context.fbo.height(), RNG::uniform<vec2>(), RNG::uniform<vec2>()
        );

        vec3 throughput = vec3(1.f);
        vec3 L = vec3(0.f);

        for (int depth = 0; depth < context.MAX_CAM_PATH_LENGTH; ++depth) {
            // russian roulett
            if (throughput[0] < context.RR_THRESHOLD || throughput[1] < context.RR_THRESHOLD || throughput[2] < context.RR_THRESHOLD){
                float p = 0.5;
                if(RNG::uniform<float>() < p){
                    throughput = vec3(0.f);
                }
                float throughput = (throughput - p) / (1-p);
            }

            SurfaceHit hit = context.scene.intersect(ray);

            // Hit a light source
            if (hit.is_light() && hit.valid) {
                // use AreaLight
                vec3 Le = hit.valid ? hit.Le() : context.scene.Le(ray);
                L += throughput * Le;
                break;
            }
            if (hit.is_light() && !hit.valid) {
                // use SkyLight
                vec3 Le = context.scene.Le(ray); // environment/ambient
                L += throughput * Le;
                break;
            }
            if (hit.valid){
                const auto [brdf, w_i, pdf] = hit.sample(-ray.dir, RNG::uniform<vec2>());
                if (pdf <= 0.f) break;

                float cos_theta = std::max(0.f, dot(hit.N, w_i));
                vec3 throughput_next = throughput * brdf * cos_theta / pdf;

                ray = Ray(hit.P, w_i);
                throughput = throughput_next;
            }
        }

        // Accumulate to framebuffer (ensuring non-negative)
        accum += max(vec3(0.f), L);
    }

    // Average over samples and write to framebuffer
    vec3 final = accum / float(samples);
    context.fbo.add_sample(x, y, final);
    }
};

static AlgorithmRegistrar<NaivePathtracer> registrar;
