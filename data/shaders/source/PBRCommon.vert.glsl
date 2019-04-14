//This is the basic vertexShader any PBR material can use
#include "Transform/TransformStructs.glsl"

//This is for a preview of the shader composition, but in time we must use more specific Light Shader
#include "DefaultLight.glsl"

// Inputs of vertex shaders are set by the application wrt the following locations
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_texcoord;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

// Set of matrices that should be used by the shader
uniform Transform transform;

// Ouputs of the vertex shader are defined by the following interface and location
// Note that all outputs are in world space (will change in the future for performance improvement)
out vec3 v_position;
out vec3 v_texcoord;
out vec3 v_normal;
out vec3 v_tangent;
out vec3 v_viewVector;
out vec3 v_lightVector;

void main()
{
	// compute position in clip space
    gl_Position = transform.mvp * vec4(in_position, 1.0);

	// compute position, normal, tangent and eye in world space
    vec4 pos = transform.model * vec4(in_position, 1.0);
    pos /= pos.w;

    vec3 normal = normalize(mat3(transform.worldNormal) * in_normal);
    vec3 tangent = normalize(mat3(transform.model) * in_tangent);

    vec3 eye = -transform.view[3].xyz * mat3(transform.view);

	// ouput vertex components
    v_position    = vec3(pos);
    v_texcoord    = in_texcoord;

    v_normal      = normal;
    v_tangent     = tangent;

    v_viewVector  = normalize(vec3(eye - vec3(pos)));
    v_lightVector = getLightDirection(light, vec3(pos));
}
