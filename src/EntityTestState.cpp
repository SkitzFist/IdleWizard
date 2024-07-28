#include "EntityTestState.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

struct BigStrength {
    float x = 0;
    float y = 0;
    bool alive;
    double strength = 258.23;

    BigStrength(bool alive, double strength) : alive(alive), strength(strength) {}
};

struct Big {
    float x = 0;
    float y = 0;
    bool alive;

    Big(bool alive) : alive(alive) {}
};

struct Entity {
    int posIndex;
    int strengthIndex;

    Entity(int posIndex, int strengthIndex) : posIndex(posIndex), strengthIndex(strengthIndex) {}
};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist(0, 1);

double getRandom() {
    return dist(gen);
}

void testBigStrength(int nrOfEntities, int nrOfTests);
void testBig(int nrOfEntities, int nrOfTests);
void testEntity(int nrOfEntities, int nrOfTests);
void testEntityTrue(int nrOfEntities, int nrOfTests);

EntityTestState::EntityTestState() {
    std::cout << "\n----\n";
    std::cout << "Big Strength Size: " << sizeof(BigStrength) << '\n';
    std::cout << "Big Size: " << sizeof(Big) << '\n';
    std::cout << "Entity size: " << sizeof(Entity) << '\n';

    int nrOfEntities = 10000000;
    int nrOfTests = 100;

    std::cout << '\n';
    testBigStrength(nrOfEntities, nrOfTests);
    std::cout << '\n';
    testBig(nrOfEntities, nrOfTests);
    std::cout << '\n';
    testEntity(nrOfEntities, nrOfTests);
    std::cout << '\n';
    testEntityTrue(nrOfEntities, nrOfTests);
}

void testBigStrength(int nrOfEntities, int nrOfTests) {
    std::vector<BigStrength> bigs;
    bigs.reserve(nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        bigs.emplace_back(i % 3 != 0, getRandom());
    }

    double totalDuration = 0.0;
    for (int i = 0; i < nrOfTests; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < nrOfEntities; ++j) {
            if (bigs[j].alive) {
                bigs[j].x += 1;
                bigs[j].y += 1;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        totalDuration += duration.count();
    }

    std::cout << "Big Strength totalSize: " << (sizeof(BigStrength) * nrOfEntities) << '\n';
    std::cout << "Big Strength Totalduration: " << totalDuration << '\n';
    std::cout << "Big Strength Average duration: " << totalDuration / 5 << '\n';
}

void testBig(int nrOfEntities, int nrOfTests) {
    std::vector<Big> bigs;
    bigs.reserve(nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        bigs.emplace_back(i % 3 != 0);
    }

    double totalDuration = 0.0;
    for (int i = 0; i < nrOfTests; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < nrOfEntities; ++j) {
            if (bigs[j].alive) {
                bigs[j].x += 1;
                bigs[j].y += 1;

                double damage = damage * 10;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        totalDuration += duration.count();
    }

    std::cout << "Big totalSize: " << (sizeof(Big) * nrOfEntities) << '\n';
    std::cout << "Big Totalduration: " << totalDuration << '\n';
    std::cout << "Big Average duration: " << totalDuration / 5 << '\n';
}

void testEntity(int nrOfEntities, int nrOfTests) {
    std::vector<Entity> entitiesAlive;
    entitiesAlive.reserve(nrOfEntities);

    std::vector<Entity> entitiesDead;
    entitiesDead.reserve(nrOfEntities);

    std::vector<float> xPositions;
    xPositions.reserve(nrOfEntities);

    std::vector<float> yPositions;
    yPositions.reserve(nrOfEntities);

    std::vector<double> entityStrengths;
    entityStrengths.reserve(nrOfEntities);

    for (int i = 0; i < nrOfEntities; ++i) {
        if (i % 3 == 0) {
            entitiesDead.emplace_back(-1, -1);
        } else {
            xPositions.emplace_back(0);
            yPositions.emplace_back(0);
            int posIndex = xPositions.size() - 1;

            entityStrengths.emplace_back(getRandom());
            int strengthIndex = entityStrengths.size() - 1;

            entitiesAlive.emplace_back(posIndex, strengthIndex);
        }
    }

    double totalDuration = 0.0;
    for (int i = 0; i < nrOfTests; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < entitiesAlive.size(); ++j) {
            int posIndex = entitiesAlive[j].posIndex;
            xPositions[posIndex] += 1;
            yPositions[posIndex] += 1;
            int strengthIndex = entitiesAlive[j].strengthIndex;
            double damage = entityStrengths[strengthIndex] * 10;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        totalDuration += duration.count();
    }

    // std::cout << "Big totalSize: " << sizeof(bigs) << '\n';
    std::cout << "Entity Totalduration: " << totalDuration << '\n';
    std::cout << "Entity Average duration: " << totalDuration / 5 << '\n';
}

void testEntityTrue(int nrOfEntities, int nrOfTests) {
    std::vector<float> xPos, yPos;
    xPos.reserve(nrOfEntities);
    yPos.reserve(nrOfEntities);

    std::vector<double> strengths;
    strengths.reserve(nrOfEntities);

    for (int i = 0; i < nrOfEntities; ++i) {
        if (i % 3 != 0) {
            xPos.emplace_back(0);
            yPos.emplace_back(0);
            strengths.emplace_back(getRandom());
        }
    }

    double totalDuration = 0.0;

    for (int j = 0; j < nrOfTests; ++j) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < xPos.size(); ++i) {
            xPos[i] += 1.f;
            yPos[i] += 1.f;
        }

        for (int i = 0; i < strengths.size(); ++i) {
            double damage = strengths[i] * 10.0;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        totalDuration += duration.count();
    }

    std::cout << "Entity True Totalduration: " << totalDuration << '\n';
    std::cout << "Entity True Average duration: " << totalDuration / 5 << '\n';
}

EntityTestState::~EntityTestState() {
}

void EntityTestState::handleInput() {
}

void EntityTestState::update(float dt) {
}

void EntityTestState::render() const {
}
