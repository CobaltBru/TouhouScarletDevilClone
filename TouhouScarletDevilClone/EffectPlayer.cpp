#include "EffectPlayer.h"
#include "D2DImage.h"

void EffectPlayer::Init(int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		Effect* e = new Effect;
		freeEffects.push_back(e);
	}
	D2DImage* image[4];
	//Hit_red
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("Hit_red_1", TEXT("Image/Hit/Hit_red_1.png"));
		image[1] = ImageManager::GetInstance()->AddImage("Hit_red_2", TEXT("Image/Hit/Hit_red_2.png"));
		image[2] = ImageManager::GetInstance()->AddImage("Hit_red_3", TEXT("Image/Hit/Hit_red_3.png"));
		image[3] = ImageManager::GetInstance()->AddImage("Hit_red_4", TEXT("Image/Hit/Hit_red_4.png"));
		for (int i = 0; i < 10; i++)
		{
			EffectTask task;
			float tangle = rand() % 360;
			float tspeed = rand() % 5 + 5;
			float tstart = ((float)(rand() % 100)) / 100;
			int imageIdx = rand() % 4;
			task.setOffset({ (float)(rand() % 10),(float)(rand() % 10) });
			task.Init(image[imageIdx], tstart, tstart + 0.8f);
			task.setFade(0.3f, 0.05f);
			task.setZoom(4.f, 2.f);
			task.setMove(tangle, tspeed, 2.0f);
			effect->pushEffectTask(task);
		}
		AddEffect("Hit_red", effect);
	}
	//Hit_white
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("Hit_white_1", TEXT("Image/Hit/Hit_red_1.png"));
		image[1] = ImageManager::GetInstance()->AddImage("Hit_white_2", TEXT("Image/Hit/Hit_white_2.png"));
		image[2] = ImageManager::GetInstance()->AddImage("Hit_white_3", TEXT("Image/Hit/Hit_white_3.png"));
		image[3] = ImageManager::GetInstance()->AddImage("Hit_white_4", TEXT("Image/Hit/Hit_white_4.png"));
		for (int i = 0; i < 10; i++)
		{
			EffectTask task;
			float tangle = rand() % 360;
			float tspeed = rand() % 5 + 5;
			float tstart = ((float)(rand() % 100)) / 100;
			int imageIdx = rand() % 4;
			task.setOffset({ (float)(rand() % 10),(float)(rand() % 10) });
			task.Init(image[imageIdx], tstart, tstart + 0.8f);
			task.setFade(0.3f, 0.05f);
			task.setZoom(4.f, 2.f);
			task.setMove(tangle, tspeed, 2.0f);
			effect->pushEffectTask(task);
		}
		AddEffect("Hit_white", effect);
	}
	//Hit_green
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("Hit_green_1", TEXT("Image/Hit/Hit_green_1.png"));
		image[1] = ImageManager::GetInstance()->AddImage("Hit_green_2", TEXT("Image/Hit/Hit_green_2.png"));
		image[2] = ImageManager::GetInstance()->AddImage("Hit_green_3", TEXT("Image/Hit/Hit_green_3.png"));
		image[3] = ImageManager::GetInstance()->AddImage("Hit_green_4", TEXT("Image/Hit/Hit_green_4.png"));
		for (int i = 0; i < 10; i++)
		{
			EffectTask task;
			float tangle = rand() % 360;
			float tspeed = rand() % 5 + 5;
			float tstart = ((float)(rand() % 100)) / 100;
			int imageIdx = rand() % 4;
			task.setOffset({ (float)(rand() % 10),(float)(rand() % 10) });
			task.Init(image[imageIdx], tstart, tstart + 0.8f);
			task.setFade(0.3f, 0.05f);
			task.setZoom(4.f, 2.f);
			task.setMove(tangle, tspeed, 2.0f);
			effect->pushEffectTask(task);
		}
		AddEffect("Hit_green", effect);
	}
	//Hit_blue
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("Hit_blue_1", TEXT("Image/Hit/Hit_blue_1.png"));
		image[1] = ImageManager::GetInstance()->AddImage("Hit_blue_2", TEXT("Image/Hit/Hit_blue_2.png"));
		image[2] = ImageManager::GetInstance()->AddImage("Hit_blue_3", TEXT("Image/Hit/Hit_blue_3.png"));
		image[3] = ImageManager::GetInstance()->AddImage("Hit_blue_4", TEXT("Image/Hit/Hit_blue_4.png"));
		for (int i = 0; i < 10; i++)
		{
			EffectTask task;
			float tangle = rand() % 360;
			float tspeed = rand() % 5 + 5;
			float tstart = ((float)(rand() % 100)) / 100;
			int imageIdx = rand() % 4;
			task.setOffset({ (float)(rand() % 10),(float)(rand() % 10) });
			task.Init(image[imageIdx], tstart, tstart + 0.8f);
			task.setFade(0.3f, 0.05f);
			task.setZoom(4.f, 2.f);
			task.setMove(tangle, tspeed, 2.0f);
			effect->pushEffectTask(task);
		}
		AddEffect("Hit_blue", effect);
	}
	//Kill
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("Kill", TEXT("Image/Hit/Kill.png"));
		EffectTask task;
		task.Init(image[0], 0, 0.2f);
		task.setFade(0.5f, 0.05f);
		task.setZoom(0.5f, 1.f);
		effect->pushEffectTask(task);
		AddEffect("Kill", effect);
	}
	//MagicCircle
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("MagicCircle", TEXT("Image/Effect/MagicCircle.png"));
		EffectTask task;
		task.Init(image[0], 0, 0.2f);
		task.setFade(0.5f, 0.8f);
		task.setZoom(0.8f, 1.f);
		task.setSpin(10.f);
		effect->pushEffectTask(task);
		AddEffect("MagicCircle", effect);
	}
	//NormalShoot_green
	{
		Effect* effect = new Effect;
		image[0] = ImageManager::GetInstance()->AddImage("NormalShoot_green", TEXT("Image/Effect/NormalShoot/NormalShoot_green.png"));
		EffectTask task;
		task.Init(image[0], 0, 0.2f);
		task.setFade(0.8f, 1.0f);
		task.setZoom(1.5f, 1.0f);
		effect->pushEffectTask(task);
		EffectTask task1;
		task1.Init(image[0], 0.2, 0.3f);
		task1.setFade(1.f, 0.5f);
		task1.setZoom(1.5f, 1.0f);
		effect->pushEffectTask(task1);
		AddEffect("NormalShoot_green", effect);
	}
}


void EffectPlayer::PlayEffect(string key, FPOINT pos)
{
	if (!freeEffects.empty())
	{
		Effect* effect = freeEffects.front();
		freeEffects.pop_front();
		effect->Clone(FindEffect(key));
		effect->On(pos);
		activeEffects.push_back(effect);
	}
}
void EffectPlayer::AddEffect(string key, Effect* effect)
{
	mapEffects.insert(make_pair(key, effect));
}
Effect* EffectPlayer::FindEffectAdd(string key)
{
	map<string, Effect*>::iterator iter;
	iter = mapEffects.find(key);

	if (iter == mapEffects.end()) return nullptr;

	return iter->second;
}
Effect* EffectPlayer::FindEffect(string key)
{
	map<string, Effect*>::iterator iter;
	iter = mapEffects.find(key);

	if (iter == mapEffects.end()) return mapEffects["Error"];

	return iter->second;
}
void EffectPlayer::Update(float dt)
{
	for (auto iter = activeEffects.begin(); iter != activeEffects.end(); )
	{
		if ((*iter)->currentTime >= (*iter)->endTime)
		{
			(*iter)->Off();
			(*iter)->tasks.clear();
			freeEffects.push_back(*iter);
			iter = activeEffects.erase(iter); 
		}
		else
		{
			(*iter)->Update(dt);
			++iter;
		}
	}
}

void EffectPlayer::Render()
{
	for (auto iter = activeEffects.begin(); iter != activeEffects.end(); iter++)
	{
		(*iter)->Render();
	}
}

void EffectPlayer::Release()
{
	for (auto& e : activeEffects)
	{
		delete e;
	}
	for (auto& e : freeEffects)
	{
		delete e;
	}
	activeEffects.clear();
	freeEffects.clear();
	for (auto iter = mapEffects.begin(); iter != mapEffects.end(); iter++)
	{
		Effect* effect = iter->second;
		delete effect;
		effect = nullptr;
	}
	mapEffects.clear();
}



void Effect::Update(float dt)
{
	currentTime += dt;
	for (auto& task : tasks)
	{
		task.Update(currentTime);
	}
}

void Effect::Render()
{
	for (auto& task : tasks)
	{
		task.Render(pos);
	}
}

void Effect::pushEffectTask(EffectTask effectTask)
{
	tasks.push_back(effectTask);
	endTime = max(endTime, effectTask.endTime);
}

void Effect::Clone(Effect* from)
{
	this->tasks = from->tasks;
	this->pos = from->pos;
	this->currentTime = 0;
	this->endTime = from->endTime;
}



void EffectTask::Init(D2DImage* image, float startTime, float endTime, FPOINT offset,
	float angle, float alpha, FPOINT scale)
{
	this->image = image;
	this->offset = offset;
	this->startTime = startTime;
	this->endTime = endTime;
	this->image_angle = angle;
	this->image_alpha = alpha;
	this->image_scale = scale;
}

void EffectTask::Update(float time)
{
	if (fadeFlag)
	{
		image_alpha = calcAlpha(time);
	}
	if (rollFlag)
	{
		image_angle = calcAngle(time);
	}
	if (spinFlag)
	{
		makeSpin(image_angle);
	}
	if (zoomFlag)
	{
		float zoom = calcZoom(time);
		image_scale.x = zoom;
		image_scale.y = zoom;
	}
	if (moveFlag)
	{
		offset = calcMove(time);
	}
}
void EffectTask::Render(FPOINT pos)
{
	image->Middle_RenderFrameScale(
		pos.x + offset.x, pos.y + offset.y,
		image_scale.x, image_scale.y, 0,
		image_angle,
		false, false, 
		image_alpha);
}

float EffectTask::calcAlpha(float time)
{
	if (time <= startTime) return startAlpha;
	else if (time >= endTime) return endAlpha;
	float percent = (time - startTime) / (endTime - startTime);
	float alpha = (endAlpha - startAlpha) * percent + startAlpha;
	return alpha;
}

float EffectTask::calcAngle(float time)
{
	if (time <= startTime) return startAngle;
	else if (time >= endTime) return endAngle;
	float percent = (time - startTime) / (endTime - startTime);
	float angle = (endAngle - startAngle) * percent + startAngle;
	if (angle <= 0)angle += 360;
	else if (angle >= 360)angle -= 360;
	return angle;
}

float EffectTask::calcZoom(float time)
{
	if (time <= startTime) return startZoom;
	else if (time >= endTime) return endZoom;
	float percent = (time - startTime) / (endTime - startTime);
	float zoom = (endZoom - startZoom) * percent + startZoom;
	return zoom;
}

void EffectTask::makeSpin(float& angle)
{
	float tangle = angle;
	tangle += spinSpeed;
	if (tangle <= 0)tangle += 360;
	else if (tangle >= 360)tangle -= 360;
	angle = tangle;
}

FPOINT EffectTask::calcMove(float time)
{
	// 아직 시작 전이면 시작 좌표 그대로 반환
	if (time < startTime)
		return offset;

	// 종료 후라면, t를 endTime - startTime으로 고정
	float dt = (time > endTime) ? (endTime - startTime) : (time - startTime);

	// 이동 거리 계산 (등가속도 운동 공식)
	float distance = move_speed * dt + 0.5f * move_speedRate * dt * dt;

	// x, y 이동량 계산
	float dx = distance * cosf(DEG_TO_RAD(move_angle));
	float dy = distance * sinf(DEG_TO_RAD(move_angle));

	return { offset.x + dx ,offset.y + dy };
}

void EffectTask::setOffset(FPOINT offset)
{
	this->offset = offset;
}

void EffectTask::setFade(float startAlpha, float endAlpha)
{
	fadeFlag = true;
	image_alpha = startAlpha;
	this->startAlpha = startAlpha;
	this->endAlpha = endAlpha;
}

void EffectTask::setRoll(float startAngle, float endAngle)
{
	rollFlag = true;
	image_angle = startAngle;
	this->startAngle = startAngle;
	this->endAngle = endAngle;
}

void EffectTask::setSpin(float speed)
{
	spinFlag = true;
	spinSpeed = speed;
}

void EffectTask::setZoom(float startSize, float endSize)
{
	zoomFlag = true;
	image_scale.x = startSize;
	image_scale.y = startSize;
	this->startZoom = startSize;
	this->endZoom = endSize;
}

void EffectTask::setMove(float angle, float speed, float speedRate)
{
	moveFlag = true;
	this->move_angle = angle;
	this->move_speed = speed;
	this->move_speedRate = speedRate;
}


