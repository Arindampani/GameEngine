#pragma once
#include <Windows.h>
#include "Glib.h"
#include "../Containers/Pointers.h"
namespace Engine
{
	
	static bool ToQuit = false;

	bool Init(const HINSTANCE& i_hInstance,const int& i_nCmdShow);
	void Run();
	bool QuitRequested();
	void Shutdown();
	void RequestShutdown();

	
}