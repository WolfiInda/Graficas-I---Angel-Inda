#pragma once

#include <windows.h>
#include <Buffer.h>
#include <Texture2D.h>
#include <RenderTargetView.h>
#include <DepthStencil.h>
#include <RenderManager.h>
#include "Camara.h"
#include "Mesh.h"

#if defined(DX11)
    #include <d3d11.h>
    #include <d3dx11.h>
    #include <d3dcompiler.h>
    #include <xnamath.h>
#endif

namespace GraphicsModule
{

    struct VIEWPORT
    {
#if defined(DX11)
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;             
#endif
    };

  struct SimpleVertex
  {
#if defined(DX11)
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
#endif
  };

  struct CBNeverChanges
  {
#if defined(DX11)
    XMMATRIX mView;
#endif
  };

  struct CBChangeOnResize
  {
#if defined(DX11)
    XMMATRIX mProjection;
#endif
  };

  struct CBChangesEveryFrame
  {
#if defined(DX11)
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
#endif
  };

  class test
  {
  public:
#if defined(DX11)
    D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;                                                  
    D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;   
    RenderManager*                      g_RenderManager;
   //RenderManager*                      g_pd3dDevice;                      //ID3D11Device*   g_pd3dDevice = NULL;                                                                  
   //RenderManager*                      g_pImmediateContext;               //ID3D11DeviceContext*  g_pImmediateContext = NULL;                                                           
   //RenderManager*                      g_pSwapChain;                      //IDXGISwapChain* g_pSwapChain = NULL;
    RenderTargetView*                   g_pRenderTargetView;               //ID3D11RenderTargetView*  g_pRenderTargetView = NULL;
    Texture2D*                          g_pDepthStencil = NULL;            //ID3D11Texture2D*   g_pDepthStencil = NULL;       
    DepthStencil*                       g_pDepthStencilView;               // ID3D11DepthStencilView* g_pDepthStencilView = NULL;
    ID3D11ShaderResourceView*           g_pDepthStencilSRV = NULL;                                                            
    ID3D11VertexShader*                 g_pVertexShader = NULL;                                                               
    ID3D11PixelShader*                  g_pPixelShader = NULL;                                                                
    ID3D11InputLayout*                  g_pVertexLayout = NULL;                                                               
    Buffer*                             g_pVertexBuffer = NULL;            //ID3D11Buffer*   g_pVertexBuffer = NULL;          
    Buffer*                             g_pIndexBuffer = NULL;             //ID3D11Buffer*   g_pIndexBuffer = NULL;           
    Buffer*                             g_pCBNeverChanges = NULL;          //ID3D11Buffer*   g_pCBNeverChanges = NULL;        
    Buffer*                             g_pCBChangeOnResize = NULL;        //ID3D11Buffer*   g_pCBChangeOnResize = NULL;      
    Buffer*                             g_pCBChangesEveryFrame = NULL;     //ID3D11Buffer*   g_pCBChangesEveryFrame = NULL;   
    ID3D11ShaderResourceView*           g_pTextureRV = NULL;
    ID3D11SamplerState*                 g_pSamplerLinear = NULL;
    XMMATRIX                            g_World;
    XMMATRIX                            g_View;
    XMMATRIX                            g_Projection;
    XMFLOAT4                            g_vMeshColor;
    Buffer*                             g_pVertexBuffer2 = NULL;           //ID3D11Buffer*   g_pVertexBuffer2 = NULL;
    Buffer*                             g_pIndexBuffer2 = NULL;            //ID3D11Buffer*   g_pIndexBuffer2 = NULL;
    ID3D11VertexShader*                 g_pVertexShader2 = NULL;
    ID3D11PixelShader*                  g_pPixelShader2 = NULL;
    ID3D11RasterizerState*              g_Rasterizer = NULL;
    ID3D11RasterizerState*              g_Rasterizer2 = NULL;
    ID3D11InputLayout*                  g_pVertexLayout2 = NULL;
    Camara                              C;
    LPPOINT                             Cursor_Old = new POINT;
    LPPOINT                             Cursor_New = new POINT;
    Mesh                                M;

    ///Textures Cubes.
    RenderTargetView*                   Cg_pRenderTargetView_1;
    RenderTargetView*                   Cg_pRenderTargetView_2;
    RenderTargetView*                   Cg_pRenderTargetView_3;
    ID3D11ShaderResourceView*           Cg_pTextureRV_1 = NULL;
    ID3D11ShaderResourceView*           Cg_pTextureRV_2 = NULL;
    ID3D11ShaderResourceView*           Cg_pTextureRV_3 = NULL;
        
#endif

  public:
#if defined(DX11)
    HRESULT CompileShaderFromFile(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
#endif

    HRESULT InitDevice(HWND _hwnd);


    void Update();
    void Render();

    void CleanupDevice();
    //void createBuffer(miBufferDesc _desc, MiBuffer& _outBuffer)

    HWND m_hwnd;
  };

  extern test& getTestObj(HWND m_hwnd);
}