#include "TileMap.h"

#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/IO/Log.h>

SmallField::SmallField(Context* context)
    : Component(context)
{
}

void SmallField::Init(unsigned int width, unsigned int height)
{
    m_field.Resize(width);
    for (auto &column: m_field)
    {
        column.Resize(height);
        for (auto &cell: column)
        {
            cell = nullptr;
        }
    }

}

SharedPtr<Node> SmallField::SetCell(unsigned int i, unsigned int j, Sprite2D *sprite)
{
//    Graphics* graphics = GetSubsystem<Graphics>();

    SharedPtr<Node> spriteNode(GetNode()->CreateChild("StaticSprite2D"));
    StaticSprite2D* staticSprite = spriteNode->CreateComponent<StaticSprite2D>();
    if (sprite)
        staticSprite->SetSprite(sprite);
    else
        Log::Write(10, "sprite is null");

    m_field[i][j] = spriteNode;

    return spriteNode;
//    for (unsigned i = 0; i < m_names.size(); ++i)
//    {
//        SharedPtr<Node> spriteNode(GetNode()->CreateChild("StaticSprite2D"));
//        spriteNode->SetPosition(Vector3(x, y, 0.0f));
//        x += 100 * PIXEL_SIZE;
//        if (x > halfWidth)
//        {
//            x = -halfWidth;
//            y += 50 * PIXEL_SIZE;
//        }
//
//        StaticSprite2D* staticSprite = spriteNode->CreateComponent<StaticSprite2D>();
//        // Set random color
//        //staticSprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f));
//        // Set blend mode
//        staticSprite->SetBlendMode(BLEND_ALPHA);
//        // Set sprite
//        Sprite2D* sprite = m_spriteSheet->GetSprite(m_names[i % m_names.size()].c_str());
//        if (sprite)
//            staticSprite->SetSprite(sprite);
//        else
//            int i = 0;
//
//        // Set move speed
//        //spriteNode->SetVar(VAR_MOVESPEED, Vector3(Random(-2.0f, 2.0f), Random(-2.0f, 2.0f), 0.0f));
//        // Set rotate speed
//        //spriteNode->SetVar(VAR_ROTATESPEED, Random(-90.0f, 90.0f));
//
//        // Add to sprite node vector
//        m_spriteNodes.Push(spriteNode);
//    }
}


TileMap::TileMap(Context* context)
    : Component(context)
    , m_spriteSheet(nullptr)
    , m_cellWidth(100)
    , m_cellHeight(50)
{
}

void TileMap::Init(unsigned int rowMax, unsigned int colMax, unsigned int smallFieldWidth, unsigned int smallFieldHeight)
{
    m_smallFieldWidth = smallFieldWidth;
    m_smallFieldHeight = smallFieldHeight;
    m_bigField.Resize(colMax);
    for (auto &column: m_bigField)
    {
        column.Resize(rowMax);
        for (auto &smallField: column)
        {
            smallField = nullptr;
        }
    }

    ResourceCache* cache = GetSubsystem<ResourceCache>();

    m_spriteSheet = cache->GetResource<SpriteSheet2D>("Custom/tiles2.xml");
    if (!m_spriteSheet)
        return;

    // Get sprite
    m_names.clear();

    // TODO: remove this line
    m_names.push_back("greenTile_0");
    m_names.push_back("brownTile_0");
    m_names.push_back("lightBrownStoneTile_0");
    m_names.push_back("yellowTile_0");
    // end to remove

    m_names.push_back("greenTile_0");
    m_names.push_back("greenTile_33");
    m_names.push_back("greenTile_66");
    m_names.push_back("brownTile_0");
    m_names.push_back("brownTile_33");
    m_names.push_back("brownTile_66");
    m_names.push_back("lightBrownStoneTile_0");
    m_names.push_back("lightBrownStoneTile_33");
    m_names.push_back("lightBrownStoneTile_66");
    m_names.push_back("yellowTile_0");
    m_names.push_back("yellowTile_33");
    m_names.push_back("yellowTile_66");
    m_names.push_back("blueStoneTile_0");
    m_names.push_back("blueStoneTile_33");
    m_names.push_back("blueStoneTile_66");
    m_names.push_back("redStoneTile_0");
    m_names.push_back("redStoneTile_33");
    m_names.push_back("redStoneTile_66");
    m_names.push_back("lightGreenTile_0");
    m_names.push_back("lightGreenTile_33");
    m_names.push_back("lightGreenTile_66");
    m_names.push_back("lightBlueTile_0");
    m_names.push_back("lightBlueTile_33");
    m_names.push_back("lightBlueTile_66");
    m_names.push_back("brickR_0");
    m_names.push_back("brickR_33");
    m_names.push_back("brickR_66");
    m_names.push_back("brickL_0");
    m_names.push_back("brickL_33");
    m_names.push_back("brickL_66");
    m_names.push_back("brickC_0");
    m_names.push_back("brickC_33");
    m_names.push_back("brickC_66");
    m_names.push_back("brownStoneTile_0");
    m_names.push_back("brownStoneTile_33");
    m_names.push_back("brownStoneTile_66");
    m_names.push_back("turquoiseTile_0");
    m_names.push_back("turquoiseTile_33");
    m_names.push_back("turquoiseTile_66");

    m_names.push_back("whiteTile_0");
    m_names.push_back("whiteTile_33");
    m_names.push_back("whiteTile_66");
    m_names.push_back("flat1_0");
    m_names.push_back("flat1_33");
    m_names.push_back("flat1_66");
    m_names.push_back("flat2_0");
    m_names.push_back("flat2_33");
    m_names.push_back("flat2_66");
    m_names.push_back("flat3_0");
    m_names.push_back("flat3_33");
    m_names.push_back("flat3_66");
    m_names.push_back("flat4_0");
    m_names.push_back("flat4_33");
    m_names.push_back("flat4_66");
    m_names.push_back("round4_0");
    m_names.push_back("round4_33");
    m_names.push_back("round4_66");
    m_names.push_back("cubic2_0");
    m_names.push_back("cubic2_33");
    m_names.push_back("cubic2_66");
    m_names.push_back("grayStoneTile_0");
    m_names.push_back("grayStoneTile_33");
    m_names.push_back("grayStoneTile_66");
    m_names.push_back("cubic3_0");
    m_names.push_back("cubic3_33");
    m_names.push_back("cubic3_66");
    m_names.push_back("fullBlackTileWall_0");
    m_names.push_back("fullBlackTileWall_33");
    m_names.push_back("fullBlackTileWall_66");
    m_names.push_back("cubic4_0");
    m_names.push_back("cubic4_33");
    m_names.push_back("cubic4_66");
    m_names.push_back("expFunnel_0");
    m_names.push_back("expFunnel_33");
    m_names.push_back("expFunnel_66");
    m_names.push_back("cubic1_0");
    m_names.push_back("cubic1_33");
    m_names.push_back("cubic1_66");
    m_names.push_back("blackTile_0");
    m_names.push_back("blackTile_33");
    m_names.push_back("blackTile_66");
    m_names.push_back("round1_0");
    m_names.push_back("round1_33");
    m_names.push_back("round1_66");
    m_names.push_back("blueTile_0");
    m_names.push_back("blueTile_33");
    m_names.push_back("blueTile_66");
    m_names.push_back("round2_0");
    m_names.push_back("round2_33");
    m_names.push_back("round2_66");
    m_names.push_back("round3_0");
    m_names.push_back("round3_33");
    m_names.push_back("round3_66");
    

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

void TileMap::CreateSmallField(unsigned int row, unsigned int col)
{
}

void TileMap::SetFieldCell(unsigned int i, unsigned int j, int index)
{
    unsigned int sfIndexCol = j / m_smallFieldHeight;
    unsigned int sfIndexRow = i / m_smallFieldWidth;
    SmallField *smallField = nullptr;
    if (m_bigField[sfIndexRow][sfIndexCol] == nullptr)
    {
        m_bigField[sfIndexRow][sfIndexCol] = GetNode()->CreateChild("SmallField");
        smallField = m_bigField[sfIndexRow][sfIndexCol]->CreateComponent<SmallField>();
        smallField->Init(m_smallFieldWidth, m_smallFieldHeight);
    }
    else
    {
        smallField = m_bigField[sfIndexRow][sfIndexCol]->GetComponent<SmallField>();
    }
    unsigned int sfCol = j % m_smallFieldHeight;
    unsigned int sfRow = i % m_smallFieldWidth;
    index = sfIndexRow * 2 + sfIndexCol;// TODO: remove this line
    Node *node = smallField->SetCell(sfRow, sfCol, m_spriteSheet->GetSprite(m_names[index].c_str()));
    Vector3 shiftX(m_cellWidth / 2 * PIXEL_SIZE, m_cellHeight / 2 * PIXEL_SIZE, 0.f);
    Vector3 shiftY(- m_cellWidth / 2 * PIXEL_SIZE, m_cellHeight / 2 * PIXEL_SIZE, 0.f);
    node->SetPosition(i * shiftX + j * shiftY);
}

