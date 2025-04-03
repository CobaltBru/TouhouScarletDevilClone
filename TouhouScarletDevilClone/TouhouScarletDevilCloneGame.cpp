﻿#include "TouhouScarletDevilCloneGame.h"
#include "UI.h"
#include "BHEnemy.h"
#include "BHPlayer.h"
#include "BHItem.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "ImageManager.h"
#include "BHObjectManager.h"
#include "GameState.h"
#include "Shape.h"


void TouhouScarletDevilCloneGame::Init()
{
    bgImage = ImageManager::GetInstance()->AddImage("bgImage", TEXT("Image/backGround.bmp"));
	
    gameState = new GameState();
    ui = new UI(gameState);

    player = BHObjectManager::GetInstance()->GetPlayer();
    player->Init("Marisa", {GAME_CENTER_X, GAME_CENTER_Y});
    D2DImage* moveImage = ImageManager::GetInstance()->AddImage("Marisa_Move_Left", TEXT("Image/Marisa_Move_Left.bmp"), 8, 1);
    player->SetMoveImage(moveImage);
    
    stageWaveManager.Init();
}

void TouhouScarletDevilCloneGame::Release(){}


void TouhouScarletDevilCloneGame::Update(float dt)
{
    if (player) player->Update(dt);

    stageWaveManager.Update(dt);

    BHObjectManager::GetInstance()->Update(dt);
    
    CircleCollisionManager::GetInstance()->Update();
}

void TouhouScarletDevilCloneGame::Render(HDC hdc)
{
    if (bgImage) bgImage->Render(-350,-560);

    if (player) player->Render(hdc);
    

    BHObjectManager::GetInstance()->Render();
    
    CircleCollisionManager::GetInstance()->Render(hdc);
}
