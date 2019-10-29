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
    float3 Local : LOCAL;
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

TextureCube env : register(t0);
SamplerState envFilter : register(s0);

float4 main(OutputVertex inputP) : SV_TARGET
{
    return env.Sample(envFilter, inputP.Local);
}