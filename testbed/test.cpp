#define USING_GAMEWORK
#include <gamework.h>

class SimpleGame : public gamework::GameWorkApp
{
public:
    SimpleGame(const gamework::WindowSpecs& specs) : gamework::GameWorkApp(specs){
        
    }
    ~SimpleGame() {}

    void OnStart() override {
        std::cerr << "OnStart!" << std::endl;
    }

    void OnUpdate(double timestep) override {
        std::cout << "OnUpdate!" << std::endl;
    }

    void OnFixedUpdate() override {
        std::cout << "OnFixedUpdate!" << std::endl;
    }

    void OnExit() override {
        std::cout << "OnExit!" << std::endl;
    } 
};

void main()
{
    gamework::WindowSpecs window_specs;

    window_specs.window_width = 1024;
    window_specs.window_height = 576;
    window_specs.window_title = "gamework::Window";
    window_specs.window_vsync = 1;
    window_specs.window_fullscreen = 1;

    gamework::GameWorkApp* app = new SimpleGame(window_specs);
    app->GameLoop();
}