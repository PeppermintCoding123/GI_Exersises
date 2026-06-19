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
        for (uint32_t i = 0; i < samples; ++i) {
            vec3 L(0);

            // TODO ASSIGNMENT4
            // - implement a pathtracer using next event estimation
            // - add russian roulette
            // - (optional, bonus) add multiple importance sampling

            context.fbo.add_sample(x, y, L);
        }
    }
};

static AlgorithmRegistrar<Pathtracer> registrar;
