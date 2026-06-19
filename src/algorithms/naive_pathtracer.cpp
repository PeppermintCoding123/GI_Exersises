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
        // if end of context, add 0
        /*if (context.MAX_CAM_PATH_LENGTH > 0){
            vec3 L(0);
            context.fbo.add_sample(x, y, L);
        }

        context.MAX_CAM_PATH_LENGTH -= 1;*/
        for (uint32_t i = 0; i < samples; ++i) {
            vec3 L(0);

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
            // intersect main ray with scene
            const SurfaceHit hit = context.scene.intersect(ray);
            if (hit.is_light()){
                if(hit.valid){
                    // use AreaLight
                    L = hit.Le() ;
                } else {
                    // use SkyLight
                    L = context.scene.Le(ray);
                }
            } else {
                if(hit.valid){
                    const uint32_t N = 1; // Q: how to determine the N here?
                    for (uint i = 0; i < N; ++i) {
                        const auto [brdf, w_i, pdf] = hit.sample(-ray.dir, RNG::uniform<vec2>());
                        Ray secondary_ray = Ray(hit.P, w_i);
                        const SurfaceHit secondary_hit = context.scene.intersect(secondary_ray);
                        if (secondary_hit.valid && secondary_hit.is_light() && dot(secondary_hit.N, -w_i) > 0)
                            L += secondary_hit.Le() * brdf * fmaxf(0.f, dot(hit.N, secondary_ray.dir)) / (N * pdf); // add throughput to the Le here...
                    }
                    L /= float(N);
                } else { 
                    // terminate if no light source found
                    context.abort;
                } 
            }
            
            // add result to framebuffer
            context.fbo.add_sample(x, y, L);
        }
    }
};

static AlgorithmRegistrar<NaivePathtracer> registrar;
