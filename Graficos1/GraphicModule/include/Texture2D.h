#pragma once

#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

public:
	void CRelease_DIRECT();
#if defined(DX11)
	ID3D11Texture2D*& getTexture_DIRECT() { return CTexture_DIRECT; }
#endif

private:
#if defined(DX11)
	ID3D11Texture2D* CTexture_DIRECT;
#endif
};

