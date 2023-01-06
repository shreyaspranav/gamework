#include <iostream>
#include <GLFW/glfw3.h>

constexpr double S_PER_FIXED_UPDATE = 1.0 / 60.0;


void print_glfw_init() {
	std::cout << glfwInit() << std::endl;
}

// Window stuff
namespace gamework {

	struct WindowSpecs {
		unsigned int window_width, window_height;
		const char* window_title;
		bool window_fullscreen;

		unsigned int window_min_width = 0, window_max_width = 0, window_min_height = 0, window_max_height = 0;
		bool window_vsync;
	};

	class Window {
	public:
		Window(const WindowSpecs& specs);
		~Window();

		void Create();
		void Update();
		void Destroy();

		double GetCurrentTime();

		void SetFullScreen(bool fullscreen);
		bool WindowShouldClose();

	private:
		GLFWwindow* m_Window;
		WindowSpecs m_WindowSpecs;
	};

	class GameWorkApp {
	public:
		GameWorkApp() {}
		GameWorkApp(const WindowSpecs& specs);
		virtual ~GameWorkApp();

		virtual void OnStart();
		virtual void OnUpdate(double timestep);
		virtual void OnFixedUpdate();
		virtual void OnExit();

		void GameLoop();

	private:
		WindowSpecs m_WindowSpecs;
		Window* m_Window;
	};
}

#ifdef USING_GAMEWORK

namespace gamework {

	// Window Class definitions:---------------------------------------------
	Window::Window(const WindowSpecs& specs) {
		m_WindowSpecs = specs;

		if(!glfwInit())
			std::cerr << "GLFW Unable to Initialise!" << std::endl;
	}

	Window::~Window() {
		Window::Destroy();
	}

	void Window::Create() {

		if(m_WindowSpecs.window_fullscreen)
			m_Window = glfwCreateWindow(m_WindowSpecs.window_width,
										m_WindowSpecs.window_height,
										m_WindowSpecs.window_title,
										glfwGetPrimaryMonitor(), NULL);
		else
			m_Window = glfwCreateWindow(m_WindowSpecs.window_width,
										m_WindowSpecs.window_height,
										m_WindowSpecs.window_title,
										NULL, NULL);
		
		if(!m_Window)
			std::cerr << "Unable to Create a GLFW Window!" << std::endl;

		glfwShowWindow(m_Window);
		glfwMakeContextCurrent(m_Window);

		glfwSwapInterval(m_WindowSpecs.window_vsync);

		glfwSetWindowSizeLimits(m_Window, 
								m_WindowSpecs.window_min_width 	== 0 ? GLFW_DONT_CARE : m_WindowSpecs.window_min_width,
								m_WindowSpecs.window_min_height == 0 ? GLFW_DONT_CARE : m_WindowSpecs.window_min_height,
								m_WindowSpecs.window_max_width 	== 0 ? GLFW_DONT_CARE : m_WindowSpecs.window_max_width,
								m_WindowSpecs.window_max_height == 0 ? GLFW_DONT_CARE : m_WindowSpecs.window_max_height);

	}

	void Window::Update() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Destroy() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::SetFullScreen(bool fullscreen) {
		glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(),
							0, 0, 
							m_WindowSpecs.window_width, 
							m_WindowSpecs.window_height,
							GLFW_DONT_CARE);
	}

	bool Window::WindowShouldClose() {
		return glfwWindowShouldClose(m_Window);
	}

	double Window::GetCurrentTime() {
		return glfwGetTime();
	}
	//-------------------------------------------------------------------------

	// GameWorkApp class definitions:--------------------------------
	GameWorkApp::~GameWorkApp() {
		delete m_Window;
	}

	GameWorkApp::GameWorkApp(const WindowSpecs& specs) {
		m_Window = new Window(specs);
	}

	void GameWorkApp::OnStart() {
		m_Window->Create();
		OnStart();
	}

	void GameWorkApp::OnUpdate(double timestep) {
		OnUpdate(timestep);
		m_Window->Update();
	}

	void GameWorkApp::OnFixedUpdate() {
		OnFixedUpdate();
	}
	void GameWorkApp::OnExit() {
		OnExit();
		m_Window->Destroy();
	}

	void GameWorkApp::GameLoop() {

		GameWorkApp::OnStart();

		double previous = m_Window->GetCurrentTime();
		double lag = 0.0;

		while (!m_Window->WindowShouldClose()) {

			double current = m_Window->GetCurrentTime();
			double elapsed = current - previous;
			previous = current;
			lag += elapsed;

			GameWorkApp::OnUpdate(elapsed);

			while (lag >= S_PER_FIXED_UPDATE) {
			  GameWorkApp::OnFixedUpdate();
			  lag -= S_PER_FIXED_UPDATE;
			}
		}
	}
	// ----------------------------------------------------------------
}

#endif