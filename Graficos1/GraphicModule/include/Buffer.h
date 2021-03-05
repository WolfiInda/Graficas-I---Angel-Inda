#pragma once

#if defined(DX11)
	#include <d3d11.h>
	#include <d3dx11.h>
#endif

#if defined(DX11)
	enum D3D11_USAGE_DIRECT
	{
		D3D11_USAGE_DEFAULT_DX11 = 0,
		D3D11_USAGE_IMMUTABLE_DX11, 
		D3D11_USAGE_DYNAMIC_DX11,
		D3D11_USAGE_STAGING_DX11
	};

	struct BUFFER_DESC_DIRECT
	{
		UINT ByteWidth;
		D3D11_USAGE_DIRECT Usage;
		UINT BindFlags;
		UINT CPUAccessFlags;
		UINT MuscFlags;
		UINT StructureByteStride;
	};
#endif

class Buffer
{
public:
	Buffer();
	~Buffer();

public:

	void CRelease_DIRECT();
#if defined(DX11)
	ID3D11Buffer*& getBuffer_DIRECT() { return CBuffer_DIRECT; }
#endif
	
private:
#if defined(DX11)
	ID3D11Buffer* CBuffer_DIRECT;
#endif
};

