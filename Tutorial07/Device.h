#pragma once
#include <d3d11.h>

class Device
{
public:
	Device();
	~Device();
	
	HRESULT CCreateRenderTargetView(
		ID3D11Resource* pResource,
		const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
		ID3D11RenderTargetView** ppRTView
	);

	HRESULT CCreateTexture2D(
		const D3D11_TEXTURE2D_DESC* pDesc,
		const D3D11_SUBRESOURCE_DATA* pInitialData,
		ID3D11Texture2D** ppTexture2D
	);

	HRESULT CCreateDepthStencilView(
		ID3D11Resource* pResource,
		const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
		ID3D11DepthStencilView** ppDepthStencilView
	);

	HRESULT CCreateVertexShader(
		const void* pShaderBytecode,
		SIZE_T             BytecodeLength,
		ID3D11ClassLinkage* pClassLinkage,
		ID3D11VertexShader** ppVertexShader
	);

	HRESULT CCreateInputLayout(
		const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
		UINT                           NumElements,
		const void* pShaderBytecodeWithInputSignature,
		SIZE_T                         BytecodeLength,
		ID3D11InputLayout** ppInputLayout
	);

	HRESULT CCreatePixelShader(
		const void* pShaderBytecode,
		SIZE_T             BytecodeLength,
		ID3D11ClassLinkage* pClassLinkage,
		ID3D11PixelShader** ppPixelShader
	);

	HRESULT CCreateBuffer(
		const D3D11_BUFFER_DESC* pDesc,
		const D3D11_SUBRESOURCE_DATA* pInitialData,
		ID3D11Buffer** ppBuffer
	);

	HRESULT CCreateSamplerState(
		const D3D11_SAMPLER_DESC* pSamplerDesc,
		ID3D11SamplerState** ppSamplerState
	);

private:
	ID3D11Device* CDevice = NULL;
};

