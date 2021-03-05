#pragma once

#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

class DepthStencil
{
public:
	DepthStencil();
	~DepthStencil();

public:
	void CRelease_DIRECT();

	ID3D11DepthStencilView*& getDepthStencilView_DIRECT() { return Cg_pDepthStencilView_DX11; }

private:
	ID3D11DepthStencilView* Cg_pDepthStencilView_DX11;

};

