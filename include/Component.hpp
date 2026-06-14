#pragma once

namespace sky{
    class Object;

    class Component{
        private:
            sky::Object& thisObject;
        public:
            Component(Object& node);
            Object& GetObject();
            virtual void Update();
    };
}