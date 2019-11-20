// Rule of 3
// 3 things must matxh
// 1. C++ Vertex struct
// 2. input layout
// 3. HLSL vertex struct

struct OutVertex
{
    float4 Pos : SV_POSITION; // System value
    float4 Color : OCOLOR;
};


float4 main(OutVertex input) : SV_Target
{
    return float4(1, 1, 0, 1.0f);
}