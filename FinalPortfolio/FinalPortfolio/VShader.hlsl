// Rule of 3
// 3 things must matxh
// 1. C++ Vertex struct
// 2. input layout
// 3. HLSL vertex struct

#pragma pack_matrix(row_major)

struct Vertex
{
    float4 Pos   : POSITION;
    float4 Color : COLOR;
};

struct OutVertex
{
    float4 Pos   : SV_POSITION; // System value
    float4 Color : OCOLOR;
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
    output.Pos = _vert.Pos;
    output.Color = _vert.Color;

    // Do math here (Shader Intrinsics)
    // Row major method 3 flip mul
    output.Pos = mul(output.Pos, WorldMatrix);
    output.Pos = mul(output.Pos, ViewMatrix);
    output.Pos = mul(output.Pos, ProjectionMatrix);

    return output;
}