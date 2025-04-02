﻿#pragma once
#include "config.h"
#include "ObjectPool.h"

class BulletShooter;
class BHBullet;

class BulletManager
{
private:
    // ObjectPool<BHBullet>* bulletPool;
    BulletShooter* bulletShooter;
public:
    void Init(int capacity = 1024);
    void Release();
    void Update(float dt);
    void Render(HDC hdc);

    void ChangeBulletShooter(BulletShooter* newShooter);
    void AddBullet(FPOINT pos, float angle, float angle_rate, float shoot_speed, float shoot_speed_rate);
};
