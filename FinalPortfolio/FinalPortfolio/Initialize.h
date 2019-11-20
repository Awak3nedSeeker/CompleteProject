#pragma once
#include"Defines.h"
#include "OBJLoader.h"



void Setup(HWND hWnd)
{
	RECT MyWin;
	HRESULT hr;
	GetClientRect(hWnd, &MyWin);

	//attach d3d11 to window
	D3D_FEATURE_LEVEL dx11 = D3D_FEATURE_LEVEL_11_0;

// Needed Variables------------------------------------------------------------------------------------------------------------------------------------//
	
	// Set Pyramid Vertices
	Vertex Tri[] =
	{
		// Front
		{ {0, 1.0f, 0, 1}, {1, 1, 1, 1} },
		{ {0.25f, -0.25f, -0.25f, 1}, {1, 0, 1, 1} },
		{ {-0.25f, -0.25f, -0.25f, 1}, {1, 1, 0, 1} },

		// Right side
		{ {0, 1.0f, 0, 1}, {1, 1, 1, 1} },
		{ {0.25f, -0.25f, 0.25f, 1}, {1, 0, 1, 1} },
		{ {0.25f, -0.25f, -0.25f, 1}, {1, 1, 0, 1} },

		// Back side
		{ {0, 1.0f, 0, 1}, {1, 1, 1, 1} },
		{ {-0.25f, -0.25f, 0.25f, 1}, {1, 0, 1, 1} },
		{ {0.25f, -0.25f, 0.25f, 1}, {1, 1, 0, 1} },

		// Left side
		{ {0, 1.0f, 0, 1}, {1, 1, 1, 1} },
		{ {-0.25f, -0.25f, -0.25f, 1}, {1, 0, 1, 1} },
		{ {-0.25f, -0.25f, 0.25f, 1}, {1, 1, 0, 1} },
	};
	NumVerts = ARRAYSIZE(Tri);

	// Set View Variables
	MyView.Width = float(MyWin.right - MyWin.left);
	MyView.Height = float(MyWin.bottom - MyWin.top);
	MyView.TopLeftX = MyView.TopLeftY = 0;
	MyView.MinDepth = 0;
	MyView.MaxDepth = 1;

	// Set Aspect Ratio
	AspectRatio = (MyView.Width / MyView.Height);

	// Skybox Loader
	Mesh Skybox = ModelLoader("Assets/Skybox.obj", 20000.0f, vertexlist, indices);
	SkyVerts = numVerts;
	SkyIndice = numIndices;
	SkyIndices = Skybox.indi;
	SkyVerts_3D = Skybox.Vert;

	// Planet 01 Loader
	Mesh Planet01 = ModelLoader("Assets/Planet06.obj", 1.5f, vertexlist, indices);
	Planet01_3D = Planet01.Vert;
	Planet01Indices = Planet01.indi;
	Planet01Verts = numVerts;
	Planet01Indice = numIndices;

	// Planet 02 Loader
	Mesh Planet02 = ModelLoader("Assets/Planet06.obj", 0.3f, vertexlist, indices);
	Planet02_3D = Planet02.Vert;
	Planet02Indices = Planet02.indi;
	Planet02Verts = numVerts;
	Planet02Indice = numIndices;

	// Planet 03 Loader
	Mesh Planet03 = ModelLoader("Assets/Planet06.obj", 0.3f, vertexlist, indices);
	Planet03_3D = Planet03.Vert;
	Planet03Indices = Planet03.indi;
	Planet03Verts = numVerts;
	Planet03Indice = numIndices;

	// Moon Loader
	Mesh Moon = ModelLoader("Assets/Planet06.obj", 0.3f, vertexlist, indices);
	Moon_3D = Moon.Vert;
	MoonIndices = Moon.indi;
	MoonVerts = numVerts;
	MoonIndice = numIndices;

	// Ground Loader
	Mesh Ground = ModelLoader("Assets/ground.obj", 0.1f, vertexlist, indices);
	Ground_3D = Ground.Vert;
	GroundIndices = Ground.indi;
	GroundVerts = numVerts;
	GroundIndice = numIndices;

	// Cave Loader
	Mesh Cave = ModelLoader("Assets/Cave.obj", 1.0f, vertexlist, indices);
	Cave_3D = Cave.Vert;
	CaveIndices = Cave.indi;
	CaveVerts = numVerts;
	CaveIndice = numIndices;

	// Holy Loader
	Mesh Holy = ModelLoader("Assets/Holy.obj", 0.75f, vertexlist, indices);
	Holy_3D = Holy.Vert;
	HolyIndices = Holy.indi;
	HolyVerts = numVerts;
	HolyIndice = numIndices;

	// Bun Loader
	Mesh Bun = ModelLoader("Assets/bun.obj", 0.01f, vertexlist, indices);
	Bun_3D = Bun.Vert;
	BunIndices = Bun.indi;
	BunVerts = numVerts;
	BunIndice = numIndices;

	// Knight Loader
	Mesh Knight = ModelLoader("Assets/chevalier.obj", 7.0f, vertexlist, indices);
	Knight_3D = Knight.Vert;
	KnightIndices = Knight.indi;
	KnightVerts = numVerts;
	KnightIndice = numIndices;

	// Ship Loader
	Mesh Ship = ModelLoader("Assets/Ship.obj", 7.0f, vertexlist, indices);
	Ship_3D = Ship.Vert;
	ShipIndices = Ship.indi;
	ShipVerts = numVerts;
	ShipIndice = numIndices;

	// Light Info
	light.dir = XMFLOAT3(1, -0.5f, 0);
	light.ambient = XMFLOAT4(1, 1, 1, 1.0f);
	light.diffuse = XMFLOAT4(0.3f, 0.3f, 0.4f, 1.0f);
	light.pos = XMFLOAT3(-15.0f, 2.0f, -5.0f);
	light.range = 900.0f;
	light.cone = 5.0f;
	light.att = XMFLOAT3(0.0f, 0.2f, 0.0f);
	light.Spos = XMFLOAT3(0, 5, -20);
	light.Sdir = XMFLOAT3(0, -1, 0);

// Needed Variables------------------------------------------------------------------------------------------------------------------------------------//

// Create Descriptors-----------------------------------------------------------------------------------------------------------------------------------//

	// SwapChain
	DXGI_SWAP_CHAIN_DESC swapchain;
	ZeroMemory(&swapchain, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapchain.BufferCount = 1;
	swapchain.OutputWindow = hWnd;
	swapchain.Windowed = true;
	swapchain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchain.BufferDesc.Width = MyWin.right - MyWin.left;
	swapchain.BufferDesc.Height = MyWin.bottom - MyWin.top;
	swapchain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain.SampleDesc.Count = 1;

	// Pyramid Vertex Buffer
	D3D11_BUFFER_DESC BDesc;
	D3D11_SUBRESOURCE_DATA SubData;
	ZeroMemory(&BDesc, sizeof(BDesc));
	ZeroMemory(&SubData, sizeof(SubData));

	BDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BDesc.ByteWidth = sizeof(Tri);
	BDesc.CPUAccessFlags = 0;
	BDesc.MiscFlags = 0;
	BDesc.StructureByteStride = 0;
	BDesc.Usage = D3D11_USAGE_IMMUTABLE;

	// Constant Buffer
	D3D11_BUFFER_DESC CDesc;
	ZeroMemory(&CDesc, sizeof(CDesc));

	CDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CDesc.ByteWidth = sizeof(WVP);
	CDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CDesc.MiscFlags = 0;
	CDesc.StructureByteStride = 0;
	CDesc.Usage = D3D11_USAGE_DYNAMIC;
	
	// Create Z buffer and view (Don't need for gateware)
	D3D11_TEXTURE2D_DESC ZDesc;
	ZeroMemory(&ZDesc, sizeof(ZDesc));

	ZDesc.ArraySize = 1;
	ZDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ZDesc.Width = swapchain.BufferDesc.Width;
	ZDesc.Height = swapchain.BufferDesc.Height;
	ZDesc.Format = DXGI_FORMAT_D32_FLOAT;
	ZDesc.Usage = D3D11_USAGE_DEFAULT;
	ZDesc.MipLevels = 1;
	ZDesc.SampleDesc.Count = 1;

	// Smapler State
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD = FLT_MAX;
	
	// Light Constant Buffer
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerFrame);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC OBJVReader;
	ZeroMemory(&OBJVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Skybox Vertex Buffer
	OBJVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	OBJVReader.ByteWidth = sizeof(Vertex_3D) * SkyVerts;
	OBJVReader.CPUAccessFlags = 0;
	OBJVReader.MiscFlags = 0;
	OBJVReader.StructureByteStride = 0;
	OBJVReader.Usage = D3D11_USAGE_IMMUTABLE;
	
	// Skybox Index Buffer
	D3D11_BUFFER_DESC OBJIReader;
	ZeroMemory(&OBJIReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	OBJIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	OBJIReader.ByteWidth = sizeof(UINT) * SkyIndice;
	OBJIReader.CPUAccessFlags = 0;
	OBJIReader.MiscFlags = 0;
	OBJIReader.StructureByteStride = 0;
	OBJIReader.Usage = D3D11_USAGE_IMMUTABLE;


	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC DeerVReader;
	ZeroMemory(&DeerVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Deer Vertex Buffer
	DeerVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DeerVReader.ByteWidth = sizeof(Vertex_3D) * Planet01Verts;
	DeerVReader.CPUAccessFlags = 0;
	DeerVReader.MiscFlags = 0;
	DeerVReader.StructureByteStride = 0;
	DeerVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Deer Index Buffer
	D3D11_BUFFER_DESC DeerIReader;
	ZeroMemory(&DeerIReader, sizeof(D3D11_BUFFER_DESC));

	DeerIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DeerIReader.ByteWidth = sizeof(UINT) * Planet01Indice;
	DeerIReader.CPUAccessFlags = 0;
	DeerIReader.MiscFlags = 0;
	DeerIReader.StructureByteStride = 0;
	DeerIReader.Usage = D3D11_USAGE_IMMUTABLE;


	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC StoneVReader;
	ZeroMemory(&StoneVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Deer Vertex Buffer
	StoneVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	StoneVReader.ByteWidth = sizeof(StoneHenge_data);
	StoneVReader.CPUAccessFlags = 0;
	StoneVReader.MiscFlags = 0;
	StoneVReader.StructureByteStride = 0;
	StoneVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Deer Index Buffer
	D3D11_BUFFER_DESC StoneIReader;
	ZeroMemory(&StoneIReader, sizeof(D3D11_BUFFER_DESC));

	StoneIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	StoneIReader.ByteWidth = sizeof(unsigned int) * ARRAYSIZE(StoneHenge_indicies);
	StoneIReader.CPUAccessFlags = 0;
	StoneIReader.MiscFlags = 0;
	StoneIReader.StructureByteStride = 0;
	StoneIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC Planet02VReader;
	ZeroMemory(&Planet02VReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	Planet02VReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Planet02VReader.ByteWidth = sizeof(Vertex_3D) * Planet02Verts;
	Planet02VReader.CPUAccessFlags = 0;
	Planet02VReader.MiscFlags = 0;
	Planet02VReader.StructureByteStride = 0;
	Planet02VReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC Planet02IReader;
	ZeroMemory(&Planet02IReader, sizeof(D3D11_BUFFER_DESC));

	Planet02IReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Planet02IReader.ByteWidth = sizeof(UINT) * Planet02Indice;
	Planet02IReader.CPUAccessFlags = 0;
	Planet02IReader.MiscFlags = 0;
	Planet02IReader.StructureByteStride = 0;
	Planet02IReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC Planet03VReader;
	ZeroMemory(&Planet03VReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	Planet03VReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Planet03VReader.ByteWidth = sizeof(Vertex_3D) * Planet03Verts;
	Planet03VReader.CPUAccessFlags = 0;
	Planet03VReader.MiscFlags = 0;
	Planet03VReader.StructureByteStride = 0;
	Planet03VReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC Planet03IReader;
	ZeroMemory(&Planet03IReader, sizeof(D3D11_BUFFER_DESC));

	Planet03IReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Planet03IReader.ByteWidth = sizeof(UINT) * Planet03Indice;
	Planet03IReader.CPUAccessFlags = 0;
	Planet03IReader.MiscFlags = 0;
	Planet03IReader.StructureByteStride = 0;
	Planet03IReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC MoonVReader;
	ZeroMemory(&MoonVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	MoonVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	MoonVReader.ByteWidth = sizeof(Vertex_3D) * MoonVerts;
	MoonVReader.CPUAccessFlags = 0;
	MoonVReader.MiscFlags = 0;
	MoonVReader.StructureByteStride = 0;
	MoonVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC MoonIReader;
	ZeroMemory(&MoonIReader, sizeof(D3D11_BUFFER_DESC));

	MoonIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	MoonIReader.ByteWidth = sizeof(UINT) * MoonIndice;
	MoonIReader.CPUAccessFlags = 0;
	MoonIReader.MiscFlags = 0;
	MoonIReader.StructureByteStride = 0;
	MoonIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC GroundVReader;
	ZeroMemory(&GroundVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	GroundVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	GroundVReader.ByteWidth = sizeof(Vertex_3D) * GroundVerts;
	GroundVReader.CPUAccessFlags = 0;
	GroundVReader.MiscFlags = 0;
	GroundVReader.StructureByteStride = 0;
	GroundVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC GroundIReader;
	ZeroMemory(&GroundIReader, sizeof(D3D11_BUFFER_DESC));

	GroundIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	GroundIReader.ByteWidth = sizeof(UINT) * GroundIndice;
	GroundIReader.CPUAccessFlags = 0;
	GroundIReader.MiscFlags = 0;
	GroundIReader.StructureByteStride = 0;
	GroundIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC CaveVReader;
	ZeroMemory(&CaveVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	CaveVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	CaveVReader.ByteWidth = sizeof(Vertex_3D) * CaveVerts;
	CaveVReader.CPUAccessFlags = 0;
	CaveVReader.MiscFlags = 0;
	CaveVReader.StructureByteStride = 0;
	CaveVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC CaveIReader;
	ZeroMemory(&CaveIReader, sizeof(D3D11_BUFFER_DESC));

	CaveIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	CaveIReader.ByteWidth = sizeof(UINT) * CaveIndice;
	CaveIReader.CPUAccessFlags = 0;
	CaveIReader.MiscFlags = 0;
	CaveIReader.StructureByteStride = 0;
	CaveIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC HolyVReader;
	ZeroMemory(&HolyVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	HolyVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	HolyVReader.ByteWidth = sizeof(Vertex_3D) * HolyVerts;
	HolyVReader.CPUAccessFlags = 0;
	HolyVReader.MiscFlags = 0;
	HolyVReader.StructureByteStride = 0;
	HolyVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC HolyIReader;
	ZeroMemory(&HolyIReader, sizeof(D3D11_BUFFER_DESC));

	HolyIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	HolyIReader.ByteWidth = sizeof(UINT) * HolyIndice;
	HolyIReader.CPUAccessFlags = 0;
	HolyIReader.MiscFlags = 0;
	HolyIReader.StructureByteStride = 0;
	HolyIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC BunVReader;
	ZeroMemory(&BunVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	BunVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BunVReader.ByteWidth = sizeof(Vertex_3D) * BunVerts;
	BunVReader.CPUAccessFlags = 0;
	BunVReader.MiscFlags = 0;
	BunVReader.StructureByteStride = 0;
	BunVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC BunIReader;
	ZeroMemory(&BunIReader, sizeof(D3D11_BUFFER_DESC));

	BunIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BunIReader.ByteWidth = sizeof(UINT) * BunIndice;
	BunIReader.CPUAccessFlags = 0;
	BunIReader.MiscFlags = 0;
	BunIReader.StructureByteStride = 0;
	BunIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC KnightVReader;
	ZeroMemory(&KnightVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	KnightVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	KnightVReader.ByteWidth = sizeof(Vertex_3D) * KnightVerts;
	KnightVReader.CPUAccessFlags = 0;
	KnightVReader.MiscFlags = 0;
	KnightVReader.StructureByteStride = 0;
	KnightVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC KnightIReader;
	ZeroMemory(&KnightIReader, sizeof(D3D11_BUFFER_DESC));

	KnightIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	KnightIReader.ByteWidth = sizeof(UINT) * KnightIndice;
	KnightIReader.CPUAccessFlags = 0;
	KnightIReader.MiscFlags = 0;
	KnightIReader.StructureByteStride = 0;
	KnightIReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Mesh Vertex and Index Buffers
	D3D11_BUFFER_DESC ShipVReader;
	ZeroMemory(&ShipVReader, sizeof(D3D11_BUFFER_DESC));

	// Setup Vertex Buffer
	ShipVReader.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	ShipVReader.ByteWidth = sizeof(Vertex_3D) * ShipVerts;
	ShipVReader.CPUAccessFlags = 0;
	ShipVReader.MiscFlags = 0;
	ShipVReader.StructureByteStride = 0;
	ShipVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Index Buffer
	D3D11_BUFFER_DESC ShipIReader;
	ZeroMemory(&ShipIReader, sizeof(D3D11_BUFFER_DESC));

	ShipIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ShipIReader.ByteWidth = sizeof(UINT) * ShipIndice;
	ShipIReader.CPUAccessFlags = 0;
	ShipIReader.MiscFlags = 0;
	ShipIReader.StructureByteStride = 0;
	ShipIReader.Usage = D3D11_USAGE_IMMUTABLE;

// Create Descriptors-----------------------------------------------------------------------------------------------------------------------------------//
	
// Create Buffers and Misc.-----------------------------------------------------------------------------------------------------------------------------//
	
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, &dx11, 1, D3D11_SDK_VERSION, &swapchain, &MySwap, &MyDev, 0, &MyCon);

	// Pyramid Buffers
	SubData.pSysMem = Tri;
	MyDev->CreateBuffer(&BDesc, &SubData, &VBuffer);
	//MyDev->CreateBuffer(&BDesc, nullptr, &CBuffer);

	// Skybox Buffers
	SubData.pSysMem = SkyVerts_3D;
	hr = MyDev->CreateBuffer(&OBJVReader, &SubData, &SkyVBuffer);

	SubData.pSysMem = SkyIndices;
	hr = MyDev->CreateBuffer(&OBJIReader, &SubData, &SkyIBuffer);

	// Planet 01 Buffers
	SubData.pSysMem = Planet01_3D;
	MyDev->CreateBuffer(&DeerVReader, &SubData, &Planet01VBuffer);

	SubData.pSysMem = Planet01Indices;
	MyDev->CreateBuffer(&DeerIReader, &SubData, &Planet01IBuffer);

	// Stonehenge Buffers
	SubData.pSysMem = StoneHenge_data;
	MyDev->CreateBuffer(&StoneVReader, &SubData, &StoneVBuffer);

	SubData.pSysMem = StoneHenge_indicies;
	MyDev->CreateBuffer(&StoneIReader, &SubData, &StoneIBuffer);

	// Planet 02 Buffers
	SubData.pSysMem = Planet02_3D;
	MyDev->CreateBuffer(&Planet02VReader, &SubData, &Planet02VBuffer);

	SubData.pSysMem = Planet02Indices;
	MyDev->CreateBuffer(&Planet02IReader, &SubData, &Planet02IBuffer);

	// Planet 03 Buffers
	SubData.pSysMem = Planet03_3D;
	MyDev->CreateBuffer(&Planet03VReader, &SubData, &Planet03VBuffer);

	SubData.pSysMem = Planet03Indices;
	MyDev->CreateBuffer(&Planet03IReader, &SubData, &Planet03IBuffer);

	// Moon Buffers
	SubData.pSysMem = Moon_3D;
	MyDev->CreateBuffer(&MoonVReader, &SubData, &MoonVBuffer);

	SubData.pSysMem = MoonIndices;
	MyDev->CreateBuffer(&MoonIReader, &SubData, &MoonIBuffer);

	// Ground Buffers
	SubData.pSysMem = Ground_3D;
	MyDev->CreateBuffer(&GroundVReader, &SubData, &GroundVBuffer);

	SubData.pSysMem = GroundIndices;
	MyDev->CreateBuffer(&GroundIReader, &SubData, &GroundIBuffer);

	// Ground Buffers
	SubData.pSysMem = Cave_3D;
	MyDev->CreateBuffer(&CaveVReader, &SubData, &CaveVBuffer);

	SubData.pSysMem = CaveIndices;
	MyDev->CreateBuffer(&CaveIReader, &SubData, &CaveIBuffer);

	// Holy Buffers
	SubData.pSysMem = Holy_3D;
	MyDev->CreateBuffer(&HolyVReader, &SubData, &HolyVBuffer);

	SubData.pSysMem = HolyIndices;
	MyDev->CreateBuffer(&HolyIReader, &SubData, &HolyIBuffer);

	// Bun Buffers
	SubData.pSysMem = Bun_3D;
	MyDev->CreateBuffer(&BunVReader, &SubData, &BunVBuffer);

	SubData.pSysMem = BunIndices;
	MyDev->CreateBuffer(&BunIReader, &SubData, &BunIBuffer);

	// Knight Buffers
	SubData.pSysMem = Knight_3D;
	MyDev->CreateBuffer(&KnightVReader, &SubData, &KnightVBuffer);

	SubData.pSysMem = KnightIndices;
	MyDev->CreateBuffer(&KnightIReader, &SubData, &KnightIBuffer);

	// Ship Buffers
	SubData.pSysMem = Ship_3D;
	MyDev->CreateBuffer(&ShipVReader, &SubData, &ShipVBuffer);

	SubData.pSysMem = ShipIndices;
	MyDev->CreateBuffer(&ShipIReader, &SubData, &ShipIBuffer);

	// Back Buffer
	ID3D11Resource* backbuffer;
	MySwap->GetBuffer(0, __uuidof(backbuffer), (void**)&backbuffer);
	MyDev->CreateRenderTargetView(backbuffer, nullptr, &MyTarget);
	backbuffer->Release();

	// ZBuffer
	MyDev->CreateTexture2D(&ZDesc, nullptr, &ZBuffer);
	MyDev->CreateDepthStencilView(ZBuffer, nullptr, &ZView);

	// Sampler
	ID3D11SamplerState* myLinearWrapSampler;
	MyDev->CreateSamplerState(&samplerDesc, &myLinearWrapSampler);
	MyCon->PSSetSamplers(0, 1, &myLinearWrapSampler);
	myLinearWrapSampler->Release();

	// Per Frame Constant Buffer
	MyDev->CreateBuffer(&cbbd, NULL, &cbPerFrameBuffer);

	// Constant Buffer
	MyDev->CreateBuffer(&CDesc, nullptr, &CBuffer);

// Create Buffers and Misc.-----------------------------------------------------------------------------------------------------------------------------//

// Create Vertex and Pixel Shaders----------------------------------------------------------------------------------------------------------------------//
	
	// Vertex Shaders
	MyDev->CreateVertexShader(VShader, sizeof(VShader), nullptr, &Vert_Shader);
	MyDev->CreateVertexShader(VMeshShader, sizeof(VMeshShader), nullptr, &VertexMShader);

	// Pixel Shaders
	MyDev->CreatePixelShader(PShader, sizeof(PShader), nullptr, &Pix_Shader);
	MyDev->CreatePixelShader(HolyShader, sizeof(HolyShader), nullptr, &Lit_Shader);
	MyDev->CreatePixelShader(BunShader, sizeof(BunShader), nullptr, &Bun_Shader);
	MyDev->CreatePixelShader(KnightShader, sizeof(KnightShader), nullptr, &Knight_Shader);
	MyDev->CreatePixelShader(P_Tex_Shader, sizeof(P_Tex_Shader), nullptr, &TexShader);
	MyDev->CreatePixelShader(SkyboxShader, sizeof(SkyboxShader), nullptr, &Sky_Shader);
	
// Create Vertex and Pixel Shaders----------------------------------------------------------------------------------------------------------------------//

// Set MVP Matrices-------------------------------------------------------------------------------------------------------------------------------------//

	// Set MVP
	//static float rota = 0;
	//rota += 0.001f;
	//XMMATRIX Temp = XMMatrixIdentity();
	//Temp = XMMatrixTranslation(0, 0, 0);
	//XMMATRIX Temp2 = XMMatrixRotationY(rota);
	//Temp = XMMatrixMultiply(Temp2, Temp);
	//XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// View
	XMMATRIX Temp = XMMatrixLookAtLH({ 0, 0, -200 }, { 0, 0, 0 }, { 0, 1, 0 });
	XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);

	// Projection
	Temp = XMMatrixPerspectiveFovLH(FOV, AspectRatio, 0.1f, 1000);
	XMStoreFloat4x4(&MyMatricies.PMatrix, Temp);

// Set MVP Matrices-------------------------------------------------------------------------------------------------------------------------------------//


// Create Textures--------------------------------------------------------------------------------------------------------------------------------------//
	
	CreateDDSTextureFromFile(MyDev, L"Assets/Space.dds", (ID3D11Resource**)&SkyTexture, &SkyView);
	CreateDDSTextureFromFile(MyDev, L"Assets/SunsetSkybox.dds", (ID3D11Resource**)&Sky2Texture, &Sky2View);
	CreateDDSTextureFromFile(MyDev, L"Assets/StoneHenge.dds", (ID3D11Resource**)&StoneTexture, &StoneView);
	CreateDDSTextureFromFile(MyDev, L"Assets/fire_planet.dds", (ID3D11Resource**)&Planet01Texture, &Planet01View);
	CreateDDSTextureFromFile(MyDev, L"Assets/uhfplanet.dds", (ID3D11Resource**)&Planet02Texture, &Planet02View);
	CreateDDSTextureFromFile(MyDev, L"Assets/bunplanet.dds", (ID3D11Resource**)&Planet03Texture, &Planet03View);
	CreateDDSTextureFromFile(MyDev, L"Assets/moon_Diffuse.dds", (ID3D11Resource**)&MoonTexture, &MoonView);
	CreateDDSTextureFromFile(MyDev, L"Assets/AlienAOE_D.dds", (ID3D11Resource**)&ShipTexture, &ShipView);

// Create Textures--------------------------------------------------------------------------------------------------------------------------------------//

//Create Layouts----------------------------------------------------------------------------------------------------------------------------------------//

	D3D11_INPUT_ELEMENT_DESC IEDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	MyDev->CreateInputLayout(IEDesc, 2, VShader, sizeof(VShader), &VLayout);

	// Make matching input layout for vertex mesh
	D3D11_INPUT_ELEMENT_DESC MeshDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	MyDev->CreateInputLayout(MeshDesc, 3, VMeshShader, sizeof(VMeshShader), &VMeshLayout);

//Create Layouts----------------------------------------------------------------------------------------------------------------------------------------//
}