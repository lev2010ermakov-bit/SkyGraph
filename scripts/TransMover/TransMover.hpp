#pragma once

#include <SkyGraph.hpp>

class TransMover{
    private:
        float buttPand;
        unsigned int currentOption;
    public:
        sky::Transformable* Target;
        bool inWork;
        TransMover();
        TransMover(sky::Transformable& target);
        void Update();
};