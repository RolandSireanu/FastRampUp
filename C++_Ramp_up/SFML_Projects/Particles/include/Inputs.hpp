#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <optional>
#include <SFML/System.hpp>
#include <mutex>
#include <condition_variable>

namespace Inputs
{

        struct MouseClickEv
        {
            float x;
            float y;
            bool leftClick;
        };

    std::optional<Inputs::MouseClickEv> getMouseClick();
        


};

#endif