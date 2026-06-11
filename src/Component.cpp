#include <Component.hpp>

namespace sk{
    Component::Component(Object& o) : thisObject(o){
        
    }

    Object& Component::GetObject(){
        return thisObject;
    }

    void Component::Update(){
        
    }
}