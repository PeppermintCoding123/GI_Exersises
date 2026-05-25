#include "brdf.h"

#include "fresnel.h"
#include "hit.h"
#include "material.h"
#include "sampling.h"
#include "gi/random.h"

// ----------------------------------------------------------------------------------------------
// Diffuse lambertian reflection

glm::vec3 LambertianReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    // TODO ASSIGNMENT2
    // evaluate the (normalized!) lambertian diffuse BRDF

    return hit.albedo() / PI;
}

std::tuple<glm::vec3, glm::vec3, float> LambertianReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    // TODO ASSIGNMENT2
    // importance sample and evaluate the lambertian diffuse BRDF
    // set w_i to the sampled (world-space!) direction, pdf to the respective PDF and brdf to the evaluated BRDF
    // importance sampling here is cosine sampling of hemisphere => see lecture 6
    const auto w_i_tangent_space = cosine_sample_hemisphere(sample);
    const glm::vec3 w_i = hit.to_world(w_i_tangent_space);
    const glm::vec3 brdf = f(hit, w_o, w_i);
    const float pdf = cosine_hemisphere_pdf(w_i_tangent_space.z);;
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
    // TODO ASSIGNMENT2
    // evaluate the (normalized!) phong BRDF for the given in- and outgoing (world-space) directions
    // you may use hit.albedo() as the specular color here
    const float exponent = Material::exponent_from_roughness(hit.roughness());
    const float index_of_refraction = hit.mat->ior;

    const auto h = glm::normalize(w_o + w_i);
    const auto k_shiny = fresnel_schlick(glm::max(glm::dot(w_o, h), 0.0f), index_of_refraction); // reflection coefficiant
    const float reflect_vect_light = std::pow(glm::max(glm::dot(hit.N, h), 0.0f), exponent);
    const float conserve_energy = (exponent + 1.0f) / (2.0f * PI); // lecture 4 page 10

    return hit.albedo() * k_shiny * reflect_vect_light * conserve_energy; // calculate entire, not just 


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
    if (NdotH <= 0){ return 0;} // X^+
    float alpha_g = roughness;
    float theta_m = NdotH;

    float D = (sqr(alpha_g)) / (M_PI * glm::pow(cos(theta_m), 4.0f) * sqr(sqr(alpha_g) + sqr(tan(theta_m)))); // sqr macht square also hoch 2
    return D;
}

inline float GGX_G1(const float NdotV, float roughness) {
    // TODO ASSIGNMENT2 (optional)
    // compute the GGX G1 term here
    // From micorofacet paper
    if (NdotV <= 0){ return 0;} // X^+
    float alpha_g = roughness;
    float theta_v = NdotV; // angle between v & n according to paper
    
    float G1 = 2.0f / (1.0f + sqrtf(1.0f + powf(alpha_g, 2.0f) * powf(tan(theta_v), 2.0f)));
    return G1; 

}

glm::vec3 GGX_sample(const glm::vec2& sample, float roughness) {
    // TODO ASSIGNMENT2 (optional)
    // implement sampling the GGX distribution here
    // return a mircofacet normal in tangent space
    return to_cartesian(glm::vec2(
        std::atan((roughness * std::sqrt(sample.x)) / (std::sqrt(1 - sample.x)))
        , 2 * PI * sample.y
    ));

}

inline float GGX_pdf(float D, float NdotH, float HdotV) {
    // TODO ASSIGNMENT2 (optional)
    // compute the microfacet PDF here
    const auto pdf = /* std::abs */(D * NdotH) / /* std::abs */(4 * HdotV);
    if(!std::isfinite(pdf) || pdf == 0.f){return 1.f;}
    return pdf;

}


// ----------------------------------------------------------------------------------------------
// Microfacet reflection

glm::vec3 MicrofacetReflection::f(const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec3& w_i) const {
    // TODO ASSIGNMENT2
    // evaluate the full microfacet BRDF here, optionally relying on the above functions for the D and G1 terms
    // note: use schlick's approximation for the F term
    
    // My version
    glm::vec3 h = glm::normalize(w_i + w_o); // halfway vector
    float alpha = hit.roughness(); // microsurface routhness

    float NdotH = glm::dot(hit.N, h);
    float IdotH = glm::dot(hit.N, w_o); // hier max 0
    float OdotH = glm::dot(h, w_o);


    float Giom = GGX_G1(IdotH, alpha) * GGX_G1(OdotH, alpha);// = Gim*Gom  QA: stimmt das => Ja
    float numerator = Giom * GGX_D(NdotH, alpha) * fresnel_schlick(IdotH, alpha);
    
    float denominator = 4.0f * (glm::dot(hit.N, w_o) * glm::dot(hit.N, w_o)); // angles of incident & exiting towards light
    // if demom small return 0 vector
    
    float f = numerator / denominator;
    return f * hit.albedo();
    // QA: what is meant by index odf reflection -> See above
    // QA: expected to multiply f with a vector? => welcher Vector => use hit.albedo()
}

std::tuple<glm::vec3, glm::vec3, float> MicrofacetReflection::sample(
    const SurfaceHit& hit, const glm::vec3& w_o, const glm::vec2& sample
) const {
    // TODO ASSIGNMENT2
    // importance sample and evaluate this microfacet BRDF
    // set w_i to the sampled (world-space!) direction, pdf to the respective PDF and brdf to the evaluated BRDF
    const glm::vec3 w_i_tangent_space = uniform_sample_hemisphere(sample);
    const glm::vec3 w_i = tangent_to_world(hit.N, w_i_tangent_space);
    const glm::vec3 brdf = f(hit, w_o, w_i);
    
    // from Paper: GGX BRDF
    // Draw a tangent space micro normal from a random sample using Eq 35 & 36
    float alpha = hit.roughness();
    float theta_m = atan(alpha * sqrtf(sample.x) / sqrtf(1 - sample.x)); // 35
    float phi_m = 2 * PI * sample.y; // 36

    // compute pdf with Eq 14, 24,38
    glm::vec3 h = glm::normalize(w_i + w_o);
    float NdotH = glm::dot(hit.N, h);
    float D = GGX_D(NdotH, alpha);

    float jacobian = 1.0f / (4.0f * glm::dot(w_o, h)); // Eq 14 jacobian = dw_h/dw_0
    float p_m = D * cos(theta_m); // Eq 24 p_m = probability of generating any m using given sampling equasion
    float p_o = p_m / jacobian; // Eq 38 p_o = probability of generating w_i via sampling m and reflecting w_o about m

    const float pdf = D * p_o; // GGX_pdf(D, NdotH, OdotH);
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
