#pragma once

using namespace std;
#include "debug.h"
#include "Game_Picture.h"
#include "Game_Picture_Static.h"
class Scene_Base
{
	protected:
		//vector<Game_Image*>* _images = NULL;
		bool _isPlaying = false;
		int id=1;
		unordered_map<int, unique_ptr<Game_Picture>> _images;
	public:
		// GET & SET
		// vector<Game_ObjectBase*>* objects() { return _objects; }

		// Run this function when scene start.
		virtual void Intro() {};
		// Run this function when scene delete.
		virtual void Outtro() {};
		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode)  {};
		// Key event handler
		virtual void KeyUpEventHandler(int KeyCode) {};

		virtual void Render();
		virtual void RenderFILLER();
		virtual void RenderImagePhase();
		virtual void Update(DWORD dt) {}
		virtual void Load() {}
		virtual void Unload() {}
		bool IsPlaying() { return _isPlaying; }
		void PLAY() { _isPlaying = true; }
		void PAUSE() { _isPlaying = false; }

		void _NextScene(int signal);
		virtual void nextScene() {};
		void AddBlinkingDarkEffect(float x, float y, int width, int height, int& id,int ani_id=99980);
		void AddImage(float x, float y, int index, int spriteID, BYTE RenderMode);
		void AddImage(float x, float y, int index, int spriteID,float ratiox,float ratioy, BYTE RenderMode);
		void AddText(int& x, int& y, const wchar_t* str, int& index, float ratio, BYTE RenderMode);
		void AddText(int& x, int& y, const wchar_t* str, int& index, float ratiox, float ratioy, BYTE RenderMode);
		void AddNumber(int& x, int& y, int str, int& index, float ratio, BYTE RenderMode);
		void AddNumber(int& x, int& y, int str, int& index, float ratiox,float ratioy, BYTE RenderMode);
		void AddImage_Static(float x, float y, int index, int spriteID, float ratio, BYTE RenderMode);
		void AddImage_Static(float x, float y, int index, int spriteID, float ratiox, float ratioy, BYTE RenderMode);

};

