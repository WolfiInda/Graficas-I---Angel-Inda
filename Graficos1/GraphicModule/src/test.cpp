#include "test.h"


namespace GraphicsModule
{
#if defined(DX11)
  HRESULT test::CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
  {
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows
    // the shaders to be optimized and to run exactly the way they will run in
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFileA(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
      dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
      if (pErrorBlob != NULL)
        OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
      if (pErrorBlob) pErrorBlob->Release();
      return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;

  }

#endif

  HRESULT test::InitDevice(HWND _hwnd)
  {
#if defined(DX11)
    g_pVertexBuffer = new Buffer();
    g_pIndexBuffer = new Buffer();
    g_pCBNeverChanges = new Buffer();
    g_pCBChangeOnResize = new Buffer();
    g_pCBChangesEveryFrame = new Buffer();
    g_pVertexBuffer2 = new Buffer();
    g_pIndexBuffer2 = new Buffer();
    g_pDepthStencil = new Texture2D();
    g_pRenderTargetView = new RenderTargetView();
    g_pDepthStencilView = new DepthStencil();
    g_RenderManager = new RenderManager();
    //g_pd3dDevice = new RenderManager();
    //g_pImmediateContext = new RenderManager();
    //g_pSwapChain = new RenderManager();
    Cg_pRenderTargetView_1 = new RenderTargetView();
    Cg_pRenderTargetView_2 = new RenderTargetView();
    Cg_pRenderTargetView_3 = new RenderTargetView();

    m_hwnd = _hwnd;

    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(m_hwnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
      g_driverType = driverTypes[driverTypeIndex];
      hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
        D3D11_SDK_VERSION, &sd, &g_RenderManager->getSwapChain_DIRECT(), &g_RenderManager->getDevice_DIRECT(), &g_featureLevel, &g_RenderManager->getImmediateContext_DIRECT());
      if (SUCCEEDED(hr))
        break;
    }
    if (FAILED(hr))
      return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = g_RenderManager->CGetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
      return hr;

    hr = g_RenderManager->CCreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView->getRenderTargetView_DIRECT());
    pBackBuffer->Release();
    if (FAILED(hr))
      return hr;

    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_R32_TYPELESS;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = g_RenderManager->CCreateTexture2D(&descDepth, NULL, &g_pDepthStencil->getTexture_DIRECT());
    if (FAILED(hr))
      return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = g_RenderManager->CCreateDepthStencilView(g_pDepthStencil->getTexture_DIRECT(), &descDSV, &g_pDepthStencilView->getDepthStencilView_DIRECT());
    if (FAILED(hr))
      return hr;

    // and the resource view for the shader
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1; // same as orig texture
    hr = g_RenderManager->CCreateShaderResourceView(g_pDepthStencil->getTexture_DIRECT(), &srvDesc, &g_pDepthStencilSRV);
    if (FAILED(hr))
      return hr;

    g_RenderManager->COMSetRenderTargets(1, &g_pRenderTargetView->getRenderTargetView_DIRECT(), g_pDepthStencilView->getDepthStencilView_DIRECT());

    // Setup the viewport
    VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_RenderManager->CRSSetViewports(1, reinterpret_cast<D3D11_VIEWPORT*> (&vp));

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile("Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
      MessageBox(NULL,
        "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
      return hr;
    }

    // Create the vertex shader
    hr = g_RenderManager->CCreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
      pVSBlob->Release();
      return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = g_RenderManager->CCreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
      pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
      return hr;

    // Compile the vertex shader
    ID3DBlob* pVSBlob2 = NULL;
    hr = CompileShaderFromFile("Limpio.fx", "VS", "vs_4_0", &pVSBlob2);
    if (FAILED(hr))
    {
      MessageBox(NULL,
        "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
      return hr;
    }

    // Create the vertex shader
    hr = g_RenderManager->CCreateVertexShader(pVSBlob2->GetBufferPointer(), pVSBlob2->GetBufferSize(), NULL, &g_pVertexShader2);
    if (FAILED(hr))
    {
      pVSBlob2->Release();
      return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout2[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements2 = ARRAYSIZE(layout2);

    // Create the input layout
    hr = g_RenderManager->CCreateInputLayout(layout2, numElements2, pVSBlob2->GetBufferPointer(),
      pVSBlob2->GetBufferSize(), &g_pVertexLayout2);
    pVSBlob2->Release();
    if (FAILED(hr))
      return hr;

    // Compile the pixel shader
    ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile("Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
      MessageBox(NULL,
        "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
      return hr;
    }

    // Create the pixel shader
    hr = g_RenderManager->CCreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
      return hr;

    // Compile the pixel shader
    ID3DBlob* pPSBlob2 = NULL;
    hr = CompileShaderFromFile("Limpio.fx", "PS", "ps_4_0", &pPSBlob2);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_RenderManager->CCreatePixelShader(pPSBlob2->GetBufferPointer(), pPSBlob2->GetBufferSize(), NULL, &g_pPixelShader2);
    pPSBlob2->Release();
    if (FAILED(hr))
      return hr;

    // Create vertex buffer

    M.setVertex(new sVertex[]
        {
            { Float3{-1.0f, 1.0f, -1.0f}, Float2{0.0f, 0.0f} },
            { Float3{1.0f, 1.0f, -1.0f}, Float2{1.0f, 0.0f} },
            { Float3{1.0f, 1.0f, 1.0f}, Float2{1.0f, 1.0f} },
            { Float3{-1.0f, 1.0f, 1.0f}, Float2{0.0f, 1.0f} },

            { Float3{-1.0f, -1.0f, -1.0f}, Float2{0.0f, 0.0f} },
            { Float3{1.0f, -1.0f, -1.0f}, Float2{1.0f, 0.0f} },
            { Float3{1.0f, -1.0f, 1.0f}, Float2{1.0f, 1.0f} },
            { Float3{-1.0f, -1.0f, 1.0f}, Float2{0.0f, 1.0f} },

            { Float3{-1.0f, -1.0f, 1.0f}, Float2{0.0f, 0.0f} },
            { Float3{-1.0f, -1.0f, -1.0f}, Float2{1.0f, 0.0f} },
            { Float3{-1.0f, 1.0f, -1.0f}, Float2{1.0f, 1.0f} },
            { Float3{-1.0f, 1.0f, 1.0f}, Float2{0.0f, 1.0f} },

            { Float3{1.0f, -1.0f, 1.0f}, Float2{0.0f, 0.0f} },
            { Float3{1.0f, -1.0f, -1.0f}, Float2{1.0f, 0.0f} },
            { Float3{1.0f, 1.0f, -1.0f}, Float2{1.0f, 1.0f} },
            { Float3{1.0f, 1.0f, 1.0f}, Float2{0.0f, 1.0f} },

            { Float3{-1.0f, -1.0f, -1.0f}, Float2{0.0f, 0.0f} },
            { Float3{1.0f, -1.0f, -1.0f}, Float2{1.0f, 0.0f} },
            { Float3{1.0f, 1.0f, -1.0f}, Float2{1.0f, 1.0f} },
            { Float3{-1.0f, 1.0f, -1.0f}, Float2{0.0f, 1.0f} },

            { Float3{-1.0f, -1.0f, 1.0f}, Float2{0.0f, 0.0f} },
            { Float3{1.0f, -1.0f, 1.0f}, Float2{1.0f, 0.0f} },
            { Float3{1.0f, 1.0f, 1.0f}, Float2{1.0f, 1.0f} },
            { Float3{-1.0f, 1.0f, 1.0f}, Float2{0.0f, 1.0f} } }, 24);

    /*
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    };
    */

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(sVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = M.getVertex();
    hr = g_RenderManager->CCreateBuffer(&bd, &InitData, &g_pVertexBuffer->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;

    // Create index buffer
    M.setIndices(new unsigned short[]
        {
            3, 1, 0,
                2, 1, 3,

                6, 4, 5,
                7, 4, 6,

                11, 9, 8,
                10, 9, 11,

                14, 12, 13,
                15, 12, 14,

                19, 17, 16,
                18, 17, 19,

                22, 20, 21,
                23, 20, 22
        }, 36);

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = M.getIndices();
    hr = g_RenderManager->CCreateBuffer(&bd, &InitData, &g_pIndexBuffer->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;

    // Create vertex buffer
    SimpleVertex vertices2[] =
    {
         { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
    };

    D3D11_BUFFER_DESC bd2;
    ZeroMemory(&bd2, sizeof(bd2));
    bd2.Usage = D3D11_USAGE_DEFAULT;
    bd2.ByteWidth = sizeof(SimpleVertex) * 4;
    bd2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd2.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData2;
    ZeroMemory(&InitData2, sizeof(InitData2));
    InitData2.pSysMem = vertices2;
    hr = g_RenderManager->CCreateBuffer(&bd2, &InitData2, &g_pVertexBuffer2->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;


    // Create index buffer
    // Create vertex buffer
    WORD indices2[] =
    {
        2,0,1,
        3,0,2
    };

    bd2.Usage = D3D11_USAGE_DEFAULT;
    bd2.ByteWidth = sizeof(WORD) * 6;
    bd2.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd2.CPUAccessFlags = 0;
    InitData2.pSysMem = indices2;
    hr = g_RenderManager->CCreateBuffer(&bd2, &InitData2, &g_pIndexBuffer2->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;



    // Set primitive topology
    g_RenderManager->CIASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Create the constant buffers
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(CBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    hr = g_RenderManager->CCreateBuffer(&bd, NULL, &g_pCBNeverChanges->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;

    bd.ByteWidth = sizeof(CBChangeOnResize);
    hr = g_RenderManager->CCreateBuffer(&bd, NULL, &g_pCBChangeOnResize->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;

    bd.ByteWidth = sizeof(CBChangesEveryFrame);
    hr = g_RenderManager->CCreateBuffer(&bd, NULL, &g_pCBChangesEveryFrame->getBuffer_DIRECT());
    if (FAILED(hr))
      return hr;

    // Load the Texture
    hr = D3DX11CreateShaderResourceViewFromFile(g_RenderManager->getDevice_DIRECT(), "MemeLehi.dds", NULL, NULL, &g_pTextureRV, NULL);
    if (FAILED(hr))
      return hr;

    // Create the sample state  
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = g_RenderManager->CCreateSamplerState(&sampDesc, &g_pSamplerLinear);
    if (FAILED(hr))
      return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix

    Vec Eye = Vec(0.0f, 3.0f, -6.0f);
    Vec At = Vec(0.0f, 1.0f, 0.0f);
    Vec Up = Vec(0.0f, 1.0f, 0.0f);
    C = Camara(Eye, At, Up, XM_PIDIV4, 0.01f, 100.0f, width, (FLOAT)height, true);
    g_View = C.getViewMatrix(Up, At, Eye);
    /*
    XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
    XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    g_View = XMMatrixLookAtLH(Eye, At, Up);*/

    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose(g_View);
    g_RenderManager->CUpdateSubresource(g_pCBNeverChanges->getBuffer_DIRECT(), 0, NULL, &cbNeverChanges, 0, 0);

    // Initialize the projection matrix
    //g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);
    g_Projection = XMMATRIX(C.getProyection());

    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
    g_RenderManager->CUpdateSubresource(g_pCBChangeOnResize->getBuffer_DIRECT(), 0, NULL, &cbChangesOnResize, 0, 0);


    // create rasterizer state
    D3D11_RASTERIZER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.CullMode = D3D11_CULL_BACK;
    desc.FillMode = D3D11_FILL_SOLID;
    hr = g_RenderManager->CCreateRasterizerState(&desc, &g_Rasterizer);
    if (FAILED(hr))
      return hr;

    desc.CullMode = D3D11_CULL_NONE;
    hr = g_RenderManager->CCreateRasterizerState(&desc, &g_Rasterizer2);
    if (FAILED(hr))
      return hr;

    //Primero
    Texture2D* Texture2DD = new Texture2D();
    D3D11_TEXTURE2D_DESC descTextRT;
    ZeroMemory(&descTextRT, sizeof(descTextRT));
    descTextRT.Width = width;
    descTextRT.Height = height;
    descTextRT.MipLevels = 1;
    descTextRT.ArraySize = 1;
    descTextRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descTextRT.SampleDesc.Count = 1;
    descTextRT.SampleDesc.Quality = 0;
    descTextRT.Usage = D3D11_USAGE_DEFAULT;
    descTextRT.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    descTextRT.CPUAccessFlags = 0;
    descTextRT.MiscFlags = 0;
    hr = g_RenderManager->CCreateTexture2D(&descTextRT, NULL, &Texture2DD->getTexture_DIRECT());
    if (FAILED(hr))
        return hr;

    // create the rt Shader resource view 2
    D3D11_SHADER_RESOURCE_VIEW_DESC descViewRT;
    ZeroMemory(&descViewRT, sizeof(descViewRT));
    descViewRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descViewRT.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    descViewRT.Texture2D.MostDetailedMip = 0;
    descViewRT.Texture2D.MipLevels = 1;
    hr = g_RenderManager->CCreateShaderResourceView(Texture2DD->getTexture_DIRECT(), &descViewRT, &Cg_pTextureRV_1);
    if (FAILED(hr))
        return hr;

    // Create the render target view 2
    hr = g_RenderManager->CCreateRenderTargetView(Texture2DD->getTexture_DIRECT(), NULL, &Cg_pRenderTargetView_1->getRenderTargetView_DIRECT());
    if (FAILED(hr))
        return hr;

    Texture2DD->CRelease_DIRECT();
    //Segunda
 
    ZeroMemory(&descTextRT, sizeof(descTextRT));
    descTextRT.Width = width;
    descTextRT.Height = height;
    descTextRT.MipLevels = 1;
    descTextRT.ArraySize = 1;
    descTextRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descTextRT.SampleDesc.Count = 1;
    descTextRT.SampleDesc.Quality = 0;
    descTextRT.Usage = D3D11_USAGE_DEFAULT;
    descTextRT.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    descTextRT.CPUAccessFlags = 0;
    descTextRT.MiscFlags = 0;
    hr = g_RenderManager->CCreateTexture2D(&descTextRT, NULL, &Texture2DD->getTexture_DIRECT());
    if (FAILED(hr))
        return hr;

    // create the rt Shader resource view 2
    ZeroMemory(&descViewRT, sizeof(descViewRT));
    descViewRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descViewRT.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    descViewRT.Texture2D.MostDetailedMip = 0;
    descViewRT.Texture2D.MipLevels = 1;
    hr = g_RenderManager->CCreateShaderResourceView(Texture2DD->getTexture_DIRECT(), &descViewRT, &Cg_pTextureRV_2);
    if (FAILED(hr))
        return hr;

    // Create the render target view 2
    hr = g_RenderManager->CCreateRenderTargetView(Texture2DD->getTexture_DIRECT(), NULL, &Cg_pRenderTargetView_2->getRenderTargetView_DIRECT());
    if (FAILED(hr))
        return hr;

    Texture2DD->CRelease_DIRECT();
    //Tercero
    ZeroMemory(&descTextRT, sizeof(descTextRT));
    descTextRT.Width = width;
    descTextRT.Height = height;
    descTextRT.MipLevels = 1;
    descTextRT.ArraySize = 1;
    descTextRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descTextRT.SampleDesc.Count = 1;
    descTextRT.SampleDesc.Quality = 0;
    descTextRT.Usage = D3D11_USAGE_DEFAULT;
    descTextRT.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    descTextRT.CPUAccessFlags = 0;
    descTextRT.MiscFlags = 0;
    hr = g_RenderManager->CCreateTexture2D(&descTextRT, NULL, &Texture2DD->getTexture_DIRECT());
    if (FAILED(hr))
        return hr;

    // create the rt Shader resource view 2
    ZeroMemory(&descViewRT, sizeof(descViewRT));
    descViewRT.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    descViewRT.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    descViewRT.Texture2D.MostDetailedMip = 0;
    descViewRT.Texture2D.MipLevels = 1;
    hr = g_RenderManager->CCreateShaderResourceView(Texture2DD->getTexture_DIRECT(), &descViewRT, &Cg_pTextureRV_3);
    if (FAILED(hr))
        return hr;

    // Create the render target view 2
    hr = g_RenderManager->CCreateRenderTargetView(Texture2DD->getTexture_DIRECT(), NULL, &Cg_pRenderTargetView_3->getRenderTargetView_DIRECT());
    if (FAILED(hr))
        return hr;

    Texture2DD->CRelease_DIRECT();

#endif
    return S_OK;

  }

   void test::Update()
   {
#if defined(DX11)
       static bool PrimerFrame = true;

       *Cursor_Old = *Cursor_New;
       GetCursorPos(Cursor_New);
       if (PrimerFrame == false)
       {
           Vec CursorNew(Cursor_New->x, -Cursor_New->y, 0);
           Vec CursorOld(Cursor_Old->x, -Cursor_Old->y, 0);
           C.getRotation(CursorOld, CursorNew);
       }
       else
       {
           PrimerFrame = false;
       }

       // Update our time
       static float t = 0.0f;
       if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
       {
           t += (float)XM_PI * 0.0125f;
       }
       else
       {
           static DWORD dwTimeStart = 0;
           DWORD dwTimeCur = GetTickCount();
           if (dwTimeStart == 0)
               dwTimeStart = dwTimeCur;
           t = (dwTimeCur - dwTimeStart) / 1000.0f;
       }

       // Rotate cube around the origin
       g_World = XMMatrixRotationY(t);
       //g_World *= XMMatrixTranslation(5, 0, 0);

       // Modify the color
       g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
       g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
       g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

       //
       // Update variables that change once per frame
       //

       // XMMATRIX Trans(1.0f, 0.0f, 0.0f, 0.0f,
       //     0.0f, 1.0f, 0.0f, 0.0f,
       //     0.0f, 0.0f, 1.0f, 0.0f,
       //     0.0f, 0.0f, 2.0f, 1.0f);

       g_View = XMMATRIX(C.getViewMatrix());

       /*
       CBNeverChanges cbNeverChanges;
       cbNeverChanges.mView = XMMatrixTranspose(g_View);
       g_pImmediateContext->UpdateSubresource(g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0);*/

       CBChangesEveryFrame cb;
       cb.mWorld = XMMatrixTranspose(g_World);
       cb.vMeshColor = g_vMeshColor;
       g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);

       g_View = XMMATRIX(C.getViewMatrix());
       CBNeverChanges cbNeverChanges;
       cbNeverChanges.mView = XMMatrixTranspose(g_View);
       g_RenderManager->CUpdateSubresource(g_pCBNeverChanges->getBuffer_DIRECT(), 0, NULL, &cbNeverChanges, 0, 0);

       g_Projection = XMMATRIX(C.getProyection());
       CBChangeOnResize cbChangesOnResize;
       cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
       g_RenderManager->CUpdateSubresource(g_pCBChangeOnResize->getBuffer_DIRECT(), 0, NULL, &cbChangesOnResize, 0, 0);
#endif
   }

  void test::Render()
  {
#if defined(DX11)
     CBChangesEveryFrame cb;
    // Update our time
    static float t = 0.0f;
    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
      t += (float)XM_PI * 0.0125f;
    }
    else
    {
      static DWORD dwTimeStart = 0;
      DWORD dwTimeCur = GetTickCount();
      if (dwTimeStart == 0)
        dwTimeStart = dwTimeCur;
      t = (dwTimeCur - dwTimeStart) / 1000.0f;
    }

    // Rotate cube around the origin
    g_World = XMMatrixRotationY(t);

    // Modify the color
    g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
    g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
    g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_RenderManager->CClearRenderTargetView(g_pRenderTargetView->getRenderTargetView_DIRECT(), ClearColor);

    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    g_RenderManager->CClearDepthStencilView(g_pDepthStencilView->getDepthStencilView_DIRECT(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    //
    // Update variables that change once per frame
    //

    /*
    CBChangesEveryFrame cb;
    cb.mWorld = XMMatrixTranspose(g_World);
    cb.vMeshColor = g_vMeshColor;
    g_pImmediateContext->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);*/


    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;

    //
    // Render the cube
    //
    // Set the input layout
    g_RenderManager->CIASetInputLayout(g_pVertexLayout);
    g_RenderManager->CRSSetState(g_Rasterizer);
    g_RenderManager->CIASetVertexBuffers(0, 1, &g_pVertexBuffer->getBuffer_DIRECT(), &stride, &offset);
    g_RenderManager->CIASetIndexBuffer(g_pIndexBuffer->getBuffer_DIRECT(), DXGI_FORMAT_R16_UINT, 0);
    g_RenderManager->CVSSetShader(g_pVertexShader, NULL, 0);
    g_RenderManager->CVSSetConstantBuffers(0, 1, &g_pCBNeverChanges->getBuffer_DIRECT());
    g_RenderManager->CVSSetConstantBuffers(1, 1, &g_pCBChangeOnResize->getBuffer_DIRECT());
    g_RenderManager->CVSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame->getBuffer_DIRECT());
    g_RenderManager->CPSSetShader(g_pPixelShader, NULL, 0);
    g_RenderManager->CPSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame->getBuffer_DIRECT());
    g_RenderManager->CPSSetShaderResources(0, 1, &g_pTextureRV);
    g_RenderManager->CPSSetSamplers(0, 1, &g_pSamplerLinear);

    //Dibujo sobre mi RenderTarget //Primer Cubo
    g_RenderManager->CClearRenderTargetView(Cg_pRenderTargetView_1->getRenderTargetView_DIRECT(), ClearColor);
    g_RenderManager->CClearDepthStencilView(g_pDepthStencilView->getDepthStencilView_DIRECT(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_RenderManager->COMSetRenderTargets(1, &Cg_pRenderTargetView_1->getRenderTargetView_DIRECT(), g_pDepthStencilView->getDepthStencilView_DIRECT());

    g_RenderManager->CDrawIndexed(36, 0, 0);

    //Un cubo normal y un cubo dentro de un cubo que se dibujan dentro de otra textura. 
    g_RenderManager->CClearRenderTargetView(Cg_pRenderTargetView_2->getRenderTargetView_DIRECT(), ClearColor);
    g_RenderManager->CClearDepthStencilView(g_pDepthStencilView->getDepthStencilView_DIRECT(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_RenderManager->COMSetRenderTargets(1, &Cg_pRenderTargetView_2->getRenderTargetView_DIRECT(), g_pDepthStencilView->getDepthStencilView_DIRECT());

    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_1);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(-3, 0 ,0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0); 
    g_RenderManager->CPSSetShaderResources(0, 1, &g_pTextureRV);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    //3 Cubos.
    g_RenderManager->CClearRenderTargetView(Cg_pRenderTargetView_3->getRenderTargetView_DIRECT(), ClearColor);
    g_RenderManager->CClearDepthStencilView(g_pDepthStencilView->getDepthStencilView_DIRECT(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_RenderManager->COMSetRenderTargets(1, &Cg_pRenderTargetView_3->getRenderTargetView_DIRECT(), g_pDepthStencilView->getDepthStencilView_DIRECT());

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(3, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_2);

    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(-3, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);

    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_1);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(0, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &g_pTextureRV);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    //4 Cubos.
    g_RenderManager->CClearRenderTargetView(g_pRenderTargetView->getRenderTargetView_DIRECT(), ClearColor);
    g_RenderManager->CClearDepthStencilView(g_pDepthStencilView->getDepthStencilView_DIRECT(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    g_RenderManager->COMSetRenderTargets(1, &g_pRenderTargetView->getRenderTargetView_DIRECT(), g_pDepthStencilView->getDepthStencilView_DIRECT());

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(0, 3, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_3);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(3, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_2);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(-3, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &Cg_pTextureRV_1);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    cb.mWorld = XMMatrixMultiplyTranspose(g_World, XMMatrixTranslation(0, 0, 0));
    cb.vMeshColor = g_vMeshColor;
    g_RenderManager->CUpdateSubresource(g_pCBChangesEveryFrame->getBuffer_DIRECT(), 0, NULL, &cb, 0, 0);
    g_RenderManager->CPSSetShaderResources(0, 1, &g_pTextureRV);
    g_RenderManager->CDrawIndexed(36, 0, 0);

    //
    // Render the SAQ
    //
    g_RenderManager->CIASetInputLayout(g_pVertexLayout2);
    g_RenderManager->CRSSetState(g_Rasterizer2);
    g_RenderManager->CIASetVertexBuffers(0, 1, &g_pVertexBuffer2->getBuffer_DIRECT(), &stride, &offset);
    g_RenderManager->CIASetIndexBuffer(g_pIndexBuffer2->getBuffer_DIRECT(), DXGI_FORMAT_R16_UINT, 0);
    g_RenderManager->CVSSetShader(g_pVertexShader2, NULL, 0);
    g_RenderManager->CPSSetShader(g_pPixelShader2, NULL, 0);
    //g_pImmediateContext->DrawIndexed(6, 0, 0);
    //
    // Present our back buffer to our front buffer
    //

    //UIRender();
    //g_pSwapChain->Present(0, 0);
#endif
  }

  void test::CleanupDevice()
  {
#if defined(DX11)
    if (g_RenderManager) g_RenderManager->CClearState();

    if (g_pSamplerLinear) g_pSamplerLinear->Release();
    if (g_pTextureRV) g_pTextureRV->Release();
    if (g_pCBNeverChanges) g_pCBNeverChanges->CRelease_DIRECT();
    if (g_pCBChangeOnResize) g_pCBChangeOnResize->CRelease_DIRECT();
    if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->CRelease_DIRECT();
    if (g_pVertexBuffer) g_pVertexBuffer->CRelease_DIRECT();
    if (g_pIndexBuffer) g_pIndexBuffer->CRelease_DIRECT();
    if (g_pVertexLayout) g_pVertexLayout->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (g_pPixelShader) g_pPixelShader->Release();
    if (g_pDepthStencil) g_pDepthStencil->CRelease_DIRECT();
    if (g_pDepthStencilView) g_pDepthStencilView->CRelease_DIRECT();
    if (g_pRenderTargetView) g_pRenderTargetView->CRelease_DIRECT();
    if (g_RenderManager) g_RenderManager->CRelease_SwapChain_DIRECT();
    if (g_RenderManager) g_RenderManager->CRelease_Device_Immediate_DIRECT();
    if (g_RenderManager) g_RenderManager->CRelease_Device_DIRECT();
#endif
  }

  //test& getTestObj(HWND m_hwnd)
 // {
      // TODO: Insertar una instrucción "return" aquí
 // }

  //test& getTestObj(HWND m_hwnd)
 // {
      // TODO: Insertar una instrucción "return" aquí
 // }

  /*extern test& GetTestObj(HWND m_hwnd)
  {
      static test pTest = nullptr;
      if (pTest == nullptr)
      {
          pTest = new test();
          pTest->InitDevice
      }
      return pTest;
  }
  */
} 

