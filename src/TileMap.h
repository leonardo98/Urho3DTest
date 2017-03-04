#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/Component.h>
#include <Urho3D/Urho2D/SpriteSheet2D.h>
#include <Urho3D/Container/Vector.h>

using namespace Urho3D;
class TileMap : public Component
{
URHO3D_OBJECT(TileMap, Component);
private:
    SharedPtr<SpriteSheet2D> m_spriteSheet;
    Vector<SharedPtr<Node> > m_spriteNodes;
    
public:
    TileMap(Context* context);
    void Init();
};

#endif//TILE_MAP_H
