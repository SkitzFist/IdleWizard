#ifndef IDLE_WIZARD_SYSTEM_H
#define IDLE_WIZARD_SYSTEM_H

/*
  Todo: Split out to their own files.
  Note: Order in the enum is important, as it is the order the system will be executed in.
*/

enum class UpdateSystemType{
  VELOCITY_MOVE,
  COUNT
};

enum class RenderSystemType{
  BLOB,
  COUNT
};

class System{
public:
  virtual ~System() = default;
};

class UpdateSystem : public System{
public:
    virtual void run(const float dt) = 0;
};

class RenderSystem : public System{
public:
  virtual void run() const = 0;
};

#endif
