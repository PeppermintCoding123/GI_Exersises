#include "brdf.h"

#include "fresnel.h"
#include "hit.h"
#include "material.h"
#include "sampling.h"

// ----------------------------------------------------------------------------------------------
// Diffuse lambertian reflection

glm::vec3 LambertianReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    // TODO ASSIGNMENT2
    // evaluate the (normalized!) lambertian diffuse BRDF
    if (glm::dot(hit.N, w_i) <= 0.0f || glm::dot(hit.N, w_o) <= 0.0f)
        return glm::vec3(0.0f);

    return hit.albedo() / float(M_PI);
    //return glm::vec3(0);

}

std::tuple<glm::vec3, glm::vec3, float> LambertianReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    // TODO ASSIGNMENT2
    // importance sample and evaluate the lambertian diffuse BRDF
    // set w_i to the sampled (world-space!) direction, pdf to the respective PDF and brdf to the evaluated BRDF
    const glm::vec3 w_i = glm::vec3(0);
    const glm::vec3 brdf = glm::vec3(0);
    const float pdf = 0.f;
    return {brdf, w_i, pdf};
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
    // TODO ASSIGNMENT2
    // evaluate the (normalized!) phong BRDF for the given in- and outgoing (world-space) directions
    // you may use hit.albedo() as the specular color here
    const float exponent = Material::exponent_from_roughness(hit.roughness());
    const float index_of_refraction = hit.mat->ior; // the k_spec
    // r = 2 * (n . l) * n - l
    // l = -w_i
    // n = hit.N
    float cos_i = glm::dot(w_i, hit.N);
    glm::vec3 r = 2.0f * cos_i * hit.N + w_i; 
    // n_shiny = exponent
    // float n_shiny = fresnel_schlick(cos_i, hit.roughness());// use fresnels term => Schlicks approximation from scr/gi/fresnel.h
    float reflect_vect_light = powf(glm::dot(w_o, r), exponent); 
    glm::vec3 temp = index_of_refraction * hit.albedo() * reflect_vect_light;
    float conserve_energy = (2.0f * M_PI)/(exponent + .0f); // lecture 4 page 10

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
    // TODO ASSIGNMENT2 (optional)
    // compute the GGX D term here
    // From micorofacet paper
    float alpha_g = 0.2f;
    // X^+ = 1 if 1 else 0 -> Q: m * n is 1 for us?
    float theta_m = NdotH;
    float D = (alpha_g * alpha_g) / (M_PI * powf(cosf(theta_m), 4.0f) * powf(powf(alpha_g, 2.0f) + powf(tan(theta_m), 2.0f), 2.0f));
    return D;

}

inline float GGX_G1(const float NdotV, float roughness) {
    // TODO ASSIGNMENT2 (optional)
    // compute the GGX G1 term here
    // From micorofacet paper
    float alpha_g = 0.2f;
    float theta_v = NdotV;
    // X^+ = 1 if 1 else 0 -> Q: v*m / v * n is 1 for us?
    float G1 = 2.0f / (1.0f + sqrtf(1.0f + powf(alpha_g, 2.0f) * powf(tan(theta_v), 2.0f)));
    return G1; 
}

glm::vec3 GGX_sample(const glm::vec2& sample, float roughness) {
    // TODO ASSIGNMENT2 (optional)
    // implement sampling the GGX distribution here
    // return a mircofacet normal in tangent space
    //TODO:hier
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

inline float GGX_pdf(float D, float NdotH, float HdotV) {
    // TODO ASSIGNMENT2 (optional)
    // compute the microfacet PDF here
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}

// ----------------------------------------------------------------------------------------------
// Microfacet reflection

glm::vec3 MicrofacetReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    // TODO ASSIGNMENT2
    // evaluate the full microfacet BRDF here, optionally relying on the above functions for the D and G1 terms
    // note: use schlick's approximation for the F term
    //const float alpha = hit.roughness();
    //const float microfacet = 0.f;
    //return coated ? glm::vec3(microfacet) : hit.albedo() * microfacet;
    
    // My version
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
    // TODO ASSIGNMENT2
    // importance sample and evaluate this microfacet BRDF
    // set w_i to the sampled (world-space!) direction, pdf to the respective PDF and brdf to the evaluated BRDF
    const glm::vec3 w_i = glm::vec3(0);
    const glm::vec3 brdf = glm::vec3(0);
    const float pdf = 0.f;
    return {brdf, w_i, pdf};
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
    const float F = fresnel_dielectric(dot(hit.N, w_o), 1.f, hit.mat->ior);
    return glm::mix(diff.f(hit, w_o, w_i), spec.f(hit, w_o, w_i), F);
}

std::tuple<glm::vec3, glm::vec3, float> LayeredSurface::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    const float F = fresnel_dielectric(dot(hit.N, w_o), 1.f, hit.mat->ior);
    glm::vec3 brdf;
    if (sample.x < F) {
        // sample specular
        const glm::vec2 sample_mapped = glm::vec2((F - sample.x) / F, sample.y);
        const auto [specular, w_i, sample_pdf] = spec.sample(hit, w_o, sample_mapped);
        if (!same_hemisphere(hit.Ng, w_i)) return {glm::vec3(0), w_i, 0.f};
        assert(std::isfinite(sample_pdf));
        return {mix(diff.f(hit, w_o, w_i), specular, F), w_i, glm::mix(diff.pdf(hit, w_o, w_i), sample_pdf, F)};
    } else {
        // sample diffuse
        const glm::vec2 sample_mapped = glm::vec2((sample.x - F) / (1 - F), sample.y);
        const auto [diffuse, w_i, sample_pdf] = diff.sample(hit, w_o, sample_mapped);
        if (!same_hemisphere(hit.Ng, w_i)) return {glm::vec3(0), w_i, 0.f};
        assert(std::isfinite(sample_pdf));
        return {mix(diffuse, spec.f(hit, w_o, w_i), F), w_i, glm::mix(sample_pdf, spec.pdf(hit, w_o, w_i), F)};
    }
}

float LayeredSurface::pdf(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    const float F = fresnel_dielectric(dot(hit.N, w_o), 1.f, hit.mat->ior);
    return glm::mix(diff.pdf(hit, w_o, w_i), spec.pdf(hit, w_o, w_i), F);
}

// ----------------------------------------------------------------------------------------------
// Metal

glm::vec3 MetallicSurface::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    throw std::runtime_error(
        "Function not implemented: " + std::string(__FILE__) + ", line: " + std::to_string(__LINE__)
    );
}
