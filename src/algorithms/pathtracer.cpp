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

struct Pathtracer : public Algorithm {
    inline static const std::string name = "Pathtracer";

    void sample_pixel(Context& context, uint32_t x, uint32_t y, uint32_t samples) {
        vec3 accum = vec3(0.f);
        for (uint32_t i = 0; i < samples; ++i) {
            // TODO ASSIGNMENT4
            // - implement a pathtracer using next event estimation
            // - add russian roulette
            // - (optional, bonus) add multiple importance sampling

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
                    // TODO: sample Light
                    const auto [light, pdf_light_source] = context.scene.sample_light_source(RNG::uniform<float>());
                    auto [Li, shadow_ray, pdf_light_sample] = light->sample_Li(hit.P, RNG::uniform<vec2>());
                    const float pdf_L = pdf_light_source * pdf_light_sample;
                    if (pdf_L <= 0.f) break;

                    if (pdf_L > 0.f && !context.scene.occluded(shadow_ray)){
                        L += Li * throughput * hit.f(-ray.dir, shadow_ray.dir) * fmaxf(0.f, dot(hit.N, shadow_ray.dir)) / pdf_L;
                    }

                    // contiue as in native
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

static AlgorithmRegistrar<Pathtracer> registrar;
