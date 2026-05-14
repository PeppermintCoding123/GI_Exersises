#pragma once

#include "sampling.h"

#include <glm/glm.hpp>

// -------------------------------------------------------------------
// Approximations

inline float fresnel_schlick(float cos_i, float index_of_refraction) {
    float R_0 = index_of_refraction;
    return R_0 + (1.0f - R_0) * powf(1.0f - cos_i, 5.0f);
}

// -------------------------------------------------------------------
// Dielectric materials

inline float fresnel_dielectric(float cos_wi, float ior_medium, float ior_material) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// -------------------------------------------------------------------
// Conductor materials

inline float fresnel_conductor(float cos_wi, float ior_material, float absorb) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}
