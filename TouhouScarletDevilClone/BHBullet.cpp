#include "BHBullet.h"

#include "CircleCollisionManager.h"
#include "CommonFunction.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "Shape.h"

void BHBullet::Init(string shapeKey, FPOINT pos)
{
	this->shape = ShapeManager::GetInstance()->FindShape(shapeKey);
	if (shape)
	{
		//TODO:
		this->hitRadius = shape->GetHitWidth() / 2;
	}
	this->position = pos;

	isAlive = true;
	pool = BHObjectManager::GetInstance()->GetEnemyBulletPool();
	
	//TODO: on create
	if (pos.y > GAME_HEIGHT / 2)
	{
		SetCollisionLayer(LAYER_PLAYER_BULLET, LAYER_ENEMY);		
	}
	else
	{
		SetCollisionLayer(LAYER_ENEMY_BULLET, LAYER_PLAYER);
	}
}

void BHBullet::Launch(float angle, float angleRate, float movementSpeed, float moveSpeedRate)
{
	this->radianAngle = angle;
	this->angleRate = angleRate;
	this->movementSpeed = movementSpeed;
	this->speedRate = moveSpeedRate;
}

void BHBullet::Launch(float angleRate, float speedRate, float movementSpeed, bool isPlayerBullet)
{
	this->angleRate = angleRate;
	this->speedRate = speedRate;
	this->movementSpeed = movementSpeed;
	
	if (isPlayerBullet)
	{
		SetCollisionLayer(LAYER_PLAYER_BULLET, LAYER_ENEMY);		
	}
	else
	{
		SetCollisionLayer(LAYER_ENEMY_BULLET, LAYER_PLAYER);
	}
}

void BHBullet::Release()
{
	isAlive = false;
	Reset();
}

void BHBullet::Render(HDC hdc)
{
	if (isAlive == false) return;
	if (shape)
	{
		shape->GetImage()->Middle_RenderFrame(position.x, position.y,1, imageAngle);

#pragma region DEBUG_SHAPE
		// Debug
		// const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
		// const float height= shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();
		// shape->GetImage()->DrawRect(
		// 	{position.x - width / 2, position.y - height / 2},
		// 	{position.x + width / 2 , position.y + height / 2},
		// 	2, 1);
#pragma endregion
	}
}

void BHBullet::Update(float dt)
{
	if (isAlive == false) return;

	FPOINT prev = position;
	Move(radianAngle, movementSpeed, dt);
	
	imageAngle = atan2( prev.x - position.x, -prev.y + position.y);
	imageAngle = RAD_TO_DEG(imageAngle);
	
	// add angular accel to radAngle
	radianAngle += angleRate * dt;
	
	// add accel to movementSpeed;
	movementSpeed += speedRate * dt;
	
	if (IsOutofScreen())
	{
		isAlive = false;
		Reset();
		pool->Release(this);
	}
}

void BHBullet::OnHit(ICollideable* hitObject)
{
	isAlive = false;
	Reset();
	pool->Release(this);
}

void BHBullet::Move(float angle, float speed, float dt)
{
	if (isAlive == false) return;
	// update position with using angle and movement speed
	position.x += speed * cosf(angle) * dt;
	position.y += speed * sinf(angle) * dt;
}

void BHBullet::Reset()
{
	position = {0,0};
	radianAngle = 0;
	angleRate = 0;
	speedRate = 0;
	movementSpeed = 0;
}

bool BHBullet::IsOutofScreen()
{
	if (shape == nullptr) return false;

	const float width = shape->GetImage()->GetWidth() * 2;
	const float height = shape->GetImage()->GetHeight() * 2;

	const float right = position.x - width;
	const float left = position.x + width;
	const float top = position.y + height;
	const float bottom = position.y - height;

	if (right > GAME_RIGHT || left < GAME_LEFT
		|| bottom > GAME_BOTTOM || top < GAME_TOP)
		return true;

	return false;
}