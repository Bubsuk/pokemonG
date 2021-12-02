#pragma once
#include "GameEntity.h"


class Image;
//class Collider;
class GameObject : public GameEntity
{
protected:
	Image* mImage = nullptr;
	//Collider* mCollider = nullptr;

	POINTFLOAT mPos = {};
	eDir mDir = eDir::Idle;
	//const POINTFLOAT DIR_VALUE[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

public:
	GameObject();
	~GameObject();

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	//inline Collider* GetCollider() { return mCollider; }
	inline POINTFLOAT GetPosition() { return mPos; }
	inline void SetPosition(POINTFLOAT pos) { mPos = pos; }
	inline eDir GetDirection() { return mDir; }
	inline void SetDirection(eDir dir) { mDir = dir; }

	//virtual void OnCollided(eCollisionDir dir, int tag) override;
};