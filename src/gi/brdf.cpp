#include "brdf.h"

#include "fresnel.h"
#include "hit.h"
#include "material.h"
#include "sampling.h"

// ----------------------------------------------------------------------------------------------
// Diffuse lambertian reflection

glm::vec3 LambertianReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    // add check
    return hit.albedo() * (float)(1.0f / M_PI);

}

std::tuple<glm::vec3, glm::vec3, float> LambertianReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    // TODO
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
    return hit.albedo() * (float)(1.0f / M_PI);
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
    // r = 2 * (n . l) * n - l
    // l = -w_i
    // n = hit.N
    float cos_i = glm::dot(w_i, hit.N);
    glm::vec3 r = 2.0f * cos_i * hit.N + w_i; 
    // n_shiny = hit.mat
    float n_shiny = fresnel_schlick(cos_i, hit.roughness());// TODO: use fresnels term => Schlicks approximation from scr/gi/fresnel.h
    // Q: what index of refraction should we use?
    float reflect_vect_light = powf(glm::dot(w_o, r), n_shiny); 
    glm::vec3 temp =  hit.albedo() * reflect_vect_light;
    float conserve_energy = (2.0f * M_PI)/(n_shiny + .0f); // lecture 4 page 10

    // TODO: get from friend
    return temp * conserve_energy;
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
    // From micorofacet paper
    float alpha_g = 0.2f;
    // X^+ = 1 if 1 else 0 -> Q: m * n is 1 for us?
    float theta_m = NdotH;
    float D = (alpha_g * alpha_g) / (M_PI * powf(cosf(theta_m), 4.0f) * powf(powf(alpha_g, 2.0f) + powf(tan(theta_m), 2.0f), 2.0f));
    return D;

}

inline float GGX_G1(const float NdotV, float roughness) {
    // From micorofacet paper
    float alpha_g = 0.2f;
    float theta_v = NdotV;
    // X^+ = 1 if 1 else 0 -> Q: v*m / v * n is 1 for us?
    float G1 = 2.0f / (1.0f + sqrtf(1.0f + powf(alpha_g, 2.0f) * powf(tan(theta_v), 2.0f)));
    return G1; 
}

glm::vec3 GGX_sample(const glm::vec2& sample, float roughness) {
    //TODO:hier
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
    glm::vec3 v = w_o;
    glm::vec3 h = glm::normalize(w_i + w_o); // halfway vector
    float cos_i = glm::dot(w_i, hit.N);
    float denominator = 4.0f * (cos_i * glm::dot(w_o, hit.N)); // angles of incident & exiting towards light
    float f = (GGX_G1(glm::dot(v, hit.N), hit.roughness()) * GGX_D(glm::dot(hit.N, h), hit.roughness()) * fresnel_schlick(cos_i, hit.roughness())) / denominator;
    return f * hit.N;
    // Q: what is meant by index odf reflection
    // Q: expected to multiply f with a vector?
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
