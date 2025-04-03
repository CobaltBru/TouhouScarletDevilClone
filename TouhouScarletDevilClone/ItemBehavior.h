#pragma once

class GameState;
class ItemBehavior
{
public:
	virtual ~ItemBehavior() = default;
	virtual void OnCollect(GameState* state) = 0;
};

