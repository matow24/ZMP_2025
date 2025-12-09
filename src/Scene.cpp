#include "Scene.hh"

Scene::~Scene()
{
    for( auto& pair : this->_objects ) {
        delete pair.second;
    }
}

AbstractMobileObj*  Scene::FindMobileObj(const char *sName)
{
    if( this->_objects.count(sName) == 0 ) {
        return nullptr;
    }

    return this->_objects[sName];
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj)
{
    if( ( pMobObj == nullptr ) || ( this->_objects.count(pMobObj->GetName()) ) )
        return;

    this->_objects[pMobObj->GetName()] = pMobObj;

}