#include "brdf.h"

#include "fresnel.h"
#include "hit.h"
#include "material.h"
#include "sampling.h"

// ----------------------------------------------------------------------------------------------
// Diffuse lambertian reflection

glm::vec3 LambertianReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> LambertianReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float LambertianReflection::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Diffuse lambertian transmission

glm::vec3 LambertianTransmission::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> LambertianTransmission::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float LambertianTransmission::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Perfect specular reflection

glm::vec3 SpecularReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> SpecularReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float SpecularReflection::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Perfect specular transmission

glm::vec3 SpecularTransmission::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> SpecularTransmission::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float SpecularTransmission::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Specular fresnel

glm::vec3 SpecularFresnel::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> SpecularFresnel::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float SpecularFresnel::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Phong

glm::vec3 SpecularPhong::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> SpecularPhong::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float SpecularPhong::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Microfacet distribution helper functions

inline float GGX_D(const float NdotH, float roughness) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

inline float GGX_G1(const float NdotV, float roughness) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

glm::vec3 GGX_sample(const glm::vec2& sample, float roughness) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

inline float GGX_pdf(float D, float NdotH, float HdotV) {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Microfacet reflection

glm::vec3 MicrofacetReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> MicrofacetReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float MicrofacetReflection::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ------------------------------------------------
// Microfacet transmission

glm::vec3 MicrofacetTransmission::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> MicrofacetTransmission::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float MicrofacetTransmission::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// -------------------------------------------------------------------------------------------
// Layered

glm::vec3 LayeredSurface::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

std::tuple<glm::vec3, glm::vec3, float> LayeredSurface::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

float LayeredSurface::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Metal

glm::vec3 MetallicSurface::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}
