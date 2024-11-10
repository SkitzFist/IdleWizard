#include "Worlds.h"
#include "MathHack.hpp"

Worlds createWorlds(int columns, int rows, float width, float height) {
    Worlds worlds;

    worlds.columns = columns;
    worlds.rows = rows;
    worlds.width = width;
    worlds.height = height;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            float posX = x * width;
            float posY = y * height;
            worlds.positions.push_back({posX, posY});
        }
    }

    return worlds;
}

void split(Worlds& worlds, EcsManager& ecs) {
    const bool splitWidth = worlds.columns <= worlds.rows;

    bool wasSplit = false;
    if (splitWidth && worlds.columns < MAX_COLUMNS) {
        worlds.columns *= 2;
        worlds.width /= 2.f;
        wasSplit = true;
    } else if (!splitWidth && worlds.rows < MAX_ROWS) {
        worlds.rows *= 2;
        worlds.height /= 2.f;
        wasSplit = true;
    }

    if (wasSplit) {
        // clear world positions
        worlds.positions.clear();
        for (int i = 0; i < worlds.columns * worlds.rows; ++i) {
            worlds.positions.push_back({0.f, 0.f});
        }
        worlds.isInTransition = true;
        worlds.transitionTimer.begin();

        // shrink sizes
        if (!splitWidth) {
            Component& sizes = ecs.components[ComponentType::SIZE];
            for (size_t i = 0; i < sizes.getSize(); ++i) {
                int entityId = sizes[i];
                if (ecs.hasComponent(entityId, ComponentType::WORLD_POSITION)) {
                    Vector2& size = sizes.get<Vector2>(i);
                    size.x /= 2.f;
                    size.y /= 2.f;
                }
            }
        }

        // copy entities
        Component& worldIndexes = ecs.components[ComponentType::WORLD_INDEX];
        std::vector<int> entitiesToCopy;
        entitiesToCopy.reserve(worldIndexes.getSize());
        for (size_t i = 0; i < worldIndexes.getSize(); ++i) {
            entitiesToCopy.emplace_back(worldIndexes[i]);
        }

        for (const int entityId : entitiesToCopy) {
            int newId = ecs.copyEntity(entityId);
            int& newWorldIndex = worldIndexes.getFromId<int>(newId);
            int increment = (worlds.columns * worlds.rows) / 2;
            newWorldIndex += increment;
        }
    }
}

void grow(Worlds& worlds, EcsManager& ecs) {
    const bool growWidth = worlds.columns >= worlds.rows;

    bool wasGrown = false;

    if (growWidth && worlds.columns > 1) {
        worlds.columns /= 2;
        worlds.width *= 2.f;
        wasGrown = true;
    } else if (!growWidth && worlds.rows > 1) {
        worlds.rows /= 2;
        worlds.height *= 2.f;
        wasGrown = true;
    }

    if (wasGrown) {
        // clear world positions
        worlds.positions.clear();
        for (int i = 0; i < worlds.columns * worlds.rows; ++i) {
            worlds.positions.push_back({0.f, 0.f});
        }
        worlds.isInTransition = true;
        worlds.transitionTimer.begin();

        // grow entity Sizes
        if (!growWidth) {
            Component& sizes = ecs.components[ComponentType::SIZE];
            for (size_t i = 0; i < sizes.getSize(); ++i) {
                int entityId = sizes[i];
                if (ecs.hasComponent(entityId, ComponentType::WORLD_POSITION)) {
                    Vector2& size = sizes.get<Vector2>(i);
                    size.x *= 2.f;
                    size.y *= 2.f;
                }
            }
        }

        // TODO this is super un-optimized
        int maxIndex = worlds.positions.size() - 1;
        Component& worldIndexes = ecs.components[ComponentType::WORLD_INDEX];
        bool isDone = true;
        int index = 0;
        while (!isDone || index < worldIndexes.getSize()) {
            isDone = true;
            if (worldIndexes.get<int>(index) > maxIndex) {
                ecs.removeEntity(worldIndexes[index]);
                isDone = false;
                index = 0;
            }

            ++index;
        }
    }
}

// todo move out to its own class and file
float lerp(float min, float max, float t) {
    return min + (max - min) * t;
}

void transition(Worlds& worlds) {
    const double duration = 750;
    if (worlds.isInTransition && worlds.transitionTimer.getDuration() < duration) {
        Vector2 target, start;
        for (int y = 0; y < worlds.rows; ++y) {
            for (int x = 0; x < worlds.columns; ++x) {
                Vector2& current = worlds.positions[y * worlds.columns + x];

                start = {GetScreenWidth() / 2.f - (worlds.width / 2.f), GetScreenHeight() / 2.f - (worlds.height / 2.f)};
                target = {x * worlds.width, y * worlds.height};

                current.x = lerp(start.x, target.x, worlds.transitionTimer.getDuration() / duration);
                current.y = lerp(start.y, target.y, worlds.transitionTimer.getDuration() / duration);
            }
        }

        worlds.isInTransition = worlds.transitionTimer.getDuration() < duration;
    }
}
