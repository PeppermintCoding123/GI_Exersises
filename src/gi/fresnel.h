#pragma once

#include "sampling.h"

#include <glm/glm.hpp>

// -------------------------------------------------------------------
// Approximations

inline float fresnel_schlick(float cos_i, float index_of_refraction) {
    // TODO ASSIGNMENT2
    // implement Schlick's approximation
    const auto R0 = std::pow((1 - index_of_refraction) / (1 + index_of_refraction), 2.0f);
    return R0 + (1.0f + R0) * std::pow(1 - cos_i, 5.0f);
}

// -------------------------------------------------------------------
// Dielectric materials

inline float fresnel_dielectric(float cos_wi, float ior_medium, float ior_material) {
    // simply use schlick's approximation for now (for the LayeredSurface BRDF to work)
    return fresnel_schlick(cos_wi, ior_material);
}

// -------------------------------------------------------------------
// Conductor materials

inline float fresnel_conductor(float cos_wi, float ior_material, float absorb) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}
