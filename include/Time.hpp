#pragma once

namespace sky{
    class Time{
        private:
            static float lastTime;
            static Time* instance;
        public:
            static float deltaTime;

            Time();
            static void Init();
            static void Update();
    };
}