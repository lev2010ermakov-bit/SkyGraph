#include <LitMat.hpp>

namespace sky{
    LitMat::LitMat(){

    }

    LitMat::LitMat(Shader& s){
        shader = &s;

        shader->SetInt("u_Material.DiffuseMap", 0);
        shader->SetInt("u_Material.SpecularMap", 1);
        shader->SetInt("u_Material.EmissionMap", 2);
    }

    void LitMat::Bind(){
        if (!shader) return;
        bool diff = DiffuseMap != nullptr;
        bool spec = SpecularMap != nullptr;
        bool emis = EmissionMap != nullptr;

        shader->SetColor("u_Material.DiffuseColor", color);
        shader->SetVec3("u_Material.ShadowColor", ShadowColor.glCol3());
        shader->SetFloat("u_Material.Shiness", Shiness);
        shader->SetFloat("u_Material.Specular", Roughness);
        shader->SetFloat("u_Material.minLight", MinLight);
        shader->SetBool("u_Material.hasDiff", diff);
        shader->SetBool("u_Material.hasSpec", spec);
        shader->SetBool("u_Material.hasEmis", emis);
        shader->use();

        if (diff){
            glActiveTexture(GL_TEXTURE0);
            DiffuseMap->Bind();
        }
    
        if (spec){
            glActiveTexture(GL_TEXTURE1);
            SpecularMap->Bind();
        }
    
        if (emis){
            glActiveTexture(GL_TEXTURE2);
            EmissionMap->Bind();
        }
    }
}