#pragma once
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment (lib, "xinput.lib")//---���ǉ�---
#include <d3d11_1.h>
#include <directxcolors.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>
#include<Xinput.h>
#include"Controller.h"

#define XINPUT_GAMEPAD_DPAD_LEFTUP          0x0005
#define XINPUT_GAMEPAD_DPAD_LEFTDOWN        0x0006
#define XINPUT_GAMEPAD_DPAD_RIGHTUP         0x0009
#define XINPUT_GAMEPAD_DPAD_RIGHTDOWN       0x0010

#define DEADZONE_STICK 15000
#define DEADZONE_MSTICK -15000

void Input_Update();
bool Input_GetKeyPress(int vkey);
bool Input_GetKeyTrigger(int vkey);
bool Input_LstickRightUp();

//--------------------------------------------------------------------------------------
// DirectX11�N���X�FDirectX�֌W
//--------------------------------------------------------------------------------------
class DirectX11
{
public:
	DirectX11();
	~DirectX11();
	HRESULT InitDevice();
	void Render();
private:
	//------------------------------------------------------------
	// DirectX11��Direct2D 1.1�̏�����
	//------------------------------------------------------------
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_D3DDeviceContext;
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_D2DDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_DXGISwapChain1;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_D2DBitmap1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_D3DRenderTargetView;

	//------------------------------------------------------------
	// DirectWrite�̏�����
	//------------------------------------------------------------
	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_DWriteTextFormat;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_D2DSolidBrush;
};