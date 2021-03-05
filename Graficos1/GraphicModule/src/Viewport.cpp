#include "Viewport.h"

Viewport::Viewport()
{
#if defined(DX11)
	CViewport_DX11 = NULL;
#endif
}

Viewport::~Viewport()
{
#if defined(DX11)
	if (NULL != CViewport_DX11) {
		delete CViewport_DX11;
		CViewport_DX11 = NULL;
	}
#endif
}
