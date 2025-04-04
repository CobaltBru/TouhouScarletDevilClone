#pragma once
#include "GameObject.h"

// ���߿� �߰� ����, ���� ���� ���� �Ҷ� ������ ������ �̸� �ص�
enum class BossPhaseType
{
	None,
	MidBoss,
	FinalBoss
};

class D2DImage;
class Timer;
class GameState;
class InGame
{
private:
	FPOINT pos;

	Timer* timer;

	vector<POINT> BackGroubdTile;
	D2DImage* BackGround_Image;
	D2DImage* BackGround;
	bool isBgReder;

	GameState* gameState = nullptr;



	FPOINT StagePos{ WINSIZE_X - 850, WINSIZE_Y - 620 };	// �������� ��ġ
	D2DImage* Stage;

	// ���� �̹����� ���� ��
	vector<string> numberImageKeys;

	FPOINT MaxScorePos{ WINSIZE_X - 370, WINSIZE_Y - 600 };	// �ִ� ���� ��ġ
	D2DImage* MaxScoreImage;

	FPOINT ScorePos{ WINSIZE_X - 355, WINSIZE_Y - 560 };	// ���� ��ġ
	D2DImage* ScoreImage;

	FPOINT PlayerHpPos{ WINSIZE_X - 370, WINSIZE_Y - 500 };	// �÷��̾� ü�� ��ġ
	D2DImage* PlayerHpBarImage;

	D2DImage* PlayerHpImage;

	FPOINT BombPos{ WINSIZE_X - 370, WINSIZE_Y - 455 };	// ��ź ��ġ
	D2DImage* BombImage;

	static const int MaxHpAndBomb = 8;

	FPOINT PowerPos{ WINSIZE_X - 370, WINSIZE_Y - 380 };	// �Ŀ� ��ġ
	int elapPowerbarFrame;
	D2DImage* PowerImage;
	D2DImage* PowerBarImage;
	D2DImage* PowerMaxImage;
	D2DImage* PowerBarBuffer = nullptr;
	int prevPowerbarFrame = -1;

	FPOINT GrazePos{ WINSIZE_X - 370, WINSIZE_Y - 330 };	// �׷����� ��ġ
	D2DImage* GrazeImage;

	// ���� �����ϸ� ��Ÿ���� �͵�
	FPOINT EnemyPhasePos{ StagePos.x - 5, StagePos.y + 5 };	// �� ���� ��ġ
	D2DImage* EnemyPhaseImage;
	D2DImage* BossHpBarImage;
	D2DImage* BossHpBarBuffer = nullptr;
	int prevBossHpBarFrame = -1;

	// Ÿ�̸� ����(���� ���� ��, isEnemyPhase�� true�� �Ǹ� ī��Ʈ ����)
	float elapsedTime = 0.0f;

	// �ٹ̱�
	FPOINT circlePos{ WINSIZE_X - 330, WINSIZE_Y - 350 };
	D2DImage* circle;

	// fps ǥ��
	FPOINT FPSPos{ WINSIZE_X - 200, WINSIZE_Y - 100 };
	D2DImage* FPSImage;
	

public:
	InGame(GameState* state);
	virtual ~InGame();


	void Update(float dt);
	void Render(HDC hdc);
	void ReLoadScore();
	void ReLoadStar();
	void RenderScoreAsImage(HDC hdc, int number, FPOINT startPos);
	void RenderHpAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderBombAsImage(HDC hdc, int number, FPOINT Pos);
	void UpdatePowerBarMax(HDC hdc, FPOINT pos);

	//void RenderPowerBarAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderEnemyPhase(HDC hdc);
	//void RenderBossHpBar(HDC hdc, int number, FPOINT Pos);
	void RenderTimerAsImage(HDC hdc, int number, FPOINT Pos);
	void RenderFPSAsImage(HDC hdc, unsigned long fps, FPOINT Pos);


	inline void SetTimer(Timer* t) { timer = t; }


};

