#pragma once

// Inlcudes
#include "stdafx.h"
#include "FinalPortfolio.h"

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

#include <vector>
#include <iostream>
#include <DirectXMath.h>

using namespace DirectX;
using namespace std;

#include "DDSTextureLoader.h"

// Complex Mesh h
#include "Assets/StoneHenge.h"
#include "Assets/Ship.h"

#include "VShader.csh"
#include "PShader.csh"
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
	float range;
	XMFLOAT3 dir;
	float cone;
	XMFLOAT3 att;
	float pad2;
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
ID3D11Buffer* DeerVBuffer;       // Deer Vertex Buffer
ID3D11Buffer* DeerIBuffer;       // Deer Index Buffer
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
ID3D11Texture2D* StoneTexture;        // Stonehenge
ID3D11ShaderResourceView* StoneView;  // Stonehenge

// Global Numbers and Objects ---------------------------------------------------------------------------------------------------------------------------------------

// Numbers
bool Lend = false;
bool DLend = false;
unsigned int NumVerts = 0;
float AspectRatio = 1;
float FOV = 3.14f / 2.0f;
float FPlane = 100000.0f;
float NPlane = 0.1f;

vector<Vertex_3D> vertexlist;
vector<UINT> indices;

Vertex_3D* SkyVerts_3D;
unsigned int* SkyIndices;

unsigned int SkyVerts;
unsigned int SkyIndice;

Vertex_3D* DeerVerts_3D;
unsigned int* DeerIndices;

unsigned int DeerVerts;
unsigned int DeerIndice;

unsigned int numVerts;
unsigned int numIndices;

// Objects
Light light;
cbPerFrame constbuffPerFrame;