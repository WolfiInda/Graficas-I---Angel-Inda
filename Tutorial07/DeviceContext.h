#pragma once
#include <d3d11.h>

class DeviceContext
{
public:
	DeviceContext();
	~DeviceContext();

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

	void CDrawIndexed(
		UINT IndexCount,
		UINT StartIndexLocation,
		INT  BaseVertexLocation
	);

private:
	ID3D11DeviceContext* CImmediateContext = NULL;
};

