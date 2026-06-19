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
        for (uint32_t i = 0; i < samples; ++i) {
            vec3 L(0);

            // TODO ASSIGNMENT4
            // - implement a (naive) pathtracer using BRDF sampling
            // - add russian roulette

            context.fbo.add_sample(x, y, L);
        }
    }
};

static AlgorithmRegistrar<NaivePathtracer> registrar;
