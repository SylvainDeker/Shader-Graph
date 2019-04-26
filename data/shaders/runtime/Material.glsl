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

vec3 getKd(Material material, vec2 texCoord) { 
vec3 Diffuse = vec3(0.0f);  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float id9_Result = 0.0f; // Output
// Input : Scalar 
id9_Result = 2.300000;

float id8_Value = id9_Result;  // Input

float id8_Step = id9_Result;  // Input
float id8_Result = 0.0f; // Output
// Step 
id8_Result = floor(id8_Value / id8_Step) * id8_Step;


float Opacity = id8_Result;  // Input
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
vec3 Diffuse = vec3(0.0f);  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float id9_Result = 0.0f; // Output
// Input : Scalar 
id9_Result = 2.300000;

float id8_Value = id9_Result;  // Input

float id8_Step = id9_Result;  // Input
float id8_Result = 0.0f; // Output
// Step 
id8_Result = floor(id8_Value / id8_Step) * id8_Step;


float Opacity = id8_Result;  // Input
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
vec3 Diffuse = vec3(0.0f);  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float id9_Result = 0.0f; // Output
// Input : Scalar 
id9_Result = 2.300000;

float id8_Value = id9_Result;  // Input

float id8_Step = id9_Result;  // Input
float id8_Result = 0.0f; // Output
// Step 
id8_Result = floor(id8_Value / id8_Step) * id8_Step;


float Opacity = id8_Result;  // Input
vec3 WorldPositionOffset = vec3(0.0f);  // Input
vec3 AmbientOcclusion = vec3(0.0f);  // Input
vec3 Refraction = vec3(0.0f);  // Input
vec2 TextureCoordinate = vec2(0.0f);  // Input
vec3 Tangent = vec3(0.0f);  // Input
float Depth = 0.0f;  // Input
// End MasterMaterialOutput
return vec2(Roughness); 
} 

float getMetalness() { 
vec3 Diffuse = vec3(0.0f);  // Input
vec3 Normal = vec3(0.0f);  // Input
vec3 Specular = vec3(0.0f);  // Input
float Metallic = 0.0f;  // Input
float Roughness = 0.0f;  // Input
float Emissive = 0.0f;  // Input
float id9_Result = 0.0f; // Output
// Input : Scalar 
id9_Result = 2.300000;

float id8_Value = id9_Result;  // Input

float id8_Step = id9_Result;  // Input
float id8_Result = 0.0f; // Output
// Step 
id8_Result = floor(id8_Value / id8_Step) * id8_Step;


float Opacity = id8_Result;  // Input
vec3 WorldPositionOffset = vec3(0.0f);  // Input
vec3 AmbientOcclusion = vec3(0.0f);  // Input
vec3 Refraction = vec3(0.0f);  // Input
vec2 TextureCoordinate = vec2(0.0f);  // Input
vec3 Tangent = vec3(0.0f);  // Input
float Depth = 0.0f;  // Input
// End MasterMaterialOutput
return Metallic; 
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

     vec3 kd = getKd(material, texC);

     if (reflect) {
        cosTi = abs(cosTi);
        cosTo = abs(cosTo);

        result = (kd * InvPi);

        vec3 wh = wi + wo;
        if (!(wh.x == 0 && wh.y == 0 && wh.z == 0)) {
            wh = normalize(wh);
            vec3 ks = getKs(material, texC);
            vec3 F0 = vec3(0.04);
            F0 = mix(F0, ks, vec3(getMetalness()));
            vec3 F90 = kd;
            vec3 F = FresnelShlick(dot(wi, wh), F0, F90);
            vec2 rough = getRoughness(material, texC);
            float D = TRD_D(wh, rough.x, rough.y);
            float G = TRD_G(wo, wi, rough.x, rough.y);
            result += (F * D * G /(4 * cosTi * cosTo));
        }
     }
     /* result + ambient */
     return result * cosTi + 0.1 * kd;
}

// Define the uniform that could be accessed from th application
uniform Material material;

#endif//PLASTICMATERIAL_GLSL
