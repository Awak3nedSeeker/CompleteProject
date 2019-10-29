// Rule of 3
// 3 things must matxh
// 1. C++ Vertex struct
// 2. input layout
// 3. HLSL vertex struct

#pragma pack_matrix(row_major)

struct Vertex
{
    float3 Pos : POSITION;
    float3 UVW : TEXCOORD;
    float3 NRM : NORMAL;
};

struct OutVertex
{
    float4 Pos : SV_POSITION;
    float4 Color : OCOLOR;
    float2 UV : UV;
    float3 NRM : NORMAL;
    float3 Local : LOCAL;
};

cbuffer Shader_Vars : register(b0)
{
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
};

OutVertex main(Vertex _vert)
{
    OutVertex output = (OutVertex) 0;
    output.Pos = float4(_vert.Pos, 1);
    output.Color.xyz = _vert.NRM;
    output.UV = _vert.UVW.xy;
    output.NRM = _vert.NRM;
    output.Local = _vert.Pos;

    // Do math here (Shader Intrinsics)
    // Row major method 3 flip mul
    output.Pos = mul(output.Pos, WorldMatrix);
    output.Pos = mul(output.Pos, ViewMatrix);
    output.Pos = mul(output.Pos, ProjectionMatrix);

    //output.NRM = mul(output.NRM, WorldMatrix);

    return output;
}