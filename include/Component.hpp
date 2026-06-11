#pragma once

namespace sk{
    class Object;

    class Component{
        private:
            sk::Object& thisObject;
        public:
            Component(Object& node);
            Object& GetObject();
            virtual void Update();
    };
}