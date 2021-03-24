// Custom Headers
#include <Renderer.h>	// Renderer header
#include <Utils.h>		// Utility header
#include <GUI.h>		// GUI header
#include <Scene.h>		// Scene header
#include <CustomMath.h> // Math header
#include <FileSystem.h> // Filesystem header
#include <Primitive.h>	// Primitive header
#include <Shader.h>		// Shader header
#include <Texture.h>	// Texture header
#include <Camera.h>		// Camera header
#include <Light.h>		// Light header
#include <Model.h>		// Model header
#include <ExampleGUI.h> // Custom GUI Widgets

// Standard Headers
#include <iostream>
#include <vector>

// Const Settings
const int majorVersion = 4;
const int minorVersion = 6;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *windowTitle = "OpenGL window";

Renderer renderer(majorVersion, minorVersion, SCR_WIDTH, SCR_HEIGHT);

Scene *loadedScenes;
int maxSceneCount = 3;
int currentSceneIndex = 0;
int loadIndex = -1;
int loadedSceneCount = 0;
int listIndex;

enum AppMode
{
	Empty_Scene,
	Normal_Scene,
};
AppMode currentMode = Empty_Scene;

bool overlayOpen = true;
bool listOpen = false;

// Method Declarations
int SetupRenderer();
void Draw();
void ClearScreen();
void ShowFileMenu();
void ShowEditMenu();
void ShowViewMenu();
void DrawNormalScene();

// Main Function
int main()
{
	if (SetupRenderer() == -1)
	{
		renderer.TerminateGLFW();
		return -1;
	}
	Draw();
	renderer.TerminateGLFW();
	return 0;
}

// Setup Renderer Data
int SetupRenderer()
{
	renderer.SetupGLFW();
	renderer.CreateWindow(windowTitle);
	if (renderer.window == NULL)
	{
		return -1;
	}
	renderer.SetData();
	if (!renderer.CheckGLAD())
	{
		return -1;
	}
	renderer.SetOtherData();
	renderer.SetupFrameBuffer();
	return 0;
}

// Draw Method
void Draw()
{
	// Setup GUI
	GUI gui(renderer.window, majorVersion, minorVersion);
	loadedScenes = new Scene[maxSceneCount];
	// Start Render Loop
	renderer.StartTimer();
	/*
	Render Loop
	1. New Frame
	2. Process Data
	3. Get New Data
	4. Refresh Last Frame
		a. Clear Screen
		b. Bind FBO
	5. Render Objects
		a. Draw Opaque Objects
			i. Ground First
			ii. Others Second
		b. Draw Translucent Objects
			i. Farthest to Closest
		c. Draw Skybox
		d. Draw 2D objects
	6. Render FBO
		a. Unbind FBO
		b. Clear Screen
		c. Draw Texture
	7. Render GUI
	8. End Frame
	*/
	while (!renderer.CheckWindowFlag())
	{
		// New Frame
		gui.NewFrame();
		renderer.NewFrame();

		// Process Data
		renderer.ProcessInput();

		// Get New Data
		int currentWidth = (int)renderer.GetCurrentWidth();
		int currentHeight = (int)renderer.GetCurrentHeight();

		// Refresh Frame
		switch (currentMode)
		{
		case Empty_Scene:
			ClearScreen();
			break;
		case Normal_Scene:
			DrawNormalScene();
			break;
		}

		// Render GUI
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ShowFileMenu();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ShowEditMenu();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View"))
			{
				ShowViewMenu();
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		// End Frame
		gui.RenderGUI();
		renderer.SwapBuffers();
	}
	// Free Data
	// Free frame buffer
	renderer.frameBuffer.FreeFBO();
	renderer.frameBuffer.FreeRBO();

	// Terminate Program
	gui.TerminateGUI();
}

void ClearScreen()
{
	renderer.SetColor(0.0f, 0.0, 0.0f, 1.0f);
}

void DrawNormalScene()
{
	int sceneNumber = max(1, loadedSceneCount - 2) + currentSceneIndex;
	listIndex = (sceneNumber + maxSceneCount - 1) % maxSceneCount;
	loadedScenes[listIndex].DrawScene(renderer);
	// Render GUI
	ImGui::ShowDemoWindow();
	if (overlayOpen)
	{
		ShowSimpleOverlay(&overlayOpen, sceneNumber);
	}
	if (listOpen)
	{
		ShowAppLayout(&listOpen, &(loadedScenes[listIndex]));
	}
}

void ShowFileMenu()
{
	if (ImGui::MenuItem("New Scene"))
	{
		currentMode = Normal_Scene;
		Scene nextScene("New Scene");
		loadIndex = (loadIndex + 1) % maxSceneCount;
		loadedSceneCount++;
		loadedScenes[loadIndex] = nextScene;
		currentSceneIndex = loadedSceneCount >= maxSceneCount ? 2 : loadIndex;
	}
	if (ImGui::MenuItem("Open Scene"))
	{
	}
	if (ImGui::BeginMenu("Open Recent Scene"))
	{
		if (loadedSceneCount == 0)
		{
			ImGui::MenuItem("(No Loaded Scenes)", NULL, false, false);
		}
		else
		{
			int startIndex = max(1, loadedSceneCount - 2);
			for (int i = startIndex; i <= loadedSceneCount; i++)
			{
				std::string name = "Scene " + std::to_string(i);
				if (ImGui::MenuItem(name.c_str()))
				{
					currentMode = Normal_Scene;
					currentSceneIndex = (i - startIndex) % maxSceneCount;
				}
			}
		}
		ImGui::EndMenu();
	}
	ImGui::Separator();
	if (ImGui::MenuItem("Save Scene"))
	{
	}
	if (ImGui::MenuItem("Save Scene as.."))
	{
	}
	ImGui::Separator();
	if (ImGui::MenuItem("Close Scene"))
	{
		currentMode = Empty_Scene;
	}
	if (ImGui::MenuItem("Quit", "Escape"))
	{
		renderer.QuitWindow();
	}
}

void ShowEditMenu()
{
	if (currentMode == Normal_Scene)
	{
		if (ImGui::BeginMenu("Edit Current Scene.."))
		{
			ImGui::ColorEdit4("Background Color", &(loadedScenes[listIndex]).backgroundColor.x);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Add Object.."))
		{
			if (ImGui::MenuItem("Triangle"))
			{
				loadedScenes[listIndex].AddObject("resources/primitives/2D/triangle.2d", PRIMITIVE_OBJECT);
			}
			if (ImGui::MenuItem("Rectangle"))
			{
				loadedScenes[listIndex].AddObject("resources/primitives/2D/rectangle.2d", PRIMITIVE_OBJECT);
			}
			if (ImGui::MenuItem("Cube"))
			{
				loadedScenes[listIndex].AddObject("resources/primitives/3D/cube.3d", PRIMITIVE_OBJECT);
			}
			/*if (ImGui::MenuItem("Backpack"))
			{
				loadedScenes[listIndex].AddObject("resources/models/backpack/backpack.obj", MODEL_OBJECT);
			}*/
			ImGui::EndMenu();
		}
	}
	else
	{
		ImGui::MenuItem("(No Scene Open)", NULL, false, false);
	}
}

void ShowViewMenu()
{
	if (currentMode == Normal_Scene)
	{
		if (ImGui::BeginMenu("SetView"))
		{
			ImGui::MenuItem("Overlay", NULL, &overlayOpen);
			ImGui::MenuItem("Object List", NULL, &listOpen);
			ImGui::EndMenu();
		}
	}
	else
	{
		ImGui::MenuItem("(No Scene Open)", NULL, false, false);
	}
}