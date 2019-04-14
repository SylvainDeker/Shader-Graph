// This is the canonic fragmentShader any PBR material will use.
// A specific material fragment shader implements the material interface (computeMaterialInternal)
// and include this shader

// For the moment, include all the ligh-type interfaces. Will change in the future for performances improvement
#include "DefaultLight.glsl"

// Fragment shader just ouput the fragment color
out vec4 fragColor;

in vec3 v_position;
in vec3 v_texcoord;
in vec3 v_normal;
in vec3 v_tangent;
in vec3 v_viewVector;
in vec3 v_lightVector;

void main()
{
    // all vectors are in world space
	vec3 binormal = normalize(cross(v_normal, v_tangent));
	vec3 normalWorld 	= getNormal(material, v_texcoord.xy, v_normal, v_tangent, binormal);
	vec3 binormalWorld 	= normalize(cross(normalWorld, v_tangent));
	vec3 tangentWorld 	= normalize(cross(binormalWorld, normalWorld));

    // A material is always evaluated in the fragment local Frame
    // compute matrix from World to local Frame
    mat3 world2local;
    world2local[0]  = vec3(tangentWorld.x, binormalWorld.x, normalWorld.x);
    world2local[1]  = vec3(tangentWorld.y, binormalWorld.y, normalWorld.y);
    world2local[2]  = vec3(tangentWorld.z, binormalWorld.z, normalWorld.z);
	
    // transform all vectors in local frame so that N = (0, 0, 1);
    vec3 wi = world2local * normalize(v_lightVector); // incident direction
    vec3 wo = world2local * normalize(v_viewVector);  // outgoing direction

	// Compute the material response (evaluate the bsdf)
    vec3 materialColor 	= computeMaterialInternal(material, v_texcoord.xy, wi, wo);

	// Compute the light contribution
	vec3 contribution 	= lightContributionFrom(light, v_position);
    
	// Set the final color
    fragColor = vec4(materialColor * contribution, 1.0);
}
