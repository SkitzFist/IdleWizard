#ifndef IDLE_MINER_ENTITY_TEST_STATE_H_
#define IDLE_MINER_ENTITY_TEST_STATE_H_

#include "GameOptions.h"
#include "GameState.h"

class EntityTestState : public GameState {
  public:
    EntityTestState();
    virtual ~EntityTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
};

#endif