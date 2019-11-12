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
    float3 pos;
    float3 Spos;
    float range;
    float3 dir;
    float3 Sdir;
    float cone;
    float3 att;
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

float4 Directionallight(OutputVertex input)
{
    input.NRM = normalize(input.NRM);

    float4 diffuse = env.Sample(envFilter, input.UV);

    float3 finalcolor;

    finalcolor = diffuse.xyz * light.ambient.xyz;
    finalcolor += saturate(dot(light.dir, input.NRM) * light.diffuse * diffuse);

    return float4(finalcolor, diffuse.a);
}

float4 Pointlight(OutputVertex input)
{

    input.NRM = normalize(input.NRM);

    float4 diffuse = env.Sample(envFilter, input.UV);

    
    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
   
    float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };
    
    //Create the vector between light position and pixels position
    float3 lightToPixelVec = light.pos - input.Local;
        
    //Find the distance between the light pos and pixel pos
    float d = length(lightToPixelVec);
    
    //Create the ambient light
    float3 finalAmbient = diffuse * light.ambient;

    //If pixel is too far, return pixel color with ambient light
    if (d > light.range)
    {
        return float4(finalAmbient, diffuse.a);
    }
        
    //Turn lightToPixelVec into a unit length vector describing
    //the pixels direction from the lights position
    lightToPixelVec /= d;
    
    //Calculate how much light the pixel gets by the angle
    //in which the light strikes the pixels surface
    float howMuchLight = dot(lightToPixelVec, input.NRM);

    //If light is striking the front side of the pixel
    if (howMuchLight > 0.0f)
    {
        //Add light to the finalColor of the pixel
        finalColor += howMuchLight * diffuse * Color;
        
        //Calculate Light's Falloff factor
        finalColor /= light.att[0] + (light.att[1] * d) + (light.att[2] * (d * d));
    }
        
    //make sure the values are between 1 and 0, and add the ambient
    finalColor = saturate(finalColor + finalAmbient);
    
    //Return Final Color
    return float4(finalColor, diffuse.a);
}

float4 Spotlight(OutputVertex input)
{
    //float3 NPos = { 0, 2, -15 };
    //float3 dir = { 0, -1, 0.75 };
    float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

    input.NRM = normalize(input.NRM);

    float4 diffuse = env.Sample(envFilter, input.UV);

    float3 finalColor = float3(0.0f, 0.0f, 0.0f);
    
    //Create the vector between light position and pixels position
    float3 lightToPixelVec = light.Spos - input.Local;
        
    //Find the distance between the light pos and pixel pos
    float d = length(lightToPixelVec);
    
    //Add the ambient light
    float3 finalAmbient = diffuse * light.ambient;

    //If pixel is too far, return pixel color with ambient light
    if (d > light.range)
    {
        return float4(finalAmbient, diffuse.a);
    }
        
    lightToPixelVec /= d;
    float howMuchLight = dot(lightToPixelVec, input.NRM);

    //If light is striking the front side of the pixel
    if (howMuchLight > 0.0f)
    {
        finalColor += diffuse * Color;             
        finalColor /= (light.att[0] + (light.att[1] * d)) + (light.att[2] * (d * d));

        //Calculate falloff from center to edge of pointlight cone
        finalColor *= pow(max(dot(-lightToPixelVec, light.Sdir), 0.0f), light.cone);
    }
    
    finalColor = saturate(finalColor + finalAmbient);
    return float4(finalColor, diffuse.a);
}

float4 main(OutputVertex inputP) : SV_TARGET
{
    float4 D = Directionallight(inputP);
    float4 P = Pointlight(inputP);
    float4 S = Spotlight(inputP);

    return saturate(S);
}