#pragma once
#include "Defines.h"

void Draw()
{
	//rendering here
	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	MyCon->ClearRenderTargetView(MyTarget, color);

	MyCon->ClearDepthStencilView(ZView, D3D11_CLEAR_DEPTH, 1, 0);

	// Setup the pipeline
	// Output merger
	ID3D11RenderTargetView* temptarget[] = { MyTarget };
	MyCon->OMSetRenderTargets(1, temptarget, ZView);
	// Rasterizer
	MyCon->RSSetViewports(1, &MyView);
	// Input Assembler
	UINT strides[] = { sizeof(Vertex) };
	UINT offsets[] = { 0 };
	ID3D11Buffer* TempBuff[] = { VBuffer };
	MyCon->IASetVertexBuffers(0, 1, TempBuff, strides, offsets);
	MyCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	MyCon->IASetInputLayout(VLayout);

	// Vertex Shader Stage
	MyCon->VSSetShader(Vert_Shader, 0, 0);

	// Pixel Shader Stage
	MyCon->PSSetShader(Pix_Shader, 0, 0);

	static float rota = 0;
	rota += 0.001f;
	XMMATRIX Temp = XMMatrixIdentity();
	Temp = XMMatrixTranslation(0, 10, 0);
	XMMATRIX Temp2 = XMMatrixRotationY(rota);
	Temp = XMMatrixMultiply(Temp2, Temp);
	XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// Upload those matrices to the video card
	// Create and update constant buffer (move variables from C++ toi shaders
	MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
	*((WVP*)(GPUBuffer.pData)) = MyMatricies;
	// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
	MyCon->Unmap(CBuffer, 0);

	// Apply matrix math in vertex shader
	// connect constant buffer to the pipeline
	// Remember by defualt HLSL matricies are COLUMN MAJOR
	ID3D11Buffer* TempConst[] = { CBuffer };
	MyCon->VSSetConstantBuffers(0, 1, TempConst);

	//Draw
	MyCon->Draw(NumVerts, 0);

	//MySwap->Present(0, 0);
}

void DrawMesh()
{
	//Skybox--------------------------------------------------------------------------------------------------------------------------//

	// Set Pipeline
	UINT Mesh_strides[] = { sizeof(Vertex_3D) };
	UINT Mesh_offsets[] = { 0 };
	ID3D11Buffer* MeshBuff[] = { SkyVBuffer };
	MyCon->IASetVertexBuffers(0, 1, MeshBuff, Mesh_strides, Mesh_offsets);
	MyCon->IASetIndexBuffer(SkyIBuffer, DXGI_FORMAT_R32_UINT, 0);
	MyCon->VSSetShader(VertexMShader, 0, 0);
	MyCon->IASetInputLayout(VMeshLayout);

	// Modify World Matrix
	XMMATRIX Temp = XMMatrixIdentity();
	Temp = XMMatrixTranslation(0, 0, 0);
	XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// Send it to the card
	MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
	*((WVP*)(GPUBuffer.pData)) = MyMatricies;

	// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
	MyCon->Unmap(CBuffer, 0);

	//MyCon->PSSetShader(TexShader, 0, 0);
	MyCon->PSSetShader(Sky_Shader, 0, 0);

	ID3D11ShaderResourceView* texView[] = { SkyView };
	MyCon->PSSetShaderResources(0, 1, texView);

	MyCon->DrawIndexed(SkyIndice, 0, 0);

	// Skybox-------------------------------------------------------------------------------------------------------------------------//

	// Deer---------------------------------------------------------------------------------------------------------------------------//

	// Set Pipeline
	UINT Deer_strides[] = { sizeof(Vertex_3D) };
	UINT Deer_offsets[] = { 0 };
	ID3D11Buffer* DeerBuff[] = { DeerVBuffer };
	MyCon->IASetVertexBuffers(0, 1, DeerBuff, Deer_strides, Deer_offsets);
	MyCon->IASetIndexBuffer(DeerIBuffer, DXGI_FORMAT_R32_UINT, 0);
	MyCon->VSSetShader(VertexMShader, 0, 0);
	MyCon->IASetInputLayout(VMeshLayout);

	// Modify World Matrix
	Temp = XMMatrixIdentity();
	Temp = XMMatrixTranslation(0, 0, 0);
	XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// Send it to the card
	MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
	*((WVP*)(GPUBuffer.pData)) = MyMatricies;

	// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
	MyCon->Unmap(CBuffer, 0);

	MyCon->PSSetShader(Pix_Shader, 0, 0);

	MyCon->DrawIndexed(DeerIndice, 0, 0);

	// Deer--------------------------------------------------------------------------------------------------------------------------//

	// Stonehenge--------------------------------------------------------------------------------------------------------------------//

	constbuffPerFrame.light = light;
	MyCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
	MyCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

	// Set Pipeline
	UINT Stone_strides[] = { sizeof(Vertex_3D) };
	UINT Stone_offsets[] = { 0 };
	ID3D11Buffer* StoneBuff[] = { StoneVBuffer };
	MyCon->IASetVertexBuffers(0, 1, StoneBuff, Stone_strides, Stone_offsets);
	MyCon->IASetIndexBuffer(StoneIBuffer, DXGI_FORMAT_R32_UINT, 0);
	MyCon->VSSetShader(VertexMShader, 0, 0);
	MyCon->IASetInputLayout(VMeshLayout);

	// Modify World Matrix
	Temp = XMMatrixIdentity();
	Temp = XMMatrixTranslation(0, 0, 0);
	XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

	// Send it to the card
	MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
	*((WVP*)(GPUBuffer.pData)) = MyMatricies;

	// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
	MyCon->Unmap(CBuffer, 0);

	MyCon->PSSetShader(TexShader, 0, 0);

	ID3D11ShaderResourceView* textView[] = { StoneView };
	MyCon->PSSetShaderResources(0, 1, textView);

	MyCon->DrawIndexed(2532, 0, 0);

	// Stonehenge--------------------------------------------------------------------------------------------------------------------//

	// Point Light Movement

	if (Lend == false)
	{
		light.pos.x += 0.01f;
	}

	if (light.pos.x >= 10)
	{
		Lend = true;
	}

	if (Lend == true)
	{
		light.pos.x -= 0.01f;
	}

	if (light.pos.x <= -10)
	{
		Lend = false;
	}

	// Directional light Movement

	if (DLend == false)
	{
		light.dir.x += 0.01f;
	}

	if (light.dir.x >= 10)
	{
		DLend = true;
	}

	if (DLend == true)
	{
		light.dir.x -= 0.01f;
	}

	if (light.dir.x <= -10)
	{
		DLend = false;
	}

	// Spotlight Movement

	if (SLPend == false)
	{
		light.Spos.x += 0.01f;
	}

	if (light.Spos.x >= 15) 
	{
		SLPend = true;
	}

	if (SLPend == true)
	{
		light.Spos.x -= 0.01f;
	}

	if (light.Spos.x <= -15)
	{
		SLPend = false;
	}

	// Spot light Direction

	if (SLDend == false)
	{
		//light.Sdir.y += 0.001f;
		light.Sdir.z += 0.003f;
	}

	if (light.Sdir.z >= 1)
	{
		SLDend = true;
	}

	if (SLDend == true)
	{
		//light.Sdir.y -= 0.001f;
		light.Sdir.z -= 0.003f;
	}
	

	if (light.Sdir.z <= -1)
	{
		SLDend = false;
	}
}

void Movement()
{
	// Movement

	if (GetAsyncKeyState('W'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0, 0, 0.01f);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('S'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0, 0, -0.01f);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('A'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(-0.01f, 0, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('D'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0.01f, 0, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	// Rotation

	if (GetAsyncKeyState('I'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixRotationX(-0.001f);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('K'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixRotationX(0.001f);
		Temp = XMMatrixMultiply(Temp2, Temp);

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('J'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);


		XMVECTOR Pos = Temp.r[3];
		Temp.r[3] = XMVectorSet( 0, 0, 0, 1 );

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixRotationY(-0.001f);
		Temp = XMMatrixMultiply(Temp, Temp2);

		Temp.r[3] = Pos;

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState('L'))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMVECTOR Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);

		XMVECTOR Pos = Temp.r[3];
		Temp.r[3] = XMVectorSet(0, 0, 0, 1);

		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixRotationY(0.001f);
		Temp = XMMatrixMultiply(Temp, Temp2);

		Temp.r[3] = Pos;

		Invert = XMMatrixDeterminant(Temp);
		Temp = XMMatrixInverse(&Invert, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	// Up and Down

	if (GetAsyncKeyState(VK_SPACE))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0, -0.01f, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0, 0.01f, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	// Reset

	if (GetAsyncKeyState('R'))
	{
		XMMATRIX Temp = XMMatrixLookAtLH({ 0, 0, -32 }, { 0, 0, 0 }, { 0, 1, 0 });
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
		FOV = 3.14f / 2.0f;
		FPlane = 100000.0f;
		NPlane = 0.1f;
	}

	// Zoom

	if (GetAsyncKeyState(VK_UP))
	{
		FOV -= 0.001f;

		if (FOV < 0.1f)
		{
			FOV = 0.1f;
		}
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		FOV += 0.001f;

		if (FOV > 2.25f)
		{
			FOV = 2.25f;
		}
	}

	// Adjust Near & Far Plane

	if (GetAsyncKeyState('Z'))
	{
		NPlane += 1.0f;

		if (NPlane >= FPlane)
		{
			NPlane = FPlane - 0.1f;
		}
	}

	if (GetAsyncKeyState('X'))
	{
		NPlane -= 1.0f;

		if (NPlane <= 0.2f)
		{
			NPlane = 0.11f;
		}
	}

	if (GetAsyncKeyState('N'))
	{
		FPlane += 10.0f;
	}

	if (GetAsyncKeyState('M'))
	{
		FPlane -= 10.0f;

		if (FPlane <= NPlane)
		{
			FPlane = NPlane + 0.1f;
		}
	}

	XMMATRIX Temp = XMMatrixPerspectiveFovLH(FOV, AspectRatio, NPlane, FPlane);
	XMStoreFloat4x4(&MyMatricies.PMatrix, Temp);
}

void Cleanup()
{
	// Shaders
	Vert_Shader->Release();
	Pix_Shader->Release();
	VertexMShader->Release();
	TexShader->Release();
	Sky_Shader->Release();

	// Layout
	VLayout->Release();
	VMeshLayout->Release();

	// Buffers
	VBuffer->Release();
	CBuffer->Release();
	ZBuffer->Release();
	cbPerFrameBuffer->Release();
	SkyVBuffer->Release();
	SkyIBuffer->Release();
	DeerVBuffer->Release();
	DeerIBuffer->Release();
	StoneVBuffer->Release();
	StoneIBuffer->Release();

	// Arrays
	delete[] SkyIndices;
	delete[] SkyVerts_3D;
	delete[] DeerVerts_3D;
	delete[] DeerIndices;

	// System
	SkyView->Release();
	SkyTexture->Release();
	StoneView->Release();
	StoneTexture->Release();
	MyCon->Release();
	ZView->Release();
	MySwap->Release();
	MyTarget->Release();
	MyDev->Release();
}