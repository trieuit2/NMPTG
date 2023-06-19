#pragma once

#define TYPE_STATIC 0
#define TYPE_MOVABLE 1

using namespace std;
#include "Game_Collision.h"
#include "Animations.h"
#include "debug.h"
#include "Contra_GET_ANI.h"
class Game_ObjectBase
{
	protected:
		/// POS

		// horizonal position, base on current map
		float _x;
		// vertical position, base on current map
		float _y;
		// Value use to determine with object will be draw first
		// Object with lowest value will be drawn first.
		int _z;

		float _vx = 0;
		float _vy = 0;

		/// PROPERTIES

		int _width;
		int _height;

		// LOGIC
		int _id = -1;
		bool _isDeleted = false;
		bool _needScanCollision = false;
		// RENDER 

		int _SpriteId = 0;
		bool _needRender = true;

		/// PROTECTED FUNCTIONS

		void UpdatePosition(DWORD dt);
		virtual void ResetStateParams();
		void ResetSpeed();

		// Clean data after calling destructor
		virtual void Cleaning() {}
	public:
		Game_ObjectBase(float x = 0, float y = 0, int z = 0, int width = 0, int height = 0);

		// GET SET FUNCTIONS
		int id() { return _id; }
		float x() { return _x; }
		float y() { return _y; }
		int z() { return _z; }
		int width() { return _width; }
		int height() { return _height; }
		float getRadius(){ return max(_width,_height)/1.0f; }
		void SetId(int id) { _id = id; }
		void SetPosition(float x, float y) { this->_x = x, this->_y = y; }
		void SetSpeed(float vx, float vy) { this->_vx = vx, this->_vy = vy; }
		void GetPosition(float& x, float& y) { x = this->_x; y = this->_y; }
		void GetSpeed(float& vx, float& vy) { vx = this->_vx; vy = this->_vy; }
		void GetCenterPoint(float& x, float& y) { x = _x + _width / 2.0f; y = _y - _height / 2.0f; }
		void SetCenterPoint(float x, float y) { this->_x = x - _width/2.0f, this->_y = y + _height / 2.0f; }
		bool NeedScanCollision() { return _needScanCollision; }
		// 0 - left alignment
		// 1 - center aligment
		// 2 - right aligment
		void SetWidth(int width, int mode = 0);
		// 0 - top alignment
		// 1 - center aligment
		// 2 - bottom aligment
		void SetHeight(int height, int mode = 0);

		// Draw object to screen
		virtual void Render();
		virtual void SetNeedRender(bool b) { _needRender = b; }
		virtual bool NeedRender() { return _needRender; }
		// For debug
		virtual void RenderHitbox();

		// Movable object or Static Object
		virtual int baseType() = 0;

		// UPDATE

		virtual void Update(DWORD dt) {}
		virtual void Update(DWORD dt, vector< Game_ObjectBase*>* coObjects) {}
		virtual void Update(DWORD dt, unordered_map<int, Game_ObjectBase*>* coObjects) {}
		//virtual void Execute_AfterUpdating(DWORD dt) {}

		// COLLISION

		// Get hitbox
		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		// Collision ON or OFF ? This can change depending on object's state. For example: die
		virtual int IsCollidable() { return 0; }
		// When no collision has been detected (triggered by CCollision::Process)
		virtual void OnNoCollision(DWORD dt);
		// When collision with an object has been detected (triggered by CCollision::Process)
		virtual void OnCollisionWith(PCOLLISIONEVENT e);
		// Is this object blocking other object? If YES, collision framework will automatically push the other object
		virtual bool IsBlocking() { return 0; }
		// Aditional condition for blocking object. This condition will check if object has IsBlocking = 1.
		// If NO, this Blocking object will be skip while processing collision framework.
		virtual bool BlockingCondition(DWORD dt, PCOLLISIONEVENT e) { return 1; }
		// Aditional condition for src object. This condition will check if blocking object has IsBlocking = 1.
		// If NO, this collision event will be skip while processing collision framework.
		virtual bool CollideBlockerCondition(DWORD dt, PCOLLISIONEVENT e) { return 1; }
		// Can this object ingore blocking object and move through it?
		// If YES, collision framework will skip this collision event.
		virtual bool IgnoreBlocking() { return 1; }


		// Key event handler
		virtual void KeyDownEventHandler(int KeyCode) {}
		// Key event handler
		virtual void KeyUpEventHandler(int KeyCode) {}
		// Key state handler
		virtual void KeyStateHandler(BYTE* state) {}

		virtual void DeleteThis() { _isDeleted = true; }
		bool IsDeleted() { return _isDeleted; }
		virtual void Execute_BeforeDelete() {}

	protected:
		int curFrame;
		ULONGLONG curFrameTime;
		int curAni;
	public:
		virtual void _Render(int aniId, float x, float y);
		void _Render(int aniId);
		bool atFinalFrame(int curAni=-99);
};

