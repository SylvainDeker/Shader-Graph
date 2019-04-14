/*
 *	This file defines common microfacet functions that could be used ba several bsdf models
 */
const float Pi = 3.14159265359;
const float InvPi = 0.31830988618379067154;

// y = x^2
float sqr(float x) {
    return x*x;
}

// Compute Schlick Fresnel approximation for dielectric
// Weight
float SchlickWeight(float cosTheta) {
    float m = clamp(1 - cosTheta, 0, 1);
    return sqr(sqr(m)) * m;
}
// Fresnel at normal incidence
float SchlickR0FromEta(float eta) {
    return sqr(eta - 1) / sqr(eta + 1);
    }

// Fresnel approximation at Theta incidence
vec3 FresnelShlick(float cosThetaI, vec3 F0, vec3 F90) {
    float m = SchlickWeight(cosThetaI);
    return mix ( F0, F90, m );
}

// Evaluate Fresnel for a dielectric material
float FresnelDielectric(float cosThetaI, float etaI, float etaT) {

    if (cosThetaI <0) {
        float e = etaI;
        etaI = etaT;
        etaT = e;
        cosThetaI = abs(cosThetaI);
    }

    float sinThetaI = sqrt(max(0.f, 1 - cosThetaI * cosThetaI));
    float sinThetaT = etaI / etaT * sinThetaI;

    if (sinThetaT >= 1) return 1.f;

    float cosThetaT = sqrt(max(0.f, 1.f - sinThetaT * sinThetaT));
    float Rparl = ((etaT * cosThetaI) - (etaI * cosThetaT)) /
                  ((etaT * cosThetaI) + (etaI * cosThetaT));
    float Rperp = ((etaI * cosThetaI) - (etaT * cosThetaT)) /
                  ((etaI * cosThetaI) + (etaT * cosThetaT));

    return (Rparl * Rparl + Rperp * Rperp) / 2.0f;
}

// Evaluate Fresnel for a conductor material
vec3 FresnelConductor(float cosThetaI, vec3 etaI, vec3 etaT, vec3 k) {
    vec3 eta = etaT / etaI;
    vec3 etak = k / etaI;

    float cosThetaI2 = cosThetaI * cosThetaI;
    float sinThetaI2 = 1. - cosThetaI2;
    vec3 eta2 = eta * eta;
    vec3 etak2 = etak * etak;

    vec3 t0 = eta2 - etak2 - sinThetaI2;
    vec3 a2plusb2 = sqrt(t0 * t0 + 4 * eta2 * etak2);
    vec3 t1 = a2plusb2 + cosThetaI2;
    vec3 a = sqrt(0.5f * (a2plusb2 + t0));
    vec3 t2 = 2.f * cosThetaI * a;
    vec3 Rs = (t1 - t2) / (t1 + t2);

    vec3 t3 = cosThetaI2 * a2plusb2 + sinThetaI2 * sinThetaI2;
    vec3 t4 = t2 * sinThetaI2;
    vec3 Rp = Rs * (t3 - t4) / (t3 + t4);

    return 0.5f * (Rp + Rs);
}

// Trowbridge-Reitz Distribution
// NOTE : all vec3 representing a direction must be expressed in local frame to use these functions
float CosTheta(vec3 w) { return w.z; }
float Cos2Theta(vec3 w) { return w.z * w.z; }
float AbsCosTheta(vec3 w) { return abs(w.z); }
float Sin2Theta(vec3 w) { return max(0, 1 - Cos2Theta(w)); }
float SinTheta(vec3 w) { return sqrt(Sin2Theta(w)); }
float TanTheta(vec3 w) { return SinTheta(w) / CosTheta(w); }
float Tan2Theta(vec3 w) { return Sin2Theta(w) / Cos2Theta(w); }
float CosPhi(vec3 w) {
    float sinTheta = SinTheta(w);
    return (sinTheta == 0) ? 1 : clamp(w.x / sinTheta, -1, 1);
}
float SinPhi(vec3 w) {
    float sinTheta = SinTheta(w);
    return (sinTheta == 0) ? 0 : clamp(w.y / sinTheta, -1, 1);
}
float Cos2Phi(vec3 w) { return CosPhi(w) * CosPhi(w); }
float Sin2Phi(vec3 w) { return SinPhi(w) * SinPhi(w); }
float CosDPhi(vec3 wa, vec3 wb) {
    return clamp(
        (wa.x * wb.x + wa.y * wb.y) / sqrt((wa.x * wa.x + wa.y * wa.y) *
                                                (wb.x * wb.x + wb.y * wb.y)),
        -1, 1);
}

float TRD_RoughnessToAlpha(float roughness) {
    float r =  max(roughness, 1e-3);
    float x = log(r);
    return 1.62142f + 0.819955f * x + 0.1734f * x * x + 0.0171201f * x * x * x +
           0.000640711f * x * x * x * x;
}

float TRD_Lambda(vec3 w, float alphax, float alphay) {
    float absTanTheta = abs(TanTheta(w));
    if (isinf(absTanTheta))
        return 0.;
    float alpha =
        sqrt(Cos2Phi(w) * sqr(alphax) + Sin2Phi(w) * sqr(alphay));
    float alpha2Tan2Theta = sqr(alpha * absTanTheta);
    return (-1 + sqrt(1. + alpha2Tan2Theta)) / 2;
}

float TRD_D(vec3 wh, float alphax, float alphay) {
    float tan2Theta = Tan2Theta(wh);

    if (isinf(tan2Theta))
        return 0.f;

    float cos4Theta = sqr(Cos2Theta(wh));

    float e =
        ( Cos2Phi(wh) / sqr(alphax) +
          Sin2Phi(wh) / sqr(alphay) ) *
        tan2Theta;

    return (1.0f / (Pi * alphax * alphay * cos4Theta * sqr(1 + e)));
}

float TRD_G(vec3 wo, vec3 wi, float alphax, float alphay) {
    return 1/(1+TRD_Lambda(wo, alphax, alphay)+TRD_Lambda(wi, alphax, alphay));
}

