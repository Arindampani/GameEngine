#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "../AwesomeEngine/Init/Engine.h"
#include "Game.h"
//bool bQuit;
//bool bSpace;
void* LoadFile(const char* i_pFilename, size_t& o_sizeFile);
GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename);
void RunStartMenu();

//void KeyCallback(unsigned int i_VKeyID, bool bWentDown)
//{
//	if (i_VKeyID == 0x1B && bWentDown) { //ESC key
//
//		bQuit = true;
//	}
//
//	if (i_VKeyID == 0x20 && bWentDown) { //SPACE key
//
//		bSpace = true;
//	}
//}
int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	if (Engine::Init(i_hInstance, i_nCmdShow))
	{

		if (Game::Init())
		{
			// runs our Game until it’s done
			//RunStartMenu();
			Engine::Run();
			Game::Shutdown();

		}

		Engine::Shutdown();
	}


#if defined _debug
	_crtdumpmemoryleaks();
#endif // _debug

	return 0;
}

void RunStartMenu() {
	////bSpace = false;
	////bQuit = false;
	////GLib::SetKeyStateChangeCallback(KeyCallback);
	//GLib::Sprites::Sprite* pBackground = CreateSprite("data\\background.dds");
	//GLib::Sprites::Sprite* pStartMenu = CreateSprite("data\\space.dds");
	//do {
	//	GLib::Service(bQuit);
	//	GLib::BeginRendering();
	//	// Tell GLib that we want to render some sprites
	//	GLib::Sprites::BeginRendering();
	//	GLib::Point2D	Offset = { 0.0f, -300.0f };
	//	GLib::Sprites::RenderSprite(*pBackground, Offset, 0.0f);
	//	GLib::Sprites::RenderSprite(*pStartMenu, Offset, 0.0f);

	//	GLib::Sprites::EndRendering();
	//	// IMPORTANT: Tell GLib we're done rendering
	//	GLib::EndRendering();

	//} while (bSpace == false);

	//if (pBackground)
	//	GLib::Sprites::Release(pBackground);
	//if (pStartMenu)
	//	GLib::Sprites::Release(pStartMenu);

	//return;

}


GLib::Sprites::Sprite* CreateSprite(const char* i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void* pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture* pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite* pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void* LoadFile(const char* i_pFilename, size_t& o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE* pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t* pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}