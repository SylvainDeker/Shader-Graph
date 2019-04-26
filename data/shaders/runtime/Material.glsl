#ifndef PLASTICMATERIAL_GLSL
#define PLASTICMATERIAL_GLSL
/*
 * Implements material interface for Plastic material
 * see at https://www.pbrt.org/fileformat-v3.html#materials for parameters and
 * properties
 */
// Microfacet functions used
#include "MicrofacetFunction.glsl"

/* Material data structure
 * Defines the input of the material
 * All material parameters will be set by the application
 */
// Material parameters could be textured,
struct MaterialTextures {
    int 	hasKd;
    int 	hasKs;
    int		hasRoughness;
    int 	hasNormal;

    sampler2D kd;
    sampler2D ks;
    sampler2D roughness;
    sampler2D normal;
};

// Main material description
struct Material {
    vec4 	kd;
    vec4 	ks;
    float 	roughness;
    int 	remapRoughness;

    MaterialTextures tex;
};

// Uniform : 
uniform sampler2D u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesBrickpng; 
// Uniform : 
uniform sampler2D u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesShaderGraphpng; 


vec3 getKd(Material material, vec2 texCoord) { 



vec2 id8_UVs = vec2(0.0f);  // Input
vec4 id8_RGBA = vec4(0.0f); // Output
float id8_R = 0.0f; // Output
float id8_G = 0.0f; // Output
float id8_B = 0.0f; // Output
float id8_A = 0.0f; // Output
id8_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesBrickpng, texCoord); 
id8_R = id8_RGBA.r; 
id8_G = id8_RGBA.g; 
id8_B = id8_RGBA.b; 
id8_A = id8_RGBA.a; 
float id20_A = id8_R;  // Input

vec2 id9_UVs = vec2(0.0f);  // Input
vec4 id9_RGBA = vec4(0.0f); // Output
float id9_R = 0.0f; // Output
float id9_G = 0.0f; // Output
float id9_B = 0.0f; // Output
float id9_A = 0.0f; // Output
id9_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesShaderGraphpng, texCoord); 
id9_R = id9_RGBA.r; 
id9_G = id9_RGBA.g; 
id9_B = id9_RGBA.b; 
id9_A = id9_RGBA.a; 
float id20_B = id9_R;  // Input
float id20_ReturnValue = 0.0f; // Output
id20_ReturnValue = id20_A + id20_B;float id23_X = id20_ReturnValue;  // Input


float id21_A = id8_G;  // Input

float id21_B = id9_G;  // Input
float id21_ReturnValue = 0.0f; // Output
id21_ReturnValue = id21_A + id21_B;float id23_Y = id21_ReturnValue;  // Input


float id22_A = id8_B;  // Input

float id22_B = id9_B;  // Input
float id22_ReturnValue = 0.0f; // Output
id22_ReturnValue = id22_A + id22_B;float id23_Z = id22_ReturnValue;  // Input
vec3 id23_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id23_Vector3 = vec3(id23_X, id23_Y, id23_Z); 

vec3 Diffuse = id23_Vector3;  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float Opacity = 0.0f;  // Input
vec3 WorldPositionOffset = vec3(0.0f);  // Input
vec3 AmbientOcclusion = vec3(0.0f);  // Input
vec3 Refraction = vec3(0.0f);  // Input
vec2 TextureCoordinate = vec2(0.0f);  // Input
vec3 Tangent = vec3(0.0f);  // Input
float Depth = 0.0f;  // Input
// End MasterMaterialOutput
return Diffuse; 
} 

vec3 getKs(Material material, vec2 texCoord) { 



vec2 id8_UVs = vec2(0.0f);  // Input
vec4 id8_RGBA = vec4(0.0f); // Output
float id8_R = 0.0f; // Output
float id8_G = 0.0f; // Output
float id8_B = 0.0f; // Output
float id8_A = 0.0f; // Output
id8_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesBrickpng, texCoord); 
id8_R = id8_RGBA.r; 
id8_G = id8_RGBA.g; 
id8_B = id8_RGBA.b; 
id8_A = id8_RGBA.a; 
float id20_A = id8_R;  // Input

vec2 id9_UVs = vec2(0.0f);  // Input
vec4 id9_RGBA = vec4(0.0f); // Output
float id9_R = 0.0f; // Output
float id9_G = 0.0f; // Output
float id9_B = 0.0f; // Output
float id9_A = 0.0f; // Output
id9_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesShaderGraphpng, texCoord); 
id9_R = id9_RGBA.r; 
id9_G = id9_RGBA.g; 
id9_B = id9_RGBA.b; 
id9_A = id9_RGBA.a; 
float id20_B = id9_R;  // Input
float id20_ReturnValue = 0.0f; // Output
id20_ReturnValue = id20_A + id20_B;float id23_X = id20_ReturnValue;  // Input


float id21_A = id8_G;  // Input

float id21_B = id9_G;  // Input
float id21_ReturnValue = 0.0f; // Output
id21_ReturnValue = id21_A + id21_B;float id23_Y = id21_ReturnValue;  // Input


float id22_A = id8_B;  // Input

float id22_B = id9_B;  // Input
float id22_ReturnValue = 0.0f; // Output
id22_ReturnValue = id22_A + id22_B;float id23_Z = id22_ReturnValue;  // Input
vec3 id23_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id23_Vector3 = vec3(id23_X, id23_Y, id23_Z); 

vec3 Diffuse = id23_Vector3;  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float Opacity = 0.0f;  // Input
vec3 WorldPositionOffset = vec3(0.0f);  // Input
vec3 AmbientOcclusion = vec3(0.0f);  // Input
vec3 Refraction = vec3(0.0f);  // Input
vec2 TextureCoordinate = vec2(0.0f);  // Input
vec3 Tangent = vec3(0.0f);  // Input
float Depth = 0.0f;  // Input
// End MasterMaterialOutput
return Specular; 
} 

vec2 getRoughness(Material material, vec2 texCoord) { 



vec2 id8_UVs = vec2(0.0f);  // Input
vec4 id8_RGBA = vec4(0.0f); // Output
float id8_R = 0.0f; // Output
float id8_G = 0.0f; // Output
float id8_B = 0.0f; // Output
float id8_A = 0.0f; // Output
id8_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesBrickpng, texCoord); 
id8_R = id8_RGBA.r; 
id8_G = id8_RGBA.g; 
id8_B = id8_RGBA.b; 
id8_A = id8_RGBA.a; 
float id20_A = id8_R;  // Input

vec2 id9_UVs = vec2(0.0f);  // Input
vec4 id9_RGBA = vec4(0.0f); // Output
float id9_R = 0.0f; // Output
float id9_G = 0.0f; // Output
float id9_B = 0.0f; // Output
float id9_A = 0.0f; // Output
id9_RGBA = texture(u_UsersvalentinDesktopWorkspaceShaderGraphdatatexturesShaderGraphpng, texCoord); 
id9_R = id9_RGBA.r; 
id9_G = id9_RGBA.g; 
id9_B = id9_RGBA.b; 
id9_A = id9_RGBA.a; 
float id20_B = id9_R;  // Input
float id20_ReturnValue = 0.0f; // Output
id20_ReturnValue = id20_A + id20_B;float id23_X = id20_ReturnValue;  // Input


float id21_A = id8_G;  // Input

float id21_B = id9_G;  // Input
float id21_ReturnValue = 0.0f; // Output
id21_ReturnValue = id21_A + id21_B;float id23_Y = id21_ReturnValue;  // Input


float id22_A = id8_B;  // Input

float id22_B = id9_B;  // Input
float id22_ReturnValue = 0.0f; // Output
id22_ReturnValue = id22_A + id22_B;float id23_Z = id22_ReturnValue;  // Input
vec3 id23_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id23_Vector3 = vec3(id23_X, id23_Y, id23_Z); 

vec3 Diffuse = id23_Vector3;  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float Opacity = 0.0f;  // Input
vec3 WorldPositionOffset = vec3(0.0f);  // Input
vec3 AmbientOcclusion = vec3(0.0f);  // Input
vec3 Refraction = vec3(0.0f);  // Input
vec2 TextureCoordinate = vec2(0.0f);  // Input
vec3 Tangent = vec3(0.0f);  // Input
float Depth = 0.0f;  // Input
// End MasterMaterialOutput
return vec2(Roughness); 
} 

vec3 getNormal(Material material, vec2 texCoord, vec3 N, vec3 T, vec3 B) {
    if (material.tex.hasNormal == 1) {
        mat3 tbn;

        tbn[0]  = T;
        tbn[1]  = B;
        tbn[2]  = N;

        vec3 normalLocal = normalize(vec3(texture(material.tex.normal, texCoord)) * 2 - 1);
        return normalize(tbn * normalLocal);
    }

    return normalize(N);
}

/*
 * Compute the response of the material according to the incomming (light) diretion wi and the
 *  outgoing (view) direction wo at the position on surface texC.
 * Note that the directions are expressed in the local frame.
 */
vec3 computeMaterialInternal(Material material, vec2 texC, vec3 wi, vec3 wo) {
     float cosTi = CosTheta(wi);
     float cosTo = CosTheta(wo);

     if (cosTi == 0 || cosTo == 0)
         return vec3(0.f);


     bool reflect = (cosTi * cosTo > 0);
     vec3 result = vec3(0.f);

     if (reflect) {
        cosTi = abs(cosTi);
        cosTo = abs(cosTo);

        vec3 kd = getKd(material, texC);
        result = (kd * InvPi);

        vec3 wh = wi + wo;
        if (!(wh.x == 0 && wh.y == 0 && wh.z == 0)) {
            wh = normalize(wh);
            vec3 ks = getKs(material, texC);
            float F = FresnelDielectric(dot(wi, wh), 1, 1.5);
            vec2 rough = getRoughness(material, texC);
            float D = TRD_D(wh, rough.x, rough.y);
            float G = TRD_G(wo, wi, rough.x, rough.y);
            result += (ks * F * D * G /(4 * cosTi * cosTo));
        }
     }
     return result * cosTi;
}

// Define the uniform that could be accessed from th application
uniform Material material;

#endif//PLASTICMATERIAL_GLSL
