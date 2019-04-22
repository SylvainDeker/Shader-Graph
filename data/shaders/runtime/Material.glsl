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
vec2 id11_UVs = vec2(0.0f); // Output
float id11_u = 0.0f; // Output
float id11_v = 0.0f; // Output
// Input : UV 
id11_UVs = texCoord; 
id11_u = texCoord.x; 
id11_v = texCoord.y; 


float id12_Value = id11_u;  // Input
float id14_Result = 0.0f; // Output
// Input : Scalar 
id14_Result = 0.02;

float id12_Step = id14_Result;  // Input
float id12_Result = 0.0f; // Output
// Step 
id12_Result = floor(id12_Value / id12_Step) * id12_Step;


float id21_X = id12_Result;  // Input

float id13_Value = id11_v;  // Input

float id13_Step = id14_Result;  // Input
float id13_Result = 0.0f; // Output
// Step 
id13_Result = floor(id13_Value / id13_Step) * id13_Step;


float id21_Y = id13_Result;  // Input
float id21_Z = 0.0f;  // Input
vec3 id21_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id21_Vector3 = vec3(id21_X, id21_Y, id21_Z); 


vec3 id22_A = id21_Vector3;  // Input
vec3 id15_Result = vec3(0.0f); // Output
// Input : Vec3 
id15_Result = vec3(4, 4, 4);

vec3 id22_B = id15_Result;  // Input
vec3 id22_Result = vec3(0.0f); // Output
id22_Result = id22_A * id22_B;
vec3 Diffuse = id22_Result;  // Input
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
vec2 id11_UVs = vec2(0.0f); // Output
float id11_u = 0.0f; // Output
float id11_v = 0.0f; // Output
// Input : UV 
id11_UVs = texCoord; 
id11_u = texCoord.x; 
id11_v = texCoord.y; 


float id12_Value = id11_u;  // Input
float id14_Result = 0.0f; // Output
// Input : Scalar 
id14_Result = 0.02;

float id12_Step = id14_Result;  // Input
float id12_Result = 0.0f; // Output
// Step 
id12_Result = floor(id12_Value / id12_Step) * id12_Step;


float id21_X = id12_Result;  // Input

float id13_Value = id11_v;  // Input

float id13_Step = id14_Result;  // Input
float id13_Result = 0.0f; // Output
// Step 
id13_Result = floor(id13_Value / id13_Step) * id13_Step;


float id21_Y = id13_Result;  // Input
float id21_Z = 0.0f;  // Input
vec3 id21_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id21_Vector3 = vec3(id21_X, id21_Y, id21_Z); 


vec3 id22_A = id21_Vector3;  // Input
vec3 id15_Result = vec3(0.0f); // Output
// Input : Vec3 
id15_Result = vec3(4, 4, 4);

vec3 id22_B = id15_Result;  // Input
vec3 id22_Result = vec3(0.0f); // Output
id22_Result = id22_A * id22_B;
vec3 Diffuse = id22_Result;  // Input
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
vec2 id11_UVs = vec2(0.0f); // Output
float id11_u = 0.0f; // Output
float id11_v = 0.0f; // Output
// Input : UV 
id11_UVs = texCoord; 
id11_u = texCoord.x; 
id11_v = texCoord.y; 


float id12_Value = id11_u;  // Input
float id14_Result = 0.0f; // Output
// Input : Scalar 
id14_Result = 0.02;

float id12_Step = id14_Result;  // Input
float id12_Result = 0.0f; // Output
// Step 
id12_Result = floor(id12_Value / id12_Step) * id12_Step;


float id21_X = id12_Result;  // Input

float id13_Value = id11_v;  // Input

float id13_Step = id14_Result;  // Input
float id13_Result = 0.0f; // Output
// Step 
id13_Result = floor(id13_Value / id13_Step) * id13_Step;


float id21_Y = id13_Result;  // Input
float id21_Z = 0.0f;  // Input
vec3 id21_Vector3 = vec3(0.0f); // Output
// MakeVec3Node 
id21_Vector3 = vec3(id21_X, id21_Y, id21_Z); 


vec3 id22_A = id21_Vector3;  // Input
vec3 id15_Result = vec3(0.0f); // Output
// Input : Vec3 
id15_Result = vec3(4, 4, 4);

vec3 id22_B = id15_Result;  // Input
vec3 id22_Result = vec3(0.0f); // Output
id22_Result = id22_A * id22_B;
vec3 Diffuse = id22_Result;  // Input
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
