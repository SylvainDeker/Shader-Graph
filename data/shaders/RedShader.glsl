#version 330 core

#include "DirectionalLight.glsl"

in vec3 normal;
out vec4 color;

void main()
{
    float diff = max(dot(normal, directionalLightDirection(dirlight)), 0.0f);
    vec3 diffuse = diff * lightContributionFrom(dirlight);
    vec3 res = vec3(1.0f, 0.5f, 0.2f) * diffuse;
    color = vec4(res, 1.0f);
}
