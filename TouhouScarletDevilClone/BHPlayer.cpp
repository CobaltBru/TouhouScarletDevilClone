#include "BHPlayer.h"
#include "config.h"
#include "CircleCollisionManager.h"
#include "D2DImage.h"
#include "BHObjectManager.h"
#include "Shape.h"
#include "SoundPlayer.h"
#include "EffectPlayer.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "ShapeManager.h"
#include "BHEnemy.h"

void BHPlayer::Init(string shapeKey, FPOINT pos)
{
    BHObject::Init(shapeKey, pos);

    moveShape = ShapeManager::GetInstance()->FindShape("marisa_left");
    moveStartShape = ShapeManager::GetInstance()->FindShape("marisa_goleft");
    subShape = ShapeManager::GetInstance()->FindShape("marisa_sub");
    
    timeElapsed = 0;
    //TODO: Initialize delay in certain value from parameter

    moveSpeed = 130.f;
    slowSpeed = 60.f;
    lv = 5;
    //΅τ·ΉΐΜ
    mainShootDelay[0] = 0.2f;
    mainShootDelay[1] = 0.2;
    mainShootDelay[2] = 0.2;
    mainShootDelay[3] = 0.15;
    mainShootDelay[4] = 0.15;
    mainShootDelay[5] = 0.15;
    mainShootDelay[6] = 0.15;
    mainShootDelay[7] = 0.15;
    mainShootDelay[8] = 0.15;

    subShootDelay[0] = 0.0f;
    subShootDelay[1] = 0.8f;
    subShootDelay[2] = 0.6f;
    subShootDelay[3] = 0.6;
    subShootDelay[4] = 0.5;
    subShootDelay[5] = 0.5;
    subShootDelay[6] = 0.3;
    subShootDelay[7] = 0.3;
    subShootDelay[8] = 0.3;

    //°ΉΌφ
    mainShootCount[0] = 1;
    mainShootCount[1] = 1;
    mainShootCount[2] = 1;
    mainShootCount[3] = 1;
    mainShootCount[4] = 1;
    mainShootCount[5] = 2;
    mainShootCount[6] = 2;
    mainShootCount[7] = 2;
    mainShootCount[8] = 3;

    subShootCount[0] = 0;
    subShootCount[1] = 1;
    subShootCount[2] = 1;
    subShootCount[3] = 1;
    subShootCount[4] = 1;
    subShootCount[5] = 1;
    subShootCount[6] = 1;
    subShootCount[7] = 2;
    subShootCount[8] = 2;

    spellCardShape = ShapeManager::GetInstance()->FindShape("NormalBullet_blue"); // μμλ‘ μ¬μ©
    
    timeElapsed = 0;
    // λλ μ΄ κ°μ νλΌλ―Έν°λ‘λΆν° μ΄κΈ°ν
    mainShootDelay = 0.6f;
    subShootDelay = 1.2f;

    moveDir = { 0,0 };
    isPreviousStateHorizontalMove = false;
    SetCollisionLayer(LAYER_PLAYER, LAYER_ENEMY_BULLET | LAYER_ITEM);
    
    // νλ μ΄μ΄ μν μ΄κΈ°ν
    isInvincible = false;
    invincibleTimer = 0.0f;
    invincibleDuration = 2.0f;
    lives = 3;
    
    // μ€ν μΉ΄λ(λ΄) μ΄κΈ°ν
    isSpellCardActive = false;
    spellCardTimer = 0.0f;
    spellCardDuration = 5.0f; // 5μ΄ μ§μ
    spellCardCooldown = 30.0f; // 30μ΄ μΏ¨λ€μ΄
    spellCardCooldownTimer = 0.0f;
    spellCardCount = 3; // μ΄κΈ° μ€ν μΉ΄λ 3κ°
    
    // κ²μ μν μ΄κΈ°ν
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->PlayerHp = lives;
        gameState->CurrPowerBarFrame = 0;
        gameState->PowerMultiplier = 1.0f;
        gameState->SpellCardCount = spellCardCount;
    }
}

void BHPlayer::Render(HDC hdc)
{
    // λ¬΄μ  μνμΌ λ κΉλΉ‘μ΄λ ν¨κ³Ό
    if (isInvincible && (int)(invincibleTimer * 10) % 2 == 0 && !isSpellCardActive) {
        return;
    }

    if (abs(moveDir.x) > FLT_EPSILON)
    {
        if (isPreviousStateHorizontalMove)
        {
            if (moveShape)
            {
                moveShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }
        else
        {
            if (frameIndex == 3) isPreviousStateHorizontalMove = true;
            // frameIndex = 0;
            if (moveStartShape)
            {
                moveStartShape->GetImage()->Middle_RenderFrame(position.x, position.y,frameIndex,0, moveDir.x > 0);
            }
        }

    }
    else
    {
        isPreviousStateHorizontalMove = false;
        if (shape && shape->GetImage())
        {
            // νλ μ μΈλ±μ€ λΆλ¦¬
            shape->GetImage()->Middle_RenderFrame(position.x, position.y, frameIndex);
        }
    }

    if (subShape)
    {
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x - 10 : position.x - 30), (isPressingShift ? position.y - 15 : position.y), 1);
        subShape->GetImage()->Middle_RenderFrame((isPressingShift ? position.x + 10 : position.x + 30),(isPressingShift ? position.y - 15 : position.y), 1);
    }
    
    // μ€ν μΉ΄λ νμ±ν μνμΌ λ μΆκ° λ λλ§
    if (isSpellCardActive) {
        RenderSpellCard(hdc);
    }
}

void BHPlayer::Move(FPOINT moveDirection, bool isPressingShift, float dt)
{
    if (abs(moveDirection.x) <= FLT_EPSILON && abs(moveDirection.y) <= FLT_EPSILON)
    {
        return;
    }
    float angle = atan2(moveDirection.x , moveDirection.y);
    
    //TODO: SetSpeed;
    float currentSpeed = isPressingShift ? slowSpeed : moveSpeed;
    position.x += sin(angle) * currentSpeed * dt;
    position.y += cos(angle) * currentSpeed * dt;
}

void BHPlayer::Move(float angle, float speed, float dt)
{
    position.x += sin(angle) * speed * dt;
    position.y += cos(angle) * speed * dt;
}

void BHPlayer::Update(float dt)
{
    mainWeaponTimer += dt;
    subWeaponTimer += dt;
    timeElapsed += dt;

    // λ¬΄μ  μν μλ°μ΄νΈ
    if (isInvincible) {
        invincibleTimer += dt;
        if (invincibleTimer >= invincibleDuration) {
            isInvincible = false;
            invincibleTimer = 0.0f;
        }
    }
    
    // μ€ν μΉ΄λ μΏ¨λ€μ΄ μλ°μ΄νΈ
    if (spellCardCooldownTimer > 0) {
        spellCardCooldownTimer -= dt;
        if (spellCardCooldownTimer < 0) {
            spellCardCooldownTimer = 0;
        }
    }
    
    // μ€ν μΉ΄λ νμ±ν μν μλ°μ΄νΈ
    if (isSpellCardActive) {
        UpdateSpellCard(dt);
    }
    
    // κ²μ μν μλ°μ΄νΈ
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->PlayerHp = lives;
        gameState->SpellCardCount = spellCardCount;
    }
    
#pragma region ARROW_INPUT
    moveDir = { 0,0 };
    // UP
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
    {
        moveDir.y=-1;
    }
    // LEFT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
    {
        moveDir.x=-1;
    }
    // DOWN
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
    {
        moveDir.y=1;
    }
    // RIGHT
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
    {
        moveDir.x=1;
    }
#pragma endregion
    isPressingShift = KeyManager::GetInstance()->IsStayKeyDown(VK_SHIFT);
    
    Move(moveDir, isPressingShift, dt);
    
    MoveBackToBorder();

    if (timeElapsed >= 0.5f)
    {
        frameIndex = frameIndex + 1 >= 4 ? 0 : frameIndex + 1;
        timeElapsed = 0;
    }
    
    // Zν€λ‘ μΌλ° κ³΅κ²©
    if (KeyManager::GetInstance()->IsStayKeyDown(0x5A))
    {
        
        Shoot("marisa_mainbullet", { position.x , position.y - 10 }, DEG_TO_RAD(-90), DEG_TO_RAD(0.f), 600.f, 0.f);
        
        
        ShootSubWeapon(isPressingShift);
    }
    
    // Xν€λ‘ μ€ν μΉ΄λ(λ΄) μ¬μ©
    if (KeyManager::GetInstance()->IsOnceKeyDown(0x58) && !isSpellCardActive && spellCardCooldownTimer <= 0 && spellCardCount > 0)
    {
        ActivateSpellCard();
    }
}

void BHPlayer::OnHit(ICollideable* hitObject)
{
    // λ¬΄μ  μνμΌ λλ μΆ©λ λ¬΄μ
    if (isInvincible || isSpellCardActive) {
        return;
    }
    
    // μΆ©λν κ°μ²΄μ λ μ΄μ΄ νμΈ
    CollisionLayer hitLayer = hitObject->GetLayer();
    
    if (hitLayer & LAYER_ENEMY_BULLET) {
        // μ  μ΄μκ³Ό μΆ©λνμ λ
        lives--;
        
        // νΌκ²© ν¨κ³Όμ μ¬μ
        // SoundPlayer::GetInstance()->SoundOn("player_hit");
        
        // νΌκ²© μ΄ννΈ μ¬μ
        // EffectPlayer::GetInstance()->PlayEffect("hit_effect", position);
        
        // λ¬΄μ  μνλ‘ μ ν
        isInvincible = true;
        invincibleTimer = 0.0f;
        
        // κ²μ μ€λ² μ²΄ν¬
        if (lives <= 0) {
            // κ²μ μ€λ² μ²λ¦¬
            GameState* gameState = GameStateManager::GetInstance()->GetGameState();
            if (gameState) {
                gameState->isGameOver = true;
                gameState->PlayerHp = 0;
                
                // κ²μ μ€λ² ν¨κ³Όμ μ¬μ
                // SoundPlayer::GetInstance()->SoundOn("game_over");
            }
        }
    }
    else if (hitLayer & LAYER_ITEM) {
        // μμ΄νκ³Ό μΆ©λνμ λλ μμ΄νμ OnHitμμ μ²λ¦¬
        // μ¬κΈ°μλ μΆκ° μμ νμ μμ
    }
}

void BHPlayer::Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate)
{
    if (mainWeaponTimer >= mainShootDelay[lv])
    {
        float shootAngle = 0;
        for (int i = 0; i < mainShootCount[lv]; i++)
        {
            BHBullet* bullet = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet->Init(bulletShapeKey, init_pos, true);
            if (mainShootCount[lv] % 2 == 0) shootAngle = -90 + (i - mainShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - mainShootCount[lv] / 2) * 3.0f;
            bullet->Launch(DEG_TO_RAD(shootAngle), angleRate, shootSpeed, shootSpeedRate);
        }
        mainWeaponTimer = 0.f;
        
        // λ°μ¬ ν¨κ³Όμ μ¬μ
        // SoundPlayer::GetInstance()->SoundOn("player_shoot");
    }
}

void BHPlayer::ShootSubWeapon(bool isAccumulating)
{
    if (subWeaponTimer >= subShootDelay[lv])
    {

        float shootAngle = 0;
        for (int i = 0; i < subShootCount[lv]; i++)
        {
            if (subShootCount[lv] % 2 == 0) shootAngle = -90 + (i - subShootCount[lv] / 2 + 0.5f) * 3.0f;
            else shootAngle = -90 + (i - subShootCount[lv] / 2) * 3.0f;
            BHBullet* bullet1 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet1->Init("marisa_subbullet", { isAccumulating ? position.x - 10 : position.x - 30,isAccumulating ? position.y - 15 : position.y }, true);
            bullet1->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            BHBullet* bullet2 = BHObjectManager::GetInstance()->GetPlayerBulletPool()->Allocate();
            bullet2->Init("marisa_subbullet", { isAccumulating ? position.x + 10 : position.x + 30,isAccumulating ? position.y - 15 : position.y }, true);
            bullet2->Launch(DEG_TO_RAD(shootAngle), DEG_TO_RAD(0.f), 500.f, 0.f);
            subWeaponTimer = 0.f;
        }
        
    }
}

void BHPlayer::MoveBackToBorder() {
    if (shape == nullptr) return;

    const float width = shape->GetImage()->GetWidth() / shape->GetImage()->GetMaxFrameX();
    const float height = shape->GetImage()->GetHeight() / shape->GetImage()->GetMaxFrameY();

    const float right = position.x + width / 2;
    const float left = position.x - width / 2;
    const float top = position.y - height / 2;
    const float bottom = position.y + height / 2;

    if (left < GAME_LEFT) position.x = GAME_LEFT + width / 2;
    if (right > GAME_RIGHT) position.x = GAME_RIGHT - width / 2;
    if (top < GAME_TOP) position.y = GAME_TOP + height / 2;
    if (bottom > GAME_BOTTOM) position.y = GAME_BOTTOM - height / 2;
}

// μ€ν μΉ΄λ(λ΄) νμ±ν
void BHPlayer::ActivateSpellCard()
{
    if (spellCardCount <= 0) return;
    
    isSpellCardActive = true;
    spellCardTimer = 0.0f;
    spellCardCount--;
    
    // μ€ν μΉ΄λ μ¬μ© ν¨κ³Όμ μ¬μ
    // SoundPlayer::GetInstance()->SoundOn("spell_card_declare");
    
    // μ€ν μΉ΄λ μ΄ννΈ μ¬μ
    // EffectPlayer::GetInstance()->PlayEffect("spell_card_effect", position);
    
    // νλ©΄μ λͺ¨λ  μ  νλ§ μ κ±°
    ClearEnemyBullets();
    
    // λ¬΄μ  μνλ‘ μ ν
    isInvincible = true;
    invincibleTimer = 0.0f;
    
    // κ²μ μν μλ°μ΄νΈ
    GameState* gameState = GameStateManager::GetInstance()->GetGameState();
    if (gameState) {
        gameState->SpellCardCount = spellCardCount;
    }
}

// μ€ν μΉ΄λ μν μλ°μ΄νΈ
void BHPlayer::UpdateSpellCard(float dt)
{
    spellCardTimer += dt;
    
    // μ£Όλ³ μ μκ² λ°λ―Έμ§
    DamageNearbyEnemies(dt);
    
    // μ§μ μκ°μ΄ λλλ©΄ λΉνμ±ν
    if (spellCardTimer >= spellCardDuration) {
        isSpellCardActive = false;
        isInvincible = false;
        invincibleTimer = 0.0f;
        
        // μΏ¨λ€μ΄ μμ
        spellCardCooldownTimer = spellCardCooldown;
    }
}

// μ€ν μΉ΄λ λ λλ§
void BHPlayer::RenderSpellCard(HDC hdc)
{
    // μ€ν μΉ΄λ μ΄ννΈ λ λλ§ (μν νλ ν¨κ³Ό)
    if (spellCardShape && spellCardShape->GetImage()) {
        float scale = 1.0f + spellCardTimer * 5.0f; // μκ°μ λ°λΌ νμ₯
        float alpha = 1.0f - (spellCardTimer / spellCardDuration); // μκ°μ λ°λΌ ν¬λͺν΄μ§
        
        // μν μ΄ννΈ λ λλ§
        spellCardShape->GetImage()->Middle_Render(position.x, position.y, scale, scale, alpha);
    }
}

// μ  νλ§ μ κ±°
void BHPlayer::ClearEnemyBullets()
{
    // νλ©΄μ λͺ¨λ  μ  νλ§ μ κ±°
    BHObjectManager::GetInstance()->ClearEnemyBullets();
    
    // νλ§ μ κ±° ν¨κ³Όμ μ¬μ
    // SoundPlayer::GetInstance()->SoundOn("bullet_clear");
    
    // νλ§ μ κ±° μ΄ννΈ μ¬μ
    // EffectPlayer::GetInstance()->PlayEffect("bullet_clear_effect", position);
}

// μ£Όλ³ μ μκ² λ°λ―Έμ§
void BHPlayer::DamageNearbyEnemies(float dt)
{
    // νλ©΄μ λͺ¨λ  μ μκ² λ°λ―Έμ§
    vector<BHEnemy*>& enemies = BHObjectManager::GetInstance()->GetEnemyPool()->GetActive();
    for (auto enemy : enemies) {
        if (enemy && enemy->IsValid()) {
            // λ³΄μ€λ μ΄λΉ 10 λ°λ―Έμ§, μΌλ° μ μ μ΄λΉ 20 λ°λ―Έμ§
            int damage = dynamic_cast<BHBoss*>(enemy) ? 10 * dt : 20 * dt;
            enemy->GetDamaged(damage);
            
            // λ°λ―Έμ§ μ΄ννΈ μ¬μ (κ°νμ μΌλ‘)
            if ((int)(spellCardTimer * 5) % 2 == 0) {
                // EffectPlayer::GetInstance()->PlayEffect("damage_effect", *enemy->GetPos());
            }
        }
    }
}

void BHPlayer::Release()
{
    // if (bulletManager)
    // {
    //     bulletManager->Release();
    //     delete bulletManager;
    // }
}


void BHPlayer::setLV(int power)
{
    if (power == 128) lv = 8;
    else if (power >= 96) lv = 7;
    else if (power >= 80) lv = 6;
    else if (power >= 64) lv = 5;
    else if (power >= 48) lv = 4;
    else if (power >= 32) lv = 3;
    else if (power >= 16) lv = 2;
    else if (power >= 8) lv = 1;
    else lv = 0;
}
