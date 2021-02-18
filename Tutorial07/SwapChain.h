#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	HRESULT CGetBuffer(
		UINT   Buffer,
		REFIID riid,
		void** ppSurface
	);

	HRESULT CPresent(
		UINT SyncInterval,
		UINT Flags
	);


private:
	IDXGISwapChain* CSwapChain = NULL;
};

