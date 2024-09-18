#ifndef TESTS_COMPONENT_TESTING_HPP
#define TESTS_COMPONENT_TESTING_HPP

#include "Timer.h"
#include <iostream>

// memComponent
#include "Component.h"
#include "ComponentUtils.h"

inline void
memComponentTest() {

    std::cout << "\n\n";
    int nrOfEntities = 1000000;
    Timer timer;

    ////////////////////////////////////////////////////////////////////////////
    ///               init test
    ////////////////////////////////////////////////////////////////////////////

    // mem Component init
    timer.begin();
    Component memComponent(sizeof(Vector2), nrOfEntities);
    for (int i = 0; i < nrOfEntities; ++i) {
        add(memComponent, i, Vector2{(float)GetRandomValue(0, 10), (float)GetRandomValue(0, 10)});
    }
    std::cout << "MemComponent init : " << timer.getDuration() << '\n';

    ////////////////////////////////////////////////////////////////////////////
    ///               Access and modify data test
    ////////////////////////////////////////////////////////////////////////////
    int nrOfTests = 100;

    // mem component
    timer.begin();
    for (int test = 0; test < nrOfTests; ++test) {
        for (int i = 0; i < nrOfEntities; ++i) {
            accessData<Vector2>(memComponent, i).x += 1.f;
            accessData<Vector2>(memComponent, i).y += 1.f;
        }
    }
    double duration = timer.getDuration();
    std::cout << "Total duration: " << duration << "   average duration: " << (duration / nrOfTests) << '\n';
}

#endif
