#include "Texture2D.h"

Texture2D::Texture2D()
{
#if defined(DX11)
	CTexture_DIRECT = NULL;
#endif
}

Texture2D::~Texture2D()
{
#if defined(DX11)
	if (NULL != CTexture_DIRECT) {
		delete CTexture_DIRECT;
		CTexture_DIRECT = NULL;
	}
#endif
	//delete this;
}

void Texture2D::CRelease_DIRECT()
{
#if defined(DX11)
	CTexture_DIRECT->Release();
#endif
}
