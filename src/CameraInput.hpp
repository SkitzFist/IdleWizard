#ifndef IDLE_MINER_CAMERA_INPUT
#define IDLE_MINER_CAMERA_INPUT

#include "raylib.h"

class CameraInput {
  public:
    CameraInput();
    void handleInput(Camera2D &camera);

  private:
    const int m_speed;
    const int m_minSpeed;
    const int m_maxSpeed;
    const float m_maxZoom;
    const float m_minZoom;

    void handleZoom(Camera2D &camera);
    void moveTowardsMouse(Camera2D &camera);
    void handleMovement(Camera2D &camera);
};

#endif