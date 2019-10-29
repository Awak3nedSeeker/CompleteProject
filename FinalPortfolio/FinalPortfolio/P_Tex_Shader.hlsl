// Rule of 3
// 3 things must matxh
// 1. C++ Vertex struct
// 2. input layout
// 3. HLSL vertex struct

struct OutputVertex
{
    float4 Pos : SV_POSITION;
    float4 Color : OCOLOR;
    float2 UV : UV;
    float3 NRM : NORMAL;
};

struct Light
{
    float3 dir;
    float4 ambient;
    float4 diffuse;
};

cbuffer cbPerFrame : register(b)
{
    Light light;
};

cbuffer Shader_Vars : register(b0)
{
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
};

Texture2D env : register(t0);
SamplerState envFilter : register(s0);

float4 main(OutputVertex inputP) : SV_TARGET
{
    //float3 dir = float3(-1.0f, 0.5f, 0.0f);
    //float4 ambient = float4(0.2f, 0.2f, 0.2f, 1.0f);
    //float4 light_diffuse = float4(0.6f, 0.6f, 0.7f, 1.0f);

    inputP.NRM = normalize(inputP.NRM);

    float4 diffuse = env.Sample(envFilter, inputP.UV);

    float3 finalcolor;

    finalcolor = diffuse.xyz * light.ambient.xyz;
    finalcolor += saturate(dot(light.dir, inputP.NRM) * light.diffuse * diffuse);

    return float4(finalcolor, diffuse.a);
}