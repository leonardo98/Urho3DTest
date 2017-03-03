#include <Urho3D/Engine/Application.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/FileSystem.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Urho2D/StaticSprite2D.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Urho2D/SpriteSheet2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/IO/File.h>

#include <string>
#include <vector>

#ifdef WIN32
#define printf OutputDebugString
#endif

using namespace Urho3D;
class MyApp : public Application
{
private:
    bool m_mousePressed;
    SharedPtr<Scene> m_scene;
    SharedPtr<Node> m_cameraNode;
    SharedPtr<Node> m_spriterNode;
    int m_spriterAnimationIndex;
    SharedPtr<SpriteSheet2D> m_spriteSheet;
    Vector<SharedPtr<Node> > m_spriteNodes;
public:
    MyApp(Context* context)
        : Application(context)
        , m_mousePressed(false)
        , m_spriterAnimationIndex(0)
    {
    }
    virtual void Setup()
    {
        // Called before engine initialization. engineParameters_ member variable can be modified here
        engineParameters_["WindowTitle"] = "Urho3DTest";
        engineParameters_["LogName"]     = GetSubsystem<FileSystem>()->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
        engineParameters_["FullScreen"]  = false;
        engineParameters_["Headless"]    = false;
        engineParameters_["Sound"]       = false;
#ifdef WIN32
        engineParameters_["WindowWidth"] = 800;
        engineParameters_["WindowHeight"] = 600;
#endif
    }
    virtual void Start()
    {
        // Called after engine initialization. Setup application & subscribe to events here
        CreateScene();
        SetupViewport();

        SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(MyApp, HandleKeyDown));

        Input* input = GetSubsystem<Input>();

        input->SetMouseVisible(true);
        SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(MyApp, HandleMouseDown));
        SubscribeToEvent(E_MOUSEBUTTONUP, URHO3D_HANDLER(MyApp, HandleMouseUp));
        SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(MyApp, HandleMouseMove));
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MyApp, HandleUpdate));

        UnsubscribeFromEvent(E_SCENEUPDATE);
    }
    virtual void Stop()
    {
        // Perform optional cleanup after main loop has terminated
    }
    void HandleKeyDown(StringHash eventType, VariantMap& eventData)
    {
        using namespace KeyDown;
        // Check for pressing ESC. Note the engine_ member variable for convenience access to the Engine object
        int key = eventData[P_KEY].GetInt();
        if (key == KEY_ESCAPE)
            engine_->Exit();
    }
    // If the user clicks the canvas, attempt to switch to relative mouse mode on web platform
    void HandleMouseDown(StringHash eventType, VariantMap& eventData)
    {
        using namespace DragBegin;
        Input* input = GetSubsystem<Input>();
        if (input->GetMouseButtonDown(MOUSEB_LEFT))
        {
            printf("HandleMouseDown\n");
            m_mousePressed = true;
        }
    }

    void HandleMouseUp(StringHash eventType, VariantMap& eventData)
    {
        if (!m_mousePressed)
            return;
        printf("HandleMouseUp\n");
        m_mousePressed = false;
    }
    void HandleMouseMove(StringHash eventType, VariantMap& eventData)
    {
        if (!m_mousePressed)
            return;

        printf("HandleMouseMove\n");
    }
    void HandleDragCancel(StringHash eventType, VariantMap& eventData)
    {
        // cancel onMouseDown action
    }
    void CreateScene()
    {
        m_scene = new Scene(context_);
        m_scene->CreateComponent<Octree>();

        // Create camera node
        m_cameraNode = m_scene->CreateChild("Camera");
        // Set camera's position
        m_cameraNode->SetPosition(Vector3(0.0f, 0.0f, -10.0f));

        Camera* camera = m_cameraNode->CreateComponent<Camera>();
        camera->SetOrthographic(true);

        Graphics* graphics = GetSubsystem<Graphics>();
        camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE);
        camera->SetZoom(1.0f * Min((float)graphics->GetWidth() / 1280.0f, (float)graphics->GetHeight() / 800.0f)); // Set zoom according to user's resolution to ensure full visibility (initial zoom (1.0) is set for full visibility at 1280x800 resolution)
        graphics->Clear(0, Color(1.f, 1.f, 1.f, 1.f));

        ResourceCache* cache = GetSubsystem<ResourceCache>();

        AnimationSet2D* spriterAnimationSet = cache->GetResource<AnimationSet2D>("Urho2D/imp/imp.scml");
        if (!spriterAnimationSet)
            return;

        m_spriterNode = m_scene->CreateChild("SpriterAnimation");
        m_spriterNode->SetScale2D(0.5f, 0.5f);
        AnimatedSprite2D* spriterAnimatedSprite = m_spriterNode->CreateComponent<AnimatedSprite2D>();
        spriterAnimatedSprite->SetAnimationSet(spriterAnimationSet);
        spriterAnimatedSprite->SetAnimation(spriterAnimationSet->GetAnimation(m_spriterAnimationIndex));

        m_spriteSheet = cache->GetResource<SpriteSheet2D>("Custom/tiles2.xml");
        if (!m_spriteSheet)
            return;

        // Get sprite
        std::vector<std::string> names = {
              "greenTile_0"
            , "greenTile_33"
            , "greenTile_66"
            , "brownTile_0"
            , "brownTile_33"
            , "brownTile_66"
            , "lightBrownStoneTile_0"
            , "lightBrownStoneTile_33"
            , "lightBrownStoneTile_66"
            , "yellowTile_0"
            , "yellowTile_33"
            , "yellowTile_66"
            , "blueStoneTile_0"
            , "blueStoneTile_33"
            , "blueStoneTile_66"
            , "redStoneTile_0"
            , "redStoneTile_33"
            , "redStoneTile_66"
            , "lightGreenTile_0"
            , "lightGreenTile_33"
            , "lightGreenTile_66"
            , "lightBlueTile_0"
            , "lightBlueTile_33"
            , "lightBlueTile_66"
            , "brickR_0"
            , "brickR_33"
            , "brickR_66"
            , "brickL_0"
            , "brickL_33"
            , "brickL_66"
            , "brickC_0"
            , "brickC_33"
            , "brickC_66"
            , "brownStoneTile_0"
            , "brownStoneTile_33"
            , "brownStoneTile_66"
            , "turquoiseTile_0"
            , "turquoiseTile_33"
            , "turquoiseTile_66"

            , "whiteTile_0"
            , "whiteTile_33"
            , "whiteTile_66"
            , "flat1_0"
            , "flat1_33"
            , "flat1_66"
            , "flat2_0"
            , "flat2_33"
            , "flat2_66"
            , "flat3_0"
            , "flat3_33"
            , "flat3_66"
            , "flat4_0"
            , "flat4_33"
            , "flat4_66"
            , "round4_0"
            , "round4_33"
            , "round4_66"
            , "cubic2_0"
            , "cubic2_33"
            , "cubic2_66"
            , "grayStoneTile_0"
            , "grayStoneTile_33"
            , "grayStoneTile_66"
            , "cubic3_0"
            , "cubic3_33"
            , "cubic3_66"
            , "fullBlackTileWall_0"
            , "fullBlackTileWall_33"
            , "fullBlackTileWall_66"
            , "cubic4_0"
            , "cubic4_33"
            , "cubic4_66"
            , "expFunnel_0"
            , "expFunnel_33"
            , "expFunnel_66"
            , "cubic1_0"
            , "cubic1_33"
            , "cubic1_66"
            , "blackTile_0"
            , "blackTile_33"
            , "blackTile_66"
            , "round1_0"
            , "round1_33"
            , "round1_66"
            , "blueTile_0"
            , "blueTile_33"
            , "blueTile_66"
            , "round2_0"
            , "round2_33"
            , "round2_66"
            , "round3_0"
            , "round3_33"
            , "round3_66"
        };

        float halfWidth = graphics->GetWidth() * 0.5f * PIXEL_SIZE;
        float halfHeight = graphics->GetHeight() * 0.5f * PIXEL_SIZE;
        float x = -halfWidth;
        float y = -halfHeight;
        for (unsigned i = 0; i < names.size(); ++i)
        {
            SharedPtr<Node> spriteNode(m_scene->CreateChild("StaticSprite2D"));
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
    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        using namespace Update;

        // Take the frame time step, which is stored as a float
        //float timeStep = eventData[P_TIMESTEP].GetFloat();

        // Move the camera, scale movement with time step
//        MoveCamera(timeStep);
    }
    void SetupViewport()
    {
        Renderer* renderer = GetSubsystem<Renderer>();

        // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
        SharedPtr<Viewport> viewport(new Viewport(context_, m_scene, m_cameraNode->GetComponent<Camera>()));
        renderer->SetViewport(0, viewport);
    }
};
URHO3D_DEFINE_APPLICATION_MAIN(MyApp)
