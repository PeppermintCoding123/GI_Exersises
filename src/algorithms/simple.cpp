#include "driver/context.h"
#include "gi/algorithm.h"
#include "gi/hit.h"
#include "gi/light.h"
#include "gi/random.h"
#include "gi/ray.h"
#include "gi/scene.h"

using namespace std;
using namespace glm;

struct SimpleRenderer : public Algorithm {
    inline static const std::string name = "SimpleRenderer";

    void sample_pixel(Context& context, uint32_t x, uint32_t y, uint32_t samples) {
        // some shortcuts
        const Camera& cam = context.cam;
        const Scene& scene = context.scene;
        Framebuffer& fbo = context.fbo;
        const size_t w = fbo.width(), h = fbo.height();

        // TODO ASSIGNMENT1
        // - add and initialize random samplers
        // - apply supersampling over #samples and DOF using your samplers
        /*UniformSampler2D pixel_sampler = UniformSampler2D();
        pixel_sampler.init(samples);

        // Q: how to pass sample to Camera::view_ray
        Ray ray = cam.view_ray(x, y, w, h, pixel_sampler.next());

        // FYI: Framebuffer automatically averages per pixel colors in Framebuffer::add_saple

        // in Camera::apply_DOF
        UniformSampler2D dof_sampler = UniformSampler2D();
        dof_sampler.init(samples);
        cam.apply_DOF(ray, dof_sampler.next());*/
        auto sampler = UniformSampler2D();
        sampler.init(samples);
        auto lens_sampler = UniformSampler2D();
        lens_sampler.init(samples);
        auto light_select_sampler = UniformSampler1D();
        light_select_sampler.init(scene.lights.size());
        auto light_pos_sampler = UniformSampler2D();
        light_pos_sampler.init(samples);
        

        vec3 L(0);

        // setup a view ray
        Ray ray = cam.view_ray(x, y, w, h, sampler.next(), lens_sampler.next());

        // intersect main ray with scene
        const SurfaceHit hit = scene.intersect(ray);

        // check if a hit was found
        if (hit.valid) {
            if (hit.is_light()) { // direct light source hit
                L = hit.Le();
            } else { // surface hit -> shading
                // TODO ASSIGNMENT1
                // add area light shading via the rendering equation from the assignment sheet
                // hint: use the following c++17 syntax to capture multiple return values:
                const auto [light_ptr, ignore_me] = scene.sample_light_source(light_select_sampler.next());
                auto [Li, shadow_ray, ignore_me2] = light_ptr->sample_Li(hit.P, light_pos_sampler.next());
                bool occluded = scene.occluded(shadow_ray);
                if (occluded){
                    L = hit.albedo() * 0.0f;
                }else{
                    L = hit.albedo() * Li; 
                    
                }
                
            }
        } else { // ray esacped the scene
            L = scene.Le(ray);
        }

        // add result to framebuffer
        fbo.add_sample(x, y, L);

    }
};

static AlgorithmRegistrar<SimpleRenderer> registrar;
