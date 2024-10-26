#ifndef IDLE_WIZARD_ENTITY_TYPES_H
#define IDLE_WIZARD_ENTITY_TYPES_H

#include <string>

enum class EntityType {
    BLOB,
    WIZARD,
    MANA_ALTAR,
    COUNT
};

inline const std::string toString(const EntityType type) {
    switch (type) {
    case EntityType::BLOB:
        return "Blob";
    case EntityType::WIZARD:
        return "Wizard";
    case EntityType::MANA_ALTAR:
        return "Mana altar";
    default:
        return "None";
    }
}
#endif
    