#include "distribution.h"

#include "buffer.h"
#include "color.h"
#include "random.h"
#include "texture.h"

#include <iostream>
// Q: how to fun function examples 1 & 2? & how to see graph distribution?

// ----------------------------------------------------
// Distribution1D

Distribution1D::Distribution1D()
    : f_integral(0) {}

Distribution1D::Distribution1D(const float* f, uint32_t N)
    : func(f, f + N), cdf(N + 1) {
    // ASSIGNMENT3
    // build a CDF from given discrete function values and ensure a density
    // Hint: take extra care regarding corner-cases!

    // Normalize CDF
    float sum_pdf = 0;
    for (size_t i = 0; i < N; ++i) {
        sum_pdf += func[i]; // sum of all discrete Probabilities
        
    }
    // Q: is it correct to override, when the sum is 0?
    if(sum_pdf == 0){ // if all values are zero, make it a uniform distribution
        for(size_t i = 0; i< N; i++){
            func[i] = 1.f / N;
        }
        sum_pdf = 1.f;
    }
    float inv_sum_pdf = 1.f / sum_pdf;

    // build cdf
    cdf[0] = 0;
    for(size_t i = 0; i< N; i++){
        cdf[i+1] = cdf[i] + inv_sum_pdf * func[i];
        
    }  

    f_integral = sum_pdf;

}

int binary_search(float sample, const std::vector<float>& cdf) {
    int low = 0;
    int high = cdf.size() - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;
        if (cdf[mid] <= sample) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low - 1; // Return the index of the largest value less than or equal to sample
}

Distribution1D::~Distribution1D() {}

double Distribution1D::integral() const {
    return f_integral; // Integration in [0, N), area under function value is: 1 * func[i]
}

double Distribution1D::unit_integral() const {
    return f_integral / size(); // Integration in [0, 1), area under function value is: (1 / N) * func[i]
}

float Distribution1D::pdf(float sample) const {
    assert(sample >= 0 && sample < 1);
    return func[sample * size()] / unit_integral();
}

float Distribution1D::pdf(size_t index) const {
    assert(index < size());
    return func[index] / integral();
}

std::tuple<float, float> Distribution1D::sample_01(float sample) const {
    // TODO ASSIGNMENT3
    // draw a sample in [0, 1) according to this distribution and the respective PDF
    // hint: a piecewise constant function is assumed, so you may linearly interpolate between function values
    
    // Q: how to test this function?
    float x_value = binary_search(sample, cdf);
    // linear interpolation
    float interp_x = cdf[x_value] + (sample - cdf[x_value]) / (cdf[x_value + 1] - cdf[x_value]) * (1.f / size());
    float p = func[interp_x]/ unit_integral(); // pdf at the interpolated index

    return {func[interp_x], p};
}

std::tuple<uint32_t, float> Distribution1D::sample_index(float sample) const {
    // ASSIGNMENT3
    // sample an index in [0, n) according to this distribution and the respective PDF
    // note: take care about proper normalization of the PDF!

    float x_value = binary_search(sample, cdf); 
    float p = func[x_value] / integral(); // pdf at the discrete index
    
    return {x_value, p };
}

// ----------------------------------------------------
// Distribution2D

std::vector<Distribution1D> conditional; // one per row => h
Distribution1D marginal; // marginal distribution along y

Distribution2D::Distribution2D(const float* f, uint32_t w, uint32_t h) {
    // TODO ASSIGNMENT3
    // build conditional and marginal distributions from linearized array of function values
    // hint: use f[y * w + x] to get the value at (x, y)
    // hint: you may re-use the Distribution1D

    float sum_y[h];
    conditional.resize(h);

    for(size_t y = 0; y < h; y++){
        conditional[y] = Distribution1D(f + y*w, w);
        sum_y[y] = 0;
        for (size_t x = 0; x < w; x++){
            sum_y[y] += f[y*w + x];
        }
    }
    marginal = Distribution1D(sum_y, h); 

    plot_heatmap(*this, w, h);

    /*float inv_sum_pdf = 0;
    if(marginal.integral()  == 0){ // if all values are zero, make it a uniform distribution
        // TODO: Edge case?
        inv_sum_pdf = 1.f;
    }else{
        inv_sum_pdf = 1.f / marginal.integral() ;
    }*/

}

Distribution2D::~Distribution2D() {}

double Distribution2D::integral() const {
    // TODO ASSIGNMENT3
    // return the integral here
    return marginal.integral();
}

double Distribution2D::unit_integral() const {
    // TODO ASSIGNMENT3
    // return the unit integral here
    return marginal.integral() / marginal.size();
}

std::tuple<glm::vec2, float> Distribution2D::sample_01(const glm::vec2& sample) const {
    // TODO ASSIGNMENT3
    // draw a two-dimensional sample in [0, 1) from this distribution and compute its PDF
    // hint: first sample a row according to the marginal distribution, then sample a column according to the respective conditional distribution
    auto [y_index, p_y] = marginal.sample_index(sample.y);
    auto [x_index, p_x] = conditional[y_index].sample_index(sample.x);
    
    float p = (p_y * p_x) / integral(); // joint pdf = p(y) * p(x|y) / integral of the whole distribution

    glm::vec2 sample_vec(x_index / float(conditional[y_index].size()), y_index / float(marginal.size()));
    
    return {sample_vec, p};

    //return {sample, 1.f};
    /*
    float x_value = binary_search(sample, cdf);
    // linear interpolation
    float interp_x = cdf[x_value] + (sample - cdf[x_value]) / (cdf[x_value + 1] - cdf[x_value]) * (1.f / size());
    float p = func[interp_x]/ size();

    return {func[interp_x], p};*/
}

float Distribution2D::pdf(const glm::vec2& sample) const {
    // Q: also do something here?
    return 1.f;
}

// ----------------------------------------------------
// Debug utilities

void plot_histogram(const Distribution1D& dist, const std::string& name) {
    uint32_t N = 250000, w = std::min(1000u, dist.size()), h = w / 2;
    Buffer<float> results(w);
    Buffer<float> pdfs(w);
    results = 0;
    UniformSampler1D sampler;
    sampler.init(N);
    for (uint32_t i = 0; i < N; ++i) {
        const auto [sample, pdf] = dist.sample_01(sampler.next());
        results[uint32_t(sample * w) % w] += 1;
        pdfs[uint32_t(sample * w) % w] += pdf;
    }
    // scale values
    float max_val = FLT_MIN;
    for (uint32_t x = 0; x < w; ++x) {
        pdfs(x) /= fmaxf(1.f, results(x));
        max_val = fmaxf(results(x), max_val);
    }
    for (uint32_t x = 0; x < w; ++x) {
        results(x) = results(x) / max_val;
        pdfs(x) = pdfs(x) / 10.f;
    }
    // build histogram
    Buffer<glm::vec3> buffer(w, h);
    Buffer<glm::vec3> buffer_pdf(w, h);
    buffer = glm::vec3(0);
    buffer_pdf = glm::vec3(0);
    for (uint32_t x = 0; x < w; ++x) {
        for (uint32_t y = 0; y < h; ++y) {
            if (y < results(x) * h) buffer(x, y) = heatmap(results(x));
            if (y < pdfs(x) * h) buffer_pdf(x, y) = heatmap(pdfs(x));
        }
    }
    // output
    static uint32_t i = 0;
    Texture::save_png(std::string("dist1D_") + name + "_hits.png", w, h, buffer.data());
    Texture::save_png(std::string("dist1D_") + name + "_pdf.png", w, h, buffer_pdf.data());
}

void plot_heatmap(const Distribution2D& dist, uint32_t w, uint32_t h) {
    uint32_t N = 100000;
    Buffer<glm::vec3> buffer_n(w, h), buffer_pdf(w, h);
    buffer_n = glm::vec3(0);
    buffer_pdf = glm::vec3(0);
    UniformSampler2D sampler;
    sampler.init(N);
    for (uint32_t i = 0; i < N; ++i) {
        const auto [sample, pdf] = dist.sample_01(sampler.next());
        uint32_t x = sample.x * w;
        uint32_t y = sample.y * h;
        if (x >= 0 && y >= 0 && x < w && y < h) {
            buffer_n(x, y) += glm::vec3(1);
            buffer_pdf(x, y) += glm::vec3(pdf);
        }
    }
    // scale values
    glm::vec3 max_val = glm::vec3(FLT_MIN);
    for (uint32_t y = 0; y < h; ++y)
        for (uint32_t x = 0; x < w; ++x)
            max_val = max(buffer_n(x, y), max_val);
    for (uint32_t y = 0; y < h; ++y) {
        for (uint32_t x = 0; x < w; ++x) {
            buffer_pdf(x, y) = heatmap(buffer_pdf(x, y).x / (buffer_n(x, y).x * 100)); // scale for visibility
            buffer_n(x, y) = heatmap((buffer_n(x, y) / (0.5f * max_val)).x);           // scale for visibility
        }
    }
    // output
    static uint32_t i = 0;
    Texture::save_png(std::string("dist2D_") + std::to_string(i) + "_hits.png", w, h, buffer_n.data(), false);
    Texture::save_png(std::string("dist2D_") + std::to_string(i++) + "_pdf.png", w, h, buffer_pdf.data(), false);
}

void debug_distributions() {
    {
        // debug 1D
        const int N = 1000;
        std::vector<float> values(N);
        // const func
        for (int i = 0; i < N; ++i)
            values[i] = 1;
        Distribution1D dist(values.data(), N);
        plot_histogram(dist, "const");
        // step func
        for (int i = 0; i < N; ++i)
            values[i] = (i + 1) / float(N);
        dist = Distribution1D(values.data(), N);
        plot_histogram(dist, "gradient");
        // power func
        for (int i = 0; i < N; ++i)
            values[i] = pow((i + 1) / float(N), 4);
        dist = Distribution1D(values.data(), N);
        plot_histogram(dist, "pow");
        // triangle func
        for (int i = 0; i < N; ++i)
            values[i] = N / 2 - std::abs(i - N / 2);
        dist = Distribution1D(values.data(), N);
        plot_histogram(dist, "abs");
    }
    {
        // debug 2D
        const int W = 1280, H = 720;
        std::vector<float> values(W * H);
        // SDF field
        for (int y = 0; y < H; ++y)
            for (int x = 0; x < W; ++x)
                values[y * W + x] =
                    pow(length(glm::vec2(W / 4, H / 4)) - length(glm::vec2(x, y) - glm::vec2(W / 2, H / 2)), 4);
        Distribution2D dist(values.data(), W, H);
        plot_heatmap(dist, W, H);
    }
}
