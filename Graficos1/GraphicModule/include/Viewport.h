#pragma once

#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

#if defined(DX11)
    struct VIEWPORT
    {
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;
    };
#endif

class Viewport
{
public:
    Viewport();
    ~Viewport();

public:
   

private:
#if defined(DX11)
    D3D11_VIEWPORT* CViewport_DX11;
#endif
};

