#pragma once
#include "BHObject.h"
#include "BHItem.h"

class EnemyController;
class BulletManager;
class D2DImage;
class BHEnemy : public BHObject
{
private:
    int frameIndex;
    float timeElapsed;
    float shootDelay;

    int tempLevel;
    D2DImage* moveImage;
    FPOINT moveDir;

    EnemyController* ec;

    // ������ ���� �ڵ�
    vector<BHItem*>* items = nullptr;
	GameState* gameState = nullptr;

public:
    // ������
    BHEnemy() = default;
    virtual ~BHEnemy () = default;

    inline void SetMoveImage(D2DImage* moveImage) { this->moveImage = moveImage; }

    void Init(string shapeKey, FPOINT pos) override;
    virtual void Init(string shapeKey, FPOINT pos, std::vector<IObjectActionPattern*> patterns);
    
    void Move(float angle, float speed, float dt) override;
    
    void Render(HDC hdc) override;

    void Update(float dt) override;
    void MoveBackToBorder();

    void Shoot(string bulletShapeKey, FPOINT init_pos, float angle, float angleRate, float shootSpeed, float shootSpeedRate) override;

    void OnHit(ICollideable* hitObject) override;

    void Release() override;


    virtual void GetDamaged(int damage);

    // ������ ���� �ڵ�
	inline void SetItemList(vector<BHItem*>& itemList) { items = &itemList; }
	inline void SetGameState(GameState* state) { gameState = state; }
};

