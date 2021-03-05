#include "RenderTargetView.h"

RenderTargetView::RenderTargetView()
{
	Cg_pRenderTargetView_DX11 = NULL;
}

RenderTargetView::~RenderTargetView()
{
	if (NULL != Cg_pRenderTargetView_DX11) {
		delete Cg_pRenderTargetView_DX11;
		Cg_pRenderTargetView_DX11 = NULL;
	}
}

void RenderTargetView::CRelease_DIRECT()
{
	Cg_pRenderTargetView_DX11->Release();
}

