#ifndef TESTS_COMPONENT_TESTING_HPP
#define TESTS_COMPONENT_TESTING_HPP

#include "Timer.h"
#include <iostream>

// base component
#include "BaseComponent.h"

// pure component
#include "VectorComponent.h"

// memComponent
#include "Component.h"
#include "ComponentUtils.h"

inline void
baseVsPure() {

    std::cout << "\n\n";
    int nrOfEntities = 1000000;
    Timer timer;

    ////////////////////////////////////////////////////////////////////////////
    ///               init test
    ////////////////////////////////////////////////////////////////////////////
    // base Component init
    timer.begin();
    Vector2Component baseComponent;
    baseComponent.reserve(nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        baseComponent.add(i, (float)GetRandomValue(0, 10), (float)GetRandomValue(0, 10));
    }
    std::cout << "baseComponent init: " << timer.getDuration() << '\n';

    // pure Component init
    timer.begin();
    VectorComponent pureComponent;
    pureComponent.reserve(nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        pureComponent.add(i, (float)GetRandomValue(0, 10), (float)GetRandomValue(0, 10));
    }
    std::cout << "pureComponent init: " << timer.getDuration() << '\n';

    // mem Component init
    timer.begin();
    Component memComponent(sizeof(Vector2), nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        add(memComponent, i, Vector2{(float)GetRandomValue(0, 10), (float)GetRandomValue(0, 10)});
    }
    std::cout << "newComponent p init : " << timer.getDuration() << '\n';

    ////////////////////////////////////////////////////////////////////////////
    ///               Access and modify data test
    ////////////////////////////////////////////////////////////////////////////
    int nrOfTests = 100;

    // Base component
    timer.begin();
    for (int test = 0; test < nrOfTests; ++test) {
        for (int i = 0; i < nrOfEntities; ++i) {
            baseComponent.data[i].x += 1.f;
            baseComponent.data[i].y += 1.f;
        }
    }
    double duration = timer.getDuration();
    std::cout << "Base:\n";
    std::cout << "Total duration: " << duration << "   average duration: " << (duration / nrOfTests) << '\n';

    // pure component
    timer.begin();
    for (int test = 0; test < nrOfTests; ++test) {
        for (int i = 0; i < nrOfEntities; ++i) {
            pureComponent.data[i].x += 1.f;
            pureComponent.data[i].y += 1.f;
        }
    }
    duration = timer.getDuration();
    std::cout << "Pure:\n";
    std::cout << "Total duration: " << duration << "   average duration: " << (duration / nrOfTests) << '\n';

    // mem component
    timer.begin();
    for (int test = 0; test < nrOfTests; ++test) {
        for (int i = 0; i < nrOfEntities; ++i) {
            accessData<Vector2>(memComponent, i).x += 1.f;
            accessData<Vector2>(memComponent, i).y += 1.f;
        }
    }
    duration = timer.getDuration();
    std::cout << "Mem:\n";
    std::cout << "Total duration: " << duration << "   average duration: " << (duration / nrOfTests) << '\n';
}

#endif
