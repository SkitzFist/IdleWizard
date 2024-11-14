#ifndef IDLE_WIZARD_SYSTEM_MONITOR_PRESENTER_H
#define IDLE_WIZARD_SYSTEM_MONITOR_PRESENTER_H

#include "GameOptions.h"
#include "System.h"
#include "Systems.h"

class SystemMonitorUi : public UiSystem {

  public:
    SystemMonitorUi(const GameOptions& gameOptions, Systems& systems);
    virtual ~SystemMonitorUi() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    const GameOptions& m_gameOptions;
    Systems& m_systems;
    bool m_isEnabled;
};

#endif
