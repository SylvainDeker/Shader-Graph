#ifndef DIRECTIONALLIGHTSHADER_GLSL
#define DIRECTIONALLIGHTSHADER_GLSL

struct DirectionalLight
{
    vec3 direction;
    vec4 color;
};

vec3 directionalLightDirection(DirectionalLight light) {
    return normalize(-light.direction);
}

vec3 lightContributionFrom(DirectionalLight light) {
    return light.color.xyz;
}

uniform DirectionalLight dirlight;

#endif //DIRECTIONALLIGHTSHADER_GLSL
