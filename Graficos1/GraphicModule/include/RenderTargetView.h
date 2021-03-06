#pragma once

#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

class RenderTargetView
{
public:
	RenderTargetView();
	~RenderTargetView();

public:
	void CRelease_DIRECT();
#if defined(DX11)
	ID3D11RenderTargetView*& getRenderTargetView_DIRECT() { return Cg_pRenderTargetView_DX11; }
#endif

private:
#if defined(DX11)
	ID3D11RenderTargetView* Cg_pRenderTargetView_DX11;
#endif
};

