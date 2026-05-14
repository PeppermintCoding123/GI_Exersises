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
            // as in simple.cpp
            const Scene& scene = context.scene;
            const Camera& cam = context.cam;
            Framebuffer& fbo = context.fbo;
            const size_t w = fbo.width(), h = fbo.height();  
    
            Ray ray = cam.view_ray(x, y, w, h);
            const SurfaceHit hit = scene.intersect(ray);
    
            auto light_select_sampler = UniformSampler1D();
            light_select_sampler.init(scene.lights.size());
            auto light_pos_sampler = HammersleySampler2D();
            light_pos_sampler.init(samples);
            MicrofacetReflection brdf = MicrofacetReflection();

            for (uint32_t i = 0; i < samples; ++i) {
                // light
                glm::vec3 L(0);
                if (hit.valid) {
                    if (hit.is_light()) { // direct light source hit
                        L = hit.Le();
                    } else { // surface hit -> shading
                        const auto [light_ptr, ignore_me] = scene.sample_light_source(light_select_sampler.next());
                        auto [Li, shadow_ray, ignore_me2] = light_ptr->sample_Li(hit.P, light_pos_sampler.next());
                        vec3 w_o = -ray.dir; // out direction is the view ray direction
                        vec3 w_i = glm::normalize(Li - hit.P); // in direction is towards the light
        
                        // L_e with glm::vec3 MicrofacetReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const 
                        
                        L += scene.Le(ray) * brdf.f(hit, w_o, w_i) * glm::dot(hit.N, w_i) / uniform_hemisphere_pdf();
                    }
                } else { // ray esacped the scene
                    L = scene.Le(ray);
                }
            }
    }
};

static AlgorithmRegistrar<BRDFImportance> registrar;
