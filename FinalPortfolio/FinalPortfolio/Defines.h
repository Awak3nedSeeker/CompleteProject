#pragma once

// Inlcudes
#include "stdafx.h"
#include "FinalPortfolio.h"

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

#include <vector>
#include <iostream>
#include <DirectXMath.h>
#include <d3d9types.h>

using namespace DirectX;
using namespace std;

#include "DDSTextureLoader.h"

// Complex Mesh h
#include "Assets/StoneHenge.h"
#include "Assets/Ship.h"

#include "VShader.csh"
#include "PShader.csh"
#include "BunShader.csh"
#include "KnightShader.csh"
#include "HolyShader.csh"
#include "P_Tex_Shader.csh"
#include "VMeshShader.csh"
#include "VMeshShader_EXP.csh"
#include "SkyboxShader.csh"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

//Global Structs

struct WVP
{
	XMFLOAT4X4 WMatrix;
	XMFLOAT4X4 VMatrix;
	XMFLOAT4X4 PMatrix;
}MyMatricies;

struct Vertex
{
	float Pos[4];
	float Color[4];
};

struct Vertex_3D
{
	XMFLOAT3 Pos;
	XMFLOAT3 UV;
	XMFLOAT3 NRM;
};

struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	XMFLOAT3 pos;
	float pad;
	XMFLOAT3 Spos;
	float range;
	XMFLOAT3 dir;
	float pad2;
	XMFLOAT3 Sdir;
	float cone;
	XMFLOAT3 att;
	float pad3;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
};

struct cbPerFrame
{
	Light  light;
};

struct Mesh
{
	Vertex_3D* Vert;
	unsigned int* indi;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

// Global Variables
// for init
ID3D11Device* MyDev;
IDXGISwapChain* MySwap;
ID3D11DeviceContext* MyCon;

// for drawing
D3D11_VIEWPORT MyView;
ID3D11RenderTargetView* MyTarget;

// Buffers
ID3D11Buffer* VBuffer;           // Pyramid Vertex Buffer
ID3D11Buffer* CBuffer;           // Constant Buffer (MVP)
ID3D11Buffer* SkyVBuffer;        // Skybox Vertex Buffer
ID3D11Buffer* SkyIBuffer;        // Skybox Index Buffer
ID3D11Buffer* Planet01VBuffer;   // Planet 01 Vertex Buffer
ID3D11Buffer* Planet01IBuffer;   // Planet 01 Index Buffer
ID3D11Buffer* Planet02VBuffer;   // Planet 02 Vertex Buffer
ID3D11Buffer* Planet02IBuffer;   // Planet 02 Index Buffer
ID3D11Buffer* Planet03VBuffer;   // Planet 03 Vertex Buffer
ID3D11Buffer* Planet03IBuffer;   // Planet 03 Index Buffer
ID3D11Buffer* MoonVBuffer;   // Moon Vertex Buffer
ID3D11Buffer* MoonIBuffer;   // Moon Index Buffer
ID3D11Buffer* GroundVBuffer;     // Ground Vertex Buffer
ID3D11Buffer* GroundIBuffer;     // Ground Index Buffer
ID3D11Buffer* CaveVBuffer;       // Cave Vertex Buffer
ID3D11Buffer* CaveIBuffer;       // Cave Index Buffer
ID3D11Buffer* HolyVBuffer;       // Holy Vertex Buffer
ID3D11Buffer* HolyIBuffer;       // Holy Index Buffer
ID3D11Buffer* BunVBuffer;       // Bun Vertex Buffer
ID3D11Buffer* BunIBuffer;       // Bun Index Buffer
ID3D11Buffer* KnightVBuffer;       // knight Vertex Buffer
ID3D11Buffer* KnightIBuffer;       // Knight Index Buffer
ID3D11Buffer* StoneVBuffer;      // Stonehenge Vertex Buffer
ID3D11Buffer* StoneIBuffer;      // Stonehenge Index Buffer
ID3D11Buffer* cbPerFrameBuffer;  // Per Frame Buffer


// Layouts
ID3D11InputLayout* VLayout;      // Pyramid(Primative) Layout
ID3D11InputLayout* VMeshLayout;  // Mesh Layout

// Shaders
ID3D11PixelShader* TexShader;       // Texture Shader
ID3D11PixelShader* Sky_Shader;      // Skybox Shader
ID3D11PixelShader* Pix_Shader;      // Normal Color Pixel Shader
ID3D11PixelShader* Lit_Shader;      // Normal Color Pixel Shader
ID3D11PixelShader* Bun_Shader;      // Normal Color Pixel Shader
ID3D11PixelShader* Knight_Shader;      // Normal Color Pixel Shader
ID3D11PixelShader* Deer_Shader;     // Deer Shader
ID3D11VertexShader* Vert_Shader;    // Vertex Shader
ID3D11VertexShader* VertexMShader;  // Vertex Mesh Shader


// Z Buffer
ID3D11Texture2D* ZBuffer;
ID3D11DepthStencilView* ZView;

// Sub Resource
D3D11_MAPPED_SUBRESOURCE GPUBuffer;

// Texture info
ID3D11Texture2D* SkyTexture;        // Skybox
ID3D11ShaderResourceView* SkyView;  // Skybox
ID3D11Texture2D* Sky2Texture;        // Skybox
ID3D11ShaderResourceView* Sky2View;  // Skybox
ID3D11Texture2D* StoneTexture;        // Stonehenge
ID3D11ShaderResourceView* StoneView;  // Stonehenge
ID3D11Texture2D* Planet01Texture;        // Planet 01
ID3D11ShaderResourceView* Planet01View;  // Planet 01
ID3D11Texture2D* Planet02Texture;        // Planet 02
ID3D11ShaderResourceView* Planet02View;  // Planet 02
ID3D11Texture2D* Planet03Texture;        // Planet 03
ID3D11ShaderResourceView* Planet03View;  // Planet 03
ID3D11Texture2D* MoonTexture;        // Moon
ID3D11ShaderResourceView* MoonView;  // Moon
// Global Numbers and Objects ---------------------------------------------------------------------------------------------------------------------------------------

// Numbers
bool Lend = false;
bool DLend = false;
bool SLDend = false;
bool SLPend = false;
bool OnScreen1 = true;
bool OnScreen2 = false;
unsigned int NumVerts = 0;
float AspectRatio = 1;
float FOV = 3.14f / 2.0f;
float FPlane = 100000.0f;
float NPlane = 0.1f;

XMMATRIX Orbit;
vector<Vertex_3D> vertexlist;
vector<UINT> indices;

Vertex_3D* SkyVerts_3D;
unsigned int* SkyIndices;
unsigned int SkyVerts;
unsigned int SkyIndice;

Vertex_3D* Planet01_3D;
unsigned int* Planet01Indices;
unsigned int Planet01Verts;
unsigned int Planet01Indice;

Vertex_3D* Planet02_3D;
unsigned int* Planet02Indices;
unsigned int Planet02Verts;
unsigned int Planet02Indice;

Vertex_3D* Planet03_3D;
unsigned int* Planet03Indices;
unsigned int Planet03Verts;
unsigned int Planet03Indice;

Vertex_3D* Ground_3D;
unsigned int* GroundIndices;
unsigned int GroundVerts;
unsigned int GroundIndice;

Vertex_3D* Cave_3D;
unsigned int* CaveIndices;
unsigned int CaveVerts;
unsigned int CaveIndice;

Vertex_3D* Moon_3D;
unsigned int* MoonIndices;
unsigned int MoonVerts;
unsigned int MoonIndice;

Vertex_3D* Holy_3D;
unsigned int* HolyIndices;
unsigned int HolyVerts;
unsigned int HolyIndice;

Vertex_3D* Bun_3D;
unsigned int* BunIndices;
unsigned int BunVerts;
unsigned int BunIndice;

Vertex_3D* Knight_3D;
unsigned int* KnightIndices;
unsigned int KnightVerts;
unsigned int KnightIndice;

unsigned int numVerts;
unsigned int numIndices;

// Objects
Light light;
cbPerFrame constbuffPerFrame;




//Vertex_3D* DeerVerts_3D;
//unsigned int* DeerIndices;
//
//unsigned int DeerVerts;
//unsigned int DeerIndice;
//ID3D11Buffer* DeerVBuffer;       // Deer Vertex Buffer
//ID3D11Buffer* DeerIBuffer;       // Deer Index Buffer