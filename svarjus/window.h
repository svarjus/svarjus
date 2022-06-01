#pragma once


#ifndef deez
#define deez
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>
#include <thread>

#include "filesystem.h"
#include "file.h"
#include "pwsh.h"
#include "keys.h"
namespace W
{
	// Data
	static LPDIRECT3D9              g_pD3D = NULL;
	static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
	static D3DPRESENT_PARAMETERS    g_d3dpp = {};

	// Forward declarations of helper functions
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void ResetDevice();
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void window();
	void renderstuff(HWND hwnd);
	void MakeStyle();
	void renderDockWindow();
	
	void render_log(HWND hwnd);

	namespace _utils
	{
		void GetWindowResolution(RECT rect, float* resolution);
		RECT GetWindowDimensions(HWND hwnd, RECT* rect);
	}

}
#endif