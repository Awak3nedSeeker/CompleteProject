#pragma once
#include "Defines.h"

void DrawMesh()
{
	constbuffPerFrame.light = light;
	MyCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
	MyCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);

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
	MyCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



	if (OnScreen1 == true)
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

		// Planet 1---------------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Planet01_strides[] = { sizeof(Vertex_3D) };
		UINT Planet01_offsets[] = { 0 };
		ID3D11Buffer* Planet01Buff[] = { Planet01VBuffer };
		MyCon->IASetVertexBuffers(0, 1, Planet01Buff, Planet01_strides, Planet01_offsets);
		MyCon->IASetIndexBuffer(Planet01IBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix

		static float rota = 0;
		rota += 0.0005f;
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(0, 0, 0);
		XMMATRIX Temp2 = XMMatrixRotationY(rota);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Upload those matrices to the video card
		// Create and update constant buffer (move variables from C++ toi shaders
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
		MyCon->Unmap(CBuffer, 0);

		ID3D11Buffer* TempConst[] = { CBuffer };
		MyCon->VSSetConstantBuffers(0, 1, TempConst);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textView[] = { Planet01View };
		MyCon->PSSetShaderResources(0, 1, textView);

		MyCon->DrawIndexed(Planet01Indice, 0, 0);

		// Planet 1--------------------------------------------------------------------------------------------------------------------------//

		// Planet 2---------------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Planet02_strides[] = { sizeof(Vertex_3D) };
		UINT Planet02_offsets[] = { 0 };
		ID3D11Buffer* Planet02Buff[] = { Planet02VBuffer };
		MyCon->IASetVertexBuffers(0, 1, Planet02Buff, Planet02_strides, Planet02_offsets);
		MyCon->IASetIndexBuffer(Planet02IBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix

		static float rotation = 0;
		rotation += 0.001f;
		XMMATRIX TempPlanet02 = XMMatrixIdentity();
		TempPlanet02 = XMMatrixTranslation(375, 0, 0);
		XMMATRIX Temp2Planet02 = XMMatrixRotationY(rotation);
		TempPlanet02 = XMMatrixMultiply(TempPlanet02, Temp2Planet02);
		XMStoreFloat4x4(&MyMatricies.WMatrix, TempPlanet02);

		Orbit = TempPlanet02;

		// Upload those matrices to the video card
		// Create and update constant buffer (move variables from C++ toi shaders
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
		MyCon->Unmap(CBuffer, 0);

		ID3D11Buffer* TempConstant[] = { CBuffer };
		MyCon->VSSetConstantBuffers(0, 1, TempConstant);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textureView[] = { Planet02View };
		MyCon->PSSetShaderResources(0, 1, textureView);

		MyCon->DrawIndexed(Planet02Indice, 0, 0);

		// Planet 2--------------------------------------------------------------------------------------------------------------------------//

		// Planet 3---------------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Planet03_strides[] = { sizeof(Vertex_3D) };
		UINT Planet03_offsets[] = { 0 };
		ID3D11Buffer* Planet03Buff[] = { Planet03VBuffer };
		MyCon->IASetVertexBuffers(0, 1, Planet03Buff, Planet03_strides, Planet03_offsets);
		MyCon->IASetIndexBuffer(Planet03IBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix

		static float rotatio = 0;
		rotatio += 0.005f;
		XMMATRIX TempPlanet03 = XMMatrixIdentity();
		TempPlanet03 = XMMatrixTranslation(200, 0, 0);
		XMMATRIX Temp2Planet03 = XMMatrixRotationY(-rotatio);
		TempPlanet03 = XMMatrixMultiply(TempPlanet03, Temp2Planet03);
		XMStoreFloat4x4(&MyMatricies.WMatrix, TempPlanet03);

		// Upload those matrices to the video card
		// Create and update constant buffer (move variables from C++ toi shaders
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
		MyCon->Unmap(CBuffer, 0);

		ID3D11Buffer* TempConstan[] = { CBuffer };
		MyCon->VSSetConstantBuffers(0, 1, TempConstan);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textureVie[] = { Planet03View };
		MyCon->PSSetShaderResources(0, 1, textureVie);

		MyCon->DrawIndexed(Planet03Indice, 0, 0);

		// Planet 3--------------------------------------------------------------------------------------------------------------------------//

		// Moon---------------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Moon_strides[] = { sizeof(Vertex_3D) };
		UINT Moon_offsets[] = { 0 };
		ID3D11Buffer* MoonBuff[] = { MoonVBuffer };
		MyCon->IASetVertexBuffers(0, 1, MoonBuff, Moon_strides, Moon_offsets);
		MyCon->IASetIndexBuffer(MoonIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix

		static float rot = 0;
		rot += 0.001f;
		XMMATRIX Tempmoon = XMMatrixIdentity();
		Tempmoon = XMMatrixTranslation(100, 75, 0);
		XMMATRIX Temp2moon = XMMatrixRotationY(-rot);
		Tempmoon = XMMatrixMultiply(Tempmoon, Temp2moon);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Tempmoon);

		// Upload those matrices to the video card
		// Create and update constant buffer (move variables from C++ toi shaders
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
		MyCon->Unmap(CBuffer, 0);

		ID3D11Buffer* TempConsta[] = { CBuffer };
		MyCon->VSSetConstantBuffers(0, 1, TempConsta);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textureV[] = { MoonView };
		MyCon->PSSetShaderResources(0, 1, textureV);

		MyCon->DrawIndexed(MoonIndice, 0, 0);

		// Moon--------------------------------------------------------------------------------------------------------------------------//

		// Ship--------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Ship_strides[] = { sizeof(Vertex_3D) };
		UINT Ship_offsets[] = { 0 };
		ID3D11Buffer* ShipBuff[] = { ShipVBuffer };
		MyCon->IASetVertexBuffers(0, 1, ShipBuff, Ship_strides, Ship_offsets);
		MyCon->IASetIndexBuffer(ShipIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(0, -10, -160);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textViewS[] = { ShipView };
		MyCon->PSSetShaderResources(0, 1, textViewS);

		MyCon->DrawIndexed(ShipIndice, 0, 0);

		// Ship--------------------------------------------------------------------------------------------------------------------//
	}

	if (OnScreen2 == true)
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

		ID3D11ShaderResourceView* texView[] = { Sky2View };
		MyCon->PSSetShaderResources(0, 1, texView);

		MyCon->DrawIndexed(SkyIndice, 0, 0);

		// Skybox-------------------------------------------------------------------------------------------------------------------------//

		// Stonehenge--------------------------------------------------------------------------------------------------------------------//

		// Used in early stages------------------------------------------------------

		// Set Pipeline
		UINT Stone_strides[] = { sizeof(Vertex_3D) };
		UINT Stone_offsets[] = { 0 };
		ID3D11Buffer* StoneBuff[] = { GroundVBuffer };
		MyCon->IASetVertexBuffers(0, 1, StoneBuff, Stone_strides, Stone_offsets);
		MyCon->IASetIndexBuffer(GroundIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(0, -10, -160);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(TexShader, 0, 0);

		ID3D11ShaderResourceView* textView[] = { StoneView };
		MyCon->PSSetShaderResources(0, 1, textView);

		MyCon->DrawIndexed(GroundIndice, 0, 0);

		// Stonehenge--------------------------------------------------------------------------------------------------------------------//

		// Cave--------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Cave_strides[] = { sizeof(Vertex_3D) };
		UINT Cave_offsets[] = { 0 };
		ID3D11Buffer* CaveBuff[] = { CaveVBuffer };
		MyCon->IASetVertexBuffers(0, 1, CaveBuff, Cave_strides, Cave_offsets);
		MyCon->IASetIndexBuffer(CaveIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(22, -10, -170);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);
		XMMATRIX Temp2 = XMMatrixRotationY(-120);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(Pix_Shader, 0, 0);

		MyCon->DrawIndexed(CaveIndice, 0, 0);

		// Cave--------------------------------------------------------------------------------------------------------------------//

		// Holy--------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Holy_strides[] = { sizeof(Vertex_3D) };
		UINT Holy_offsets[] = { 0 };
		ID3D11Buffer* HolyBuff[] = { HolyVBuffer };
		MyCon->IASetVertexBuffers(0, 1, HolyBuff, Holy_strides, Holy_offsets);
		MyCon->IASetIndexBuffer(HolyIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(5, 0, -170);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);
		Temp2 = XMMatrixRotationZ(45);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(Lit_Shader, 0, 0);

		MyCon->DrawIndexed(HolyIndice, 0, 0);

		// Holy--------------------------------------------------------------------------------------------------------------------//

		// Bun--------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Bun_strides[] = { sizeof(Vertex_3D) };
		UINT Bun_offsets[] = { 0 };
		ID3D11Buffer* BunBuff[] = { BunVBuffer };
		MyCon->IASetVertexBuffers(0, 1, BunBuff, Bun_strides, Bun_offsets);
		MyCon->IASetIndexBuffer(BunIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(15, -10, -170);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);
		Temp2 = XMMatrixRotationY(-90);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(Bun_Shader, 0, 0);

		MyCon->DrawIndexed(BunIndice, 0, 0);

		// Bun--------------------------------------------------------------------------------------------------------------------//

		// knght--------------------------------------------------------------------------------------------------------------------//

		// Set Pipeline
		UINT Knight_strides[] = { sizeof(Vertex_3D) };
		UINT Knight_offsets[] = { 0 };
		ID3D11Buffer* KnightBuff[] = { KnightVBuffer };
		MyCon->IASetVertexBuffers(0, 1, KnightBuff, Knight_strides, Knight_offsets);
		MyCon->IASetIndexBuffer(KnightIBuffer, DXGI_FORMAT_R32_UINT, 0);
		MyCon->VSSetShader(VertexMShader, 0, 0);
		MyCon->IASetInputLayout(VMeshLayout);

		// Modify World Matrix
		Temp = XMMatrixIdentity();
		Temp = XMMatrixTranslation(-8, -9, -170);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);
		Temp2 = XMMatrixRotationY(-16.5f);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

		// Send it to the card
		MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
		*((WVP*)(GPUBuffer.pData)) = MyMatricies;
		MyCon->Unmap(CBuffer, 0);

		MyCon->PSSetShader(Knight_Shader, 0, 0);

		MyCon->DrawIndexed(KnightIndice, 0, 0);

		// Knight--------------------------------------------------------------------------------------------------------------------//
	}

	if (GetAsyncKeyState('1'))
	{
		OnScreen1 = true;
		OnScreen2 = false;

		MyCon->ClearRenderTargetView(MyTarget, color);
	}

	if (GetAsyncKeyState('2'))
	{
		OnScreen1 = false;
		OnScreen2 = true;

		MyCon->ClearRenderTargetView(MyTarget, color);
	}

	MySwap->Present(0, 0);
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
		Temp2 = XMMatrixTranslation(0, 0, 0.1f);
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
		Temp2 = XMMatrixTranslation(0, 0, -0.1f);
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
		Temp2 = XMMatrixTranslation(-0.1f, 0, 0);
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
		Temp2 = XMMatrixTranslation(0.1f, 0, 0);
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
		Temp2 = XMMatrixTranslation(0, -0.1f, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		XMMATRIX Temp = XMLoadFloat4x4(&MyMatricies.VMatrix);
		XMMATRIX Temp2 = XMMatrixIdentity();
		Temp2 = XMMatrixTranslation(0, 0.1f, 0);
		Temp = XMMatrixMultiply(Temp2, Temp);
		XMStoreFloat4x4(&MyMatricies.VMatrix, Temp);
	}

	// Reset

	if (GetAsyncKeyState('R'))
	{
		XMMATRIX Temp = XMMatrixLookAtLH({ 0, 0, -200 }, { 0, 0, 0 }, { 0, 1, 0 });
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
	Bun_Shader->Release();
	Lit_Shader->Release();
	Knight_Shader->Release();
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
	Planet01VBuffer->Release();
	Planet01IBuffer->Release();
	Planet02VBuffer->Release();
	Planet02IBuffer->Release();
	Planet03VBuffer->Release();
	Planet03IBuffer->Release();
	MoonVBuffer->Release();
	MoonIBuffer->Release();
	GroundVBuffer->Release();
	GroundIBuffer->Release();
	CaveVBuffer->Release();
	CaveIBuffer->Release();
	HolyVBuffer->Release();
	HolyIBuffer->Release();
	BunVBuffer->Release();
	BunIBuffer->Release();
	KnightVBuffer->Release();
	KnightIBuffer->Release();
	ShipVBuffer->Release();
	ShipIBuffer->Release();
	StoneVBuffer->Release();
	StoneIBuffer->Release();

	// Arrays
	delete[] SkyIndices;
	delete[] SkyVerts_3D;
	delete[] Planet01_3D;
	delete[] Planet02_3D;
	delete[] Planet03_3D;
	delete[] Ground_3D;
	delete[] Cave_3D;
	delete[] Holy_3D;
	delete[] Bun_3D;
	delete[] Knight_3D;
	delete[] Ship_3D;
	delete[] Planet01Indices;

	// System
	SkyView->Release();
	SkyTexture->Release();
	Sky2View->Release();
	Sky2Texture->Release();
	Planet01View->Release();
	Planet01Texture->Release();
	Planet02View->Release();
	Planet02Texture->Release();
	Planet03View->Release();
	Planet03Texture->Release();
	MoonView->Release();
	MoonTexture->Release();
	StoneView->Release();
	StoneTexture->Release();
	ShipView->Release();
	ShipTexture->Release();
	MyCon->Release();
	ZView->Release();
	MySwap->Release();
	MyTarget->Release();
	MyDev->Release();
}

//void Draw()
//{
//	//rendering here
//	float color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	MyCon->ClearRenderTargetView(MyTarget, color);
//
//	MyCon->ClearDepthStencilView(ZView, D3D11_CLEAR_DEPTH, 1, 0);
//
//	// Setup the pipeline
//	// Output merger
//	ID3D11RenderTargetView* temptarget[] = { MyTarget };
//	MyCon->OMSetRenderTargets(1, temptarget, ZView);
//
//	// Rasterizer
//	MyCon->RSSetViewports(1, &MyView);
//	//// Input Assembler
//	//UINT strides[] = { sizeof(Vertex) };
//	//UINT offsets[] = { 0 };
//	//ID3D11Buffer* TempBuff[] = { VBuffer };
//	//MyCon->IASetVertexBuffers(0, 1, TempBuff, strides, offsets);
//	MyCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	//MyCon->IASetInputLayout(VLayout);
//
//	//// Vertex Shader Stage
//	//MyCon->VSSetShader(Vert_Shader, 0, 0);
//
//	//// Pixel Shader Stage
//	//MyCon->PSSetShader(Pix_Shader, 0, 0);
//
//	//static float rota = 0;
//	//rota += 0.001f;
//	//XMMATRIX Temp = XMMatrixIdentity();
//	//Temp = XMMatrixTranslation(0, 10, 0);
//	//XMMATRIX Temp2 = XMMatrixRotationY(rota);
//	//Temp = XMMatrixMultiply(Temp2, Temp);
//	//XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);
//
//	//// Upload those matrices to the video card
//	//// Create and update constant buffer (move variables from C++ toi shaders
//	//MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
//	//*((WVP*)(GPUBuffer.pData)) = MyMatricies;
//	//// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
//	//MyCon->Unmap(CBuffer, 0);
//
//	//// Apply matrix math in vertex shader
//	//// connect constant buffer to the pipeline
//	//// Remember by defualt HLSL matricies are COLUMN MAJOR
//	//ID3D11Buffer* TempConst[] = { CBuffer };
//	//MyCon->VSSetConstantBuffers(0, 1, TempConst);
///
//	//Draw
//	//MyCon->Draw(NumVerts, 0);
//
//	//MySwap->Present(0, 0);
//}

// Stonehenge--------------------------------------------------------------------------------------------------------------------//

// Used in early stages------------------------------------------------------

//// Set Pipeline
//UINT Stone_strides[] = { sizeof(Vertex_3D) };
//UINT Stone_offsets[] = { 0 };
//ID3D11Buffer* StoneBuff[] = { StoneVBuffer };
//MyCon->IASetVertexBuffers(0, 1, StoneBuff, Stone_strides, Stone_offsets);
//MyCon->IASetIndexBuffer(StoneIBuffer, DXGI_FORMAT_R32_UINT, 0);
//MyCon->VSSetShader(VertexMShader, 0, 0);
//MyCon->IASetInputLayout(VMeshLayout);

//// Modify World Matrix
//Temp = XMMatrixIdentity();
//Temp = XMMatrixTranslation(0, 0, 0);
//XMStoreFloat4x4(&MyMatricies.WMatrix, Temp);

//// Send it to the card
//MyCon->Map(CBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &GPUBuffer);
//*((WVP*)(GPUBuffer.pData)) = MyMatricies;

//// memcpy(GPUBuffer.pData, &WMatrix, sizeof(XMFLOAT4X4));
//MyCon->Unmap(CBuffer, 0);

//MyCon->PSSetShader(TexShader, 0, 0);

//ID3D11ShaderResourceView* textView[] = { StoneView };
//MyCon->PSSetShaderResources(0, 1, textView);

//MyCon->DrawIndexed(2532, 0, 0);

// Stonehenge--------------------------------------------------------------------------------------------------------------------//

// Point Light Movement

//if (Lend == false)
//{
//	light.pos.x += 0.01f;
//}

//if (light.pos.x >= 10)
//{
//	Lend = true;
//}

//if (Lend == true)
//{
//	light.pos.x -= 0.01f;
//}

//if (light.pos.x <= -10)
//{
//	Lend = false;
//}

// Directional light Movement

//if (DLend == false)
//{
//	light.dir.x += 0.01f;
//}

//if (light.dir.x >= 10)
//{
//	DLend = true;
//}

//if (DLend == true)
//{
//	light.dir.x -= 0.01f;
//}

//if (light.dir.x <= -10)
//{
//	DLend = false;
//}

// Spotlight Movement

//if (SLPend == false)
//{
//	light.Spos.x += 0.01f;
//}

//if (light.Spos.x >= 15) 
//{
//	SLPend = true;
//}

//if (SLPend == true)
//{
//	light.Spos.x -= 0.01f;
//}

//if (light.Spos.x <= -15)
//{
//	SLPend = false;
//}

// Spot light Direction

//if (SLDend == false)
//{
//	light.Sdir.y += 0.001f;
//	light.Sdir.z += 0.003f;
//}

//if (light.Sdir.z >= 1)
//{
//	SLDend = true;
//}

//if (SLDend == true)
//{
//	light.Sdir.y -= 0.001f;
//	light.Sdir.z -= 0.003f;
//}
//

//if (light.Sdir.z <= -1)
//{
//	SLDend = false;
//}