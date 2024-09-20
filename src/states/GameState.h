#ifndef IDLE_WIZARD_GAME_STATE_H_
#define IDLE_WIZARD_GAME_STATE_H_

class GameState {
  public:
    virtual ~GameState() {}
    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void render() const = 0;
};

#endif
