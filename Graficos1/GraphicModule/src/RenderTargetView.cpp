#include "RenderTargetView.h"

RenderTargetView::RenderTargetView()
{
#if defined(DX11)
	Cg_pRenderTargetView_DX11 = NULL;
#endif
}

RenderTargetView::~RenderTargetView()
{
#if defined(DX11)
	if (NULL != Cg_pRenderTargetView_DX11) {
		delete Cg_pRenderTargetView_DX11;
		Cg_pRenderTargetView_DX11 = NULL;
	}
#endif
}

void RenderTargetView::CRelease_DIRECT()
{
#if defined(DX11)
	Cg_pRenderTargetView_DX11->Release();
#endif
}

