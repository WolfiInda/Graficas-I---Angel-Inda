#include "Buffer.h"

Buffer::Buffer()
{
#if defined(DX11)
	CBuffer_DIRECT = NULL;
#endif
}

Buffer::~Buffer()
{
#if defined(DX11)
	if (NULL != CBuffer_DIRECT) {
		delete CBuffer_DIRECT;
		CBuffer_DIRECT = NULL;
	}

#endif
	//delete this;
}


void Buffer::CRelease_DIRECT()
{
#if defined(DX11)
	CBuffer_DIRECT->Release();
#endif
}
