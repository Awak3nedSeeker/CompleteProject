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

	// Deer Loader
	Mesh Deer = ModelLoader("Assets/deer.obj", 0.01f, vertexlist, indices);
	DeerVerts_3D = Deer.Vert;
	DeerIndices = Deer.indi;
	DeerVerts = numVerts;
	DeerIndice = numIndices;

	// Light Info
	light.dir = XMFLOAT3(0.25f, -0.5f, -1.0f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(0.3f, 0.3f, 0.4f, 1.0f);
	light.pos = XMFLOAT3(0.0f, 2.0f, -5.0f);
	light.range = 100.0f;
	light.att = XMFLOAT3(0.0f, 0.2f, 0.0f);
	
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
	DeerVReader.ByteWidth = sizeof(Vertex_3D) * DeerVerts;
	DeerVReader.CPUAccessFlags = 0;
	DeerVReader.MiscFlags = 0;
	DeerVReader.StructureByteStride = 0;
	DeerVReader.Usage = D3D11_USAGE_IMMUTABLE;

	// Deer Index Buffer
	D3D11_BUFFER_DESC DeerIReader;
	ZeroMemory(&DeerIReader, sizeof(D3D11_BUFFER_DESC));

	DeerIReader.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DeerIReader.ByteWidth = sizeof(UINT) * DeerIndice;
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

	// Deer Buffers
	SubData.pSysMem = DeerVerts_3D;
	MyDev->CreateBuffer(&DeerVReader, &SubData, &DeerVBuffer);

	SubData.pSysMem = DeerIndices;
	MyDev->CreateBuffer(&DeerIReader, &SubData, &DeerIBuffer);

	// Stonehenge Buffers
	SubData.pSysMem = StoneHenge_data;
	MyDev->CreateBuffer(&StoneVReader, &SubData, &StoneVBuffer);

	SubData.pSysMem = StoneHenge_indicies;
	MyDev->CreateBuffer(&StoneIReader, &SubData, &StoneIBuffer);

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
	MyDev->CreatePixelShader(P_Tex_Shader, sizeof(P_Tex_Shader), nullptr, &TexShader);
	MyDev->CreatePixelShader(SkyboxShader, sizeof(SkyboxShader), nullptr, &Sky_Shader);
	
// Create Vertex and Pixel Shaders----------------------------------------------------------------------------------------------------------------------//

// Set MVP Matrices-------------------------------------------------------------------------------------------------------------------------------------//

	// Set MVP
	static float rota = 0;
	rota += 0.001f;
	XMMATRIX Temp = XMMatrixIdentity();
	Temp = XMMatrixTranslation(0, 0, 0);
	XMMATRIX Temp2 = XMMatrixRotationY(rota);
	Temp = XMMatrixMultiply(Temp2, Temp);
	XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// View
	Temp = XMMatrixLookAtLH({ 0, 0, -32 }, { 0, 0, 0 }, { 0, 1, 0 });
	XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);

	// Projection
	Temp = XMMatrixPerspectiveFovLH(FOV, AspectRatio, 0.1f, 1000);
	XMStoreFloat4x4(&MyMatricies.PMatrix, Temp);

// Set MVP Matrices-------------------------------------------------------------------------------------------------------------------------------------//


// Create Textures--------------------------------------------------------------------------------------------------------------------------------------//
	
	CreateDDSTextureFromFile(MyDev, L"Assets/SkyboxOcean.dds", (ID3D11Resource**)&SkyTexture, &SkyView);
	CreateDDSTextureFromFile(MyDev, L"Assets/StoneHenge.dds", (ID3D11Resource**)&StoneTexture, &StoneView);
	
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