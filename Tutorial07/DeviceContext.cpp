#include "DeviceContext.h"

DeviceContext::DeviceContext()
{
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::COMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
{
	CImmediateContext->OMSetRenderTargets(NumViews, ppRenderTargetViews, pDepthStencilView);
}

void DeviceContext::CRSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports)
{
	CImmediateContext->RSSetViewports(NumViewports, pViewports);
}

void DeviceContext::CIASetInputLayout(ID3D11InputLayout* pInputLayout)
{
	CImmediateContext->IASetInputLayout(pInputLayout);
}

void DeviceContext::CIASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets)
{
	CImmediateContext->IASetVertexBuffers(StartSlot, NumBuffers, ppVertexBuffers, pStrides, pOffsets);
}

void DeviceContext::CIASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset)
{
	CImmediateContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
}

void DeviceContext::CIASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	CImmediateContext->IASetPrimitiveTopology(Topology);
}

void DeviceContext::CUpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch)
{
	CImmediateContext->UpdateSubresource(pDstResource, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void DeviceContext::CClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4])
{
	CImmediateContext->ClearRenderTargetView(pRenderTargetView, ColorRGBA);
}

void DeviceContext::CClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil)
{
	CImmediateContext->ClearDepthStencilView(pDepthStencilView, ClearFlags, Depth, Stencil);
}

void DeviceContext::CVSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	CImmediateContext->VSSetShader(pVertexShader, ppClassInstances, NumClassInstances);
}

void DeviceContext::CVSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	CImmediateContext->VSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void DeviceContext::CPSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances)
{
	CImmediateContext->PSSetShader(pPixelShader, ppClassInstances, NumClassInstances);
}

void DeviceContext::CPSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers)
{
	CImmediateContext->PSSetConstantBuffers(StartSlot, NumBuffers, ppConstantBuffers);
}

void DeviceContext::CPSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	CImmediateContext->PSSetShaderResources(StartSlot, NumViews, ppShaderResourceViews);
}

void DeviceContext::CPSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
{
	CImmediateContext->CSSetSamplers(StartSlot, NumSamplers, ppSamplers);
}

void DeviceContext::CDrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	CImmediateContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
}
