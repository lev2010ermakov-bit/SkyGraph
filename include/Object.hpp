#pragma once 

#include "Component.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

namespace sk{
    const glm::vec3 World_up = glm::vec3(0, 1, 0);
    
    class Object{
        private:
            static Object* scene;
            Object* parent;
            std::vector<Object> childs;
            std::vector<Component> components;
        public:
            glm::vec3 position;
            glm::vec3 eulerAngles;
            glm::vec3 scale;

            glm::vec3 front;
            glm::vec3 right;
            glm::vec3 up;

            Object();

            void AddChild(Object child);
            Object& GetChild(int id);

            void SetParent(Object& parent);
            void SetParent(Object* parent);
            Object* GetParent();

            void UpdateLocalVectors();
            glm::mat4 GetModelMat();

            template<typename T>
            void AddComponent(){
                T res(*this);
                if (!dynamic_cast<Component*>(res)){
                    std::cout << "this type is not Component. adding to object aborted!\n";
                }
                components.push_back(static_cast<Component>(res));
            }

            template<typename T>
            T* GetComponent(){
                T* res = nullptr;
                for (auto& c : components){
                    if (dynamic_cast<T*>(&c)){
                        res = dynamic_cast<T*>(&c);
                        break;
                    }
                }
                if (res == nullptr)
                    std::cout << "failed to find this kind of component\n";
                
                return res;
            }

            void Update(){
                for (auto& c : components){
                    c.Update();
                }
            }
    };
}
