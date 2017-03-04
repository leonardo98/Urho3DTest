#include "TileMap.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Graphics/Graphics.h>

#include <vector>
#include <string>

TileMap::TileMap(Context* context)
    : Component(context)
    , m_spriteSheet(nullptr)
{
}

void TileMap::Init()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();

    m_spriteSheet = cache->GetResource<SpriteSheet2D>("Custom/tiles2.xml");
    if (!m_spriteSheet)
        return;

    // Get sprite
    std::vector<std::string> names;
    names.push_back("greenTile_0");
    names.push_back("greenTile_33");
    names.push_back("greenTile_66");
    names.push_back("brownTile_0");
    names.push_back("brownTile_33");
    names.push_back("brownTile_66");
    names.push_back("lightBrownStoneTile_0");
    names.push_back("lightBrownStoneTile_33");
    names.push_back("lightBrownStoneTile_66");
    names.push_back("yellowTile_0");
    names.push_back("yellowTile_33");
    names.push_back("yellowTile_66");
    names.push_back("blueStoneTile_0");
    names.push_back("blueStoneTile_33");
    names.push_back("blueStoneTile_66");
    names.push_back("redStoneTile_0");
    names.push_back("redStoneTile_33");
    names.push_back("redStoneTile_66");
    names.push_back("lightGreenTile_0");
    names.push_back("lightGreenTile_33");
    names.push_back("lightGreenTile_66");
    names.push_back("lightBlueTile_0");
    names.push_back("lightBlueTile_33");
    names.push_back("lightBlueTile_66");
    names.push_back("brickR_0");
    names.push_back("brickR_33");
    names.push_back("brickR_66");
    names.push_back("brickL_0");
    names.push_back("brickL_33");
    names.push_back("brickL_66");
    names.push_back("brickC_0");
    names.push_back("brickC_33");
    names.push_back("brickC_66");
    names.push_back("brownStoneTile_0");
    names.push_back("brownStoneTile_33");
    names.push_back("brownStoneTile_66");
    names.push_back("turquoiseTile_0");
    names.push_back("turquoiseTile_33");
    names.push_back("turquoiseTile_66");

    names.push_back("whiteTile_0");
    names.push_back("whiteTile_33");
    names.push_back("whiteTile_66");
    names.push_back("flat1_0");
    names.push_back("flat1_33");
    names.push_back("flat1_66");
    names.push_back("flat2_0");
    names.push_back("flat2_33");
    names.push_back("flat2_66");
    names.push_back("flat3_0");
    names.push_back("flat3_33");
    names.push_back("flat3_66");
    names.push_back("flat4_0");
    names.push_back("flat4_33");
    names.push_back("flat4_66");
    names.push_back("round4_0");
    names.push_back("round4_33");
    names.push_back("round4_66");
    names.push_back("cubic2_0");
    names.push_back("cubic2_33");
    names.push_back("cubic2_66");
    names.push_back("grayStoneTile_0");
    names.push_back("grayStoneTile_33");
    names.push_back("grayStoneTile_66");
    names.push_back("cubic3_0");
    names.push_back("cubic3_33");
    names.push_back("cubic3_66");
    names.push_back("fullBlackTileWall_0");
    names.push_back("fullBlackTileWall_33");
    names.push_back("fullBlackTileWall_66");
    names.push_back("cubic4_0");
    names.push_back("cubic4_33");
    names.push_back("cubic4_66");
    names.push_back("expFunnel_0");
    names.push_back("expFunnel_33");
    names.push_back("expFunnel_66");
    names.push_back("cubic1_0");
    names.push_back("cubic1_33");
    names.push_back("cubic1_66");
    names.push_back("blackTile_0");
    names.push_back("blackTile_33");
    names.push_back("blackTile_66");
    names.push_back("round1_0");
    names.push_back("round1_33");
    names.push_back("round1_66");
    names.push_back("blueTile_0");
    names.push_back("blueTile_33");
    names.push_back("blueTile_66");
    names.push_back("round2_0");
    names.push_back("round2_33");
    names.push_back("round2_66");
    names.push_back("round3_0");
    names.push_back("round3_33");
    names.push_back("round3_66");
    
    Graphics* graphics = GetSubsystem<Graphics>();

    float halfWidth = graphics->GetWidth() * 0.5f * PIXEL_SIZE;
    float halfHeight = graphics->GetHeight() * 0.5f * PIXEL_SIZE;
    float x = -halfWidth;
    float y = -halfHeight;
    for (unsigned i = 0; i < names.size(); ++i)
    {
        SharedPtr<Node> spriteNode(GetNode()->CreateChild("StaticSprite2D"));
        spriteNode->SetPosition(Vector3(x, y, 0.0f));
        x += 100 * PIXEL_SIZE;
        if (x > halfWidth)
        {
            x = -halfWidth;
            y += 50 * PIXEL_SIZE;
        }

        StaticSprite2D* staticSprite = spriteNode->CreateComponent<StaticSprite2D>();
        // Set random color
        //staticSprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f));
        // Set blend mode
        staticSprite->SetBlendMode(BLEND_ALPHA);
        // Set sprite
        Sprite2D* sprite = m_spriteSheet->GetSprite(names[i % names.size()].c_str());
        if (sprite)
            staticSprite->SetSprite(sprite);
        else
            int i = 0;

        // Set move speed
        //spriteNode->SetVar(VAR_MOVESPEED, Vector3(Random(-2.0f, 2.0f), Random(-2.0f, 2.0f), 0.0f));
        // Set rotate speed
        //spriteNode->SetVar(VAR_ROTATESPEED, Random(-90.0f, 90.0f));

        // Add to sprite node vector
        m_spriteNodes.Push(spriteNode);
    }

    //// Get tmx file
    //TmxFile2D* tmxFile = cache->GetResource<TmxFile2D>("Urho2D/isometric_grass_and_water.tmx");
    //if (!tmxFile)
    //    return;

    //SharedPtr<Node> tileMapNode(scene_->CreateChild("TileMap"));
    //tileMapNode->SetPosition(Vector3(0.0f, 0.0f, -1.0f));

    //TileMap2D* tileMap = tileMapNode->CreateComponent<TileMap2D>();
    //// Set animation
    //tileMap->SetTmxFile(tmxFile);

    //// Set camera's position
    //const TileMapInfo2D& info = tileMap->GetInfo();
    //float x = info.GetMapWidth() * 0.5f;
    //float y = info.GetMapHeight() * 0.5f;
    //m_cameraNode->SetPosition(Vector3(x, y, -10.0f));
}

