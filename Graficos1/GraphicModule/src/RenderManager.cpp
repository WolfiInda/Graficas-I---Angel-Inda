#include "RenderManager.h"

RenderManager::RenderManager()
{
	Cg_pd3dDevice_DX11 = NULL;
	Cg_pImmediateContext_DX11 = NULL;
	Cg_pSwapChain_DX11 = NULL;
}

RenderManager::~RenderManager()
{
	if (NULL != Cg_pd3dDevice_DX11) {
		delete Cg_pd3dDevice_DX11;
		Cg_pd3dDevice_DX11 = NULL;
	}
	if (NULL != Cg_pImmediateContext_DX11) {
		delete Cg_pImmediateContext_DX11;
		Cg_pImmediateContext_DX11 = NULL;
	}
	if (NULL != Cg_pSwapChain_DX11) {
		delete Cg_pSwapChain_DX11;
		Cg_pSwapChain_DX11 = NULL;
	}
}

////////////////////////////////////////////// DEVICE //////////////////////////////////////////////

HRESULT RenderManager::CD3D11CreateDeviceAndSwapChain(IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc, IDXGISwapChain** ppSwapChain, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext)
{
	return CD3D11CreateDeviceAndSwapChain(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, pSwapChainDesc, ppSwapChain, ppDevice, pFeatureLevel, ppImmediateContext);
}

HRESULT RenderManager::CCreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView)
{
	return Cg_pd3dDevice_DX11->CreateRenderTargetView(pResource, pDesc, ppRTView);
}

HRESULT RenderManager::CCreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D)
{
	return Cg_pd3dDevice_DX11->CreateTexture2D(pDesc, pInitialData, ppTexture2D);
}

HRESULT RenderManager::CCreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView)
{
	return Cg_pd3dDevice_DX11->CreateDepthStencilView(pResource, pDesc, ppDepthStencilView);
}

HRESULT RenderManager::CCreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView)
{
	return Cg_pd3dDevice_DX11->CreateShaderResourceView(pResource, pDesc, ppSRView);
}

HRESULT RenderManager::CCreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader)
{
	return Cg_pd3dDevice_DX11->CreateVertexShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader);
}

HRESULT RenderManager::CCreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
{
	return Cg_pd3dDevice_DX11->CreateInputLayout(pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout);
}

HRESULT RenderManager::CCreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader)
{
	return Cg_pd3dDevice_DX11->CreatePixelShader(pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader);
}

HRESULT RenderManager::CCreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer)
{
	return Cg_pd3dDevice_DX11->CreateBuffer(pDesc, pInitialData, ppBuffer);
}

HRESULT RenderManager::CCreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
{
	return Cg_pd3dDevice_DX11->CreateSamplerState(pSamplerDesc, ppSamplerState);
}

HRESULT RenderManager::CCreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState)
{
	return Cg_pd3dDevice_DX11->CreateRasterizerState(pRasterizerDesc, ppRasterizerState);
}

void RenderManager::CRelease_Device_DIRECT()
{
	Cg_pd3dDevice_DX11->Release();
}

////////////////////////////////////////////// DEVICE CONTEXT //////////////////////////////////////////////

void RenderManager::COMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
	Cg_pImmediateContext_DX11->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void RenderManager::CRSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
	Cg_pImmediateContext_DX11->RSSetViewports(NumViewports, pViewports);
}

void RenderManager::CIASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	Cg_pImmediateContext_DX11->IASetInputLayout(pInputLayout);
}

void RenderManager::CIASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	Cg_pImmediateContext_DX11->IASetPrimitiveTopology(Topology);
}

void RenderManager::CUpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	Cg_pImmediateContext_DX11->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void RenderManager::CIASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
{
	Cg_pImmediateContext_DX11->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void RenderManager::CIASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	Cg_pImmediateContext_DX11->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void RenderManager::CClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
	Cg_pImmediateContext_DX11->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void RenderManager::CClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	Cg_pImmediateContext_DX11->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void RenderManager::CVSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	Cg_pImmediateContext_DX11->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void RenderManager::CVSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	Cg_pImmediateContext_DX11->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void RenderManager::CRSSetState(ID3D11RasterizerState* pRasterizerState)
{
	Cg_pImmediateContext_DX11->RSSetState(pRasterizerState);
}

void RenderManager::CPSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	Cg_pImmediateContext_DX11->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void RenderManager::CPSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	Cg_pImmediateContext_DX11->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void RenderManager::CPSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	Cg_pImmediateContext_DX11->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void RenderManager::CPSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	Cg_pImmediateContext_DX11->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void RenderManager::CClearState()
{
	Cg_pImmediateContext_DX11->ClearState();
}

void RenderManager::CDrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	Cg_pImmediateContext_DX11->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}

void RenderManager::CRelease_Device_Immediate_DIRECT()
{
	Cg_pImmediateContext_DX11->Release();
}

////////////////////////////////////////////// SWAP CHAIN //////////////////////////////////////////////

HRESULT RenderManager::CGetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
{
	return Cg_pSwapChain_DX11->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT RenderManager::CPresent(UINT SyncInterval, UINT Flags)
{
	return Cg_pSwapChain_DX11->Present(SyncInterval, Flags);
}

void RenderManager::CRelease_SwapChain_DIRECT()
{
	Cg_pSwapChain_DX11->Release();
}

