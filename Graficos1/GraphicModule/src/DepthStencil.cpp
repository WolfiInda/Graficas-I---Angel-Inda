#include "DepthStencil.h"

DepthStencil::DepthStencil()
{
#if defined(DX11)
	Cg_pDepthStencilView_DX11 = NULL;
#endif
}

DepthStencil::~DepthStencil()
{
#if defined(DX11)
	if (NULL != Cg_pDepthStencilView_DX11) {
		delete Cg_pDepthStencilView_DX11;
		Cg_pDepthStencilView_DX11 = NULL;
	}
#endif
}

void DepthStencil::CRelease_DIRECT()
{
#if defined(DX11)
	Cg_pDepthStencilView_DX11->Release();
#endif
}
