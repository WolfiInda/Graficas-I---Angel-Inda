#pragma once
#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

class RenderManager
{
public: 
	RenderManager();
	~RenderManager();

public:
#if defined(DX11)
	/////////////////////Device/////////////////////
	HRESULT CD3D11CreateDeviceAndSwapChain(
		IDXGIAdapter*				pAdapter,
		D3D_DRIVER_TYPE            DriverType,
		HMODULE                    Software,
		UINT                       Flags,
		const D3D_FEATURE_LEVEL* pFeatureLevels,
		UINT                       FeatureLevels,
		UINT                       SDKVersion,
		const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
		IDXGISwapChain**			ppSwapChain,
		ID3D11Device**				ppDevice,
		D3D_FEATURE_LEVEL*			pFeatureLevel,
		ID3D11DeviceContext**		ppImmediateContext
	);

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

	HRESULT CCreateShaderResourceView(
		ID3D11Resource* pResource,
		const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc,
		ID3D11ShaderResourceView** ppSRView
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

	HRESULT CCreateRasterizerState(
		const D3D11_RASTERIZER_DESC* pRasterizerDesc,
		ID3D11RasterizerState** ppRasterizerState
	);

	void CRelease_Device_DIRECT();

 	///////////////////////////////////////////////////////

	/////////////////////DeviceContext/////////////////////
	void COMSetRenderTargets(
		UINT                   NumViews,
		ID3D11RenderTargetView* const* ppRenderTargetViews,
		ID3D11DepthStencilView* pDepthStencilView
	);

	void CRSSetViewports(
		UINT                 NumViewports,
		const D3D11_VIEWPORT* pViewports
	);

	void CIASetInputLayout(
		ID3D11InputLayout* pInputLayout
	);

	void CIASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY Topology
	);

	void CUpdateSubresource(
		ID3D11Resource* pDstResource,
		UINT            DstSubresource,
		const D3D11_BOX* pDstBox,
		const void* pSrcData,
		UINT            SrcRowPitch,
		UINT            SrcDepthPitch
	);

	void CIASetVertexBuffers(
		UINT         StartSlot,
		UINT         NumBuffers,
		ID3D11Buffer* const* ppVertexBuffers,
		const UINT* pStrides,
		const UINT* pOffsets
	);

	void CIASetIndexBuffer(
		ID3D11Buffer* pIndexBuffer,
		DXGI_FORMAT  Format,
		UINT         Offset
	);

	void CClearRenderTargetView(
		ID3D11RenderTargetView* pRenderTargetView,
		const FLOAT        ColorRGBA[4]
	);

	void CClearDepthStencilView(
		ID3D11DepthStencilView* pDepthStencilView,
		UINT                   ClearFlags,
		FLOAT                  Depth,
		UINT8                  Stencil
	);

	void CVSSetShader(
		ID3D11VertexShader* pVertexShader,
		ID3D11ClassInstance* const* ppClassInstances,
		UINT                NumClassInstances
	);

	void CVSSetConstantBuffers(
		UINT         StartSlot,
		UINT         NumBuffers,
		ID3D11Buffer* const* ppConstantBuffers
	);

	void CRSSetState(
		ID3D11RasterizerState* pRasterizerState
	);

	void CPSSetShader(
		ID3D11PixelShader* pPixelShader,
		ID3D11ClassInstance* const* ppClassInstances,
		UINT                NumClassInstances
	);

	void CPSSetConstantBuffers(
		UINT         StartSlot,
		UINT         NumBuffers,
		ID3D11Buffer* const* ppConstantBuffers
	);

	void CPSSetShaderResources(
		UINT                     StartSlot,
		UINT                     NumViews,
		ID3D11ShaderResourceView* const* ppShaderResourceViews
	);

	void CPSSetSamplers(
		UINT               StartSlot,
		UINT               NumSamplers,
		ID3D11SamplerState* const* ppSamplers
	);

	void CClearState();

	void CDrawIndexed(
		UINT IndexCount,
		UINT StartIndexLocation,
		INT  BaseVertexLocation
	);

	void CRelease_Device_Immediate_DIRECT();

	//////////////// SWAP CHAIN ///////////////////////
	HRESULT CGetBuffer(
		UINT   Buffer,
		REFIID riid,
		void** ppSurface
	);

	HRESULT CPresent(
		UINT SyncInterval,
		UINT Flags
	);

	void CRelease_SwapChain_DIRECT();

	ID3D11Device*& getDevice_DIRECT() { return Cg_pd3dDevice_DX11; }
	ID3D11DeviceContext*& getImmediateContext_DIRECT() { return Cg_pImmediateContext_DX11; }
	IDXGISwapChain*& getSwapChain_DIRECT() { return Cg_pSwapChain_DX11; }
#endif

private:
#if defined(DX11)
	ID3D11Device* Cg_pd3dDevice_DX11;
	ID3D11DeviceContext* Cg_pImmediateContext_DX11;
	IDXGISwapChain* Cg_pSwapChain_DX11;
#endif
};

