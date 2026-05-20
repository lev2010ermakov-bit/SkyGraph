#pragma once

template <typename T> void Destroy(T& object)
{
    object.destroy();
    delete &object;
}