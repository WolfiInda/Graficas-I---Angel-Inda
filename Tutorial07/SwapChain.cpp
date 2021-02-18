#include "SwapChain.h"

SwapChain::SwapChain()
{
}

SwapChain::~SwapChain()
{
}

HRESULT SwapChain::CGetBuffer(UINT Buffer, REFIID riid, void** ppSurface)
{
	return CSwapChain->GetBuffer(Buffer, riid, ppSurface);
}

HRESULT SwapChain::CPresent(UINT SyncInterval, UINT Flags)
{
	return CSwapChain->Present(SyncInterval, Flags);
}
