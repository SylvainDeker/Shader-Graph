#shader vertex

/* ================================================================= */
/*                             VERTEX                                */
/* ================================================================= */

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 in_normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 normal;

void main()
{
    gl_Position = position;
    normal = in_normal;
}

#shader fragment

/* ================================================================= */
/*                             FRAGMENT                              */
/* ================================================================= */

#version 330 core

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


in vec3 normal;
out vec4 color;

void main()
{
    float diff = max(dot(normal, directionalLightDirection(dirlight)), 0.0f);
    vec3 diffuse = diff * lightContributionFrom(dirlight);
    vec3 res = vec3(1.0f, 0.5f, 0.2f) * diffuse;
    color = vec4(res, 1.0f);
}
