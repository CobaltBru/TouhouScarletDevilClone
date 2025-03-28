#pragma once
#include "BHObject.h"
#include "config.h"

class BHBullet : public BHObject
{
protected:

	// angluar accel
	float AngleRate;
	// accel
	float SpeedRate;
	float movementSpeed;
public:
	void Init(Image* image, float hit, FPOINT position, float radianAngle) override;

	void Init(Image* image, float hit, FPOINT position, float radianAngle, float angleRate, float speedRate, float movementSpeed);
	

	// BHObject을(를) 통해 상속됨
	void Update() override;
	void Render(HDC hdc) override;
};

