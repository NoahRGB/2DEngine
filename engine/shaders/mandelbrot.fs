#version 400 core

in vec2 vLocal;

out vec4 FragColor;

uniform double uZoom;
uniform dvec2 uPos;
uniform float uTime;

vec3 palette(float t) {
    // see https://iquilezles.org/articles/palettes/
    // vec3 a = vec3(0.5, 0.5, 0.5);
    // vec3 b = vec3(0.5, 0.5, 0.5);
    // vec3 c = vec3(2.0, 1.0, 0.0);
    // vec3 d = vec3(0.5, 0.20, 0.25);
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 0.5);
    vec3 d = vec3(0.80, 0.90, 0.30);
    return a + b * cos(6.28318 * (c * t + d));
}

void main() {

    dvec2 c = uPos + vLocal * 3.0 / uZoom;
    dvec2 z = vec2(0.0);

    // set maxIterations based on how zoomed in it is
    int maxIterations = int(200 + 100 * log2(float(uZoom)));
    int iteration = 0;

    for (; iteration < maxIterations; iteration++) {
        if (dot(z, z) > 256.0) {
            break;
        }
        z = dvec2(z.x*z.x-z.y*z.y, 2.0*z.x*z.y) + c;
    }

    // make inner parts fully black
    if (iteration == maxIterations) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    // smooth stepping (https://iquilezles.org/articles/msetsmooth/)
    float sn = float(iteration) - log2(log2(float(dot(z, z)))) + 4.0;
    FragColor = vec4(palette(sn * 0.02 + uTime * 0.5), 1.0);
}