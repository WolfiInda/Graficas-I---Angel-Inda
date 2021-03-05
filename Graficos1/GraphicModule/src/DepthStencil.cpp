#include "DepthStencil.h"

DepthStencil::DepthStencil()
{
	Cg_pDepthStencilView_DX11 = NULL;
}

DepthStencil::~DepthStencil()
{
	if (NULL != Cg_pDepthStencilView_DX11) {
		delete Cg_pDepthStencilView_DX11;
		Cg_pDepthStencilView_DX11 = NULL;
	}
}

void DepthStencil::CRelease_DIRECT()
{
	Cg_pDepthStencilView_DX11->Release();
}
