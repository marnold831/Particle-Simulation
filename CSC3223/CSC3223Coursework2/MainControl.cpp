#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/MeshGeometry.h"
#include "TerrainGeneration.h"
#include "SnowGeneration.h"

using namespace NCL;
using namespace CSC3223;
using namespace Generation;

int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");

	if (!w->HasInitialised()) {
 	}

	/*Screen size variables*/
	Vector2 size = w->GetScreenSize();
	float currentWidth = size.x;
	float currentHeight = size.y;
	float depth = 100.0;
	float width = 100.0;
	bool screenLock = true;
	bool wireFrame = false;

	/*Camera variables*/
	float pitch = 0.0f;
	float yaw = 0.0f;
	float speed = 0.05f;

	/*variables to hold positions*/
	Vector3 viewPosition(0, 0, 0);
	Vector2 vec(0, 0);

	/*Renderer Creation, Objects Creation*/
	Renderer*	renderer = new Renderer(*w);
	TerrainGeneration* tG = new TerrainGeneration();
	SnowGeneration* sG = new SnowGeneration(1000, 5.0, 50.0);
	tG->generatePlane(*renderer, depth, width, 5.2, 5.2);
	sG->generateSnow(*renderer, width, depth);

	/*set background colour black*/
	//lClearColor(0.0, 0.75, 0.99, 1);
	glClearColor(0.75, 0.75, 0.75, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/*Set projection matrix*/
	renderer->SetProjectionMatrix(Matrix4::Perspective(1.0f, 200.0f, w->GetScreenAspect(), 60.0f));
	//renderer->SetProjectionMatrix(Matrix4::Orthographic(-1.0f, 1.0f, currentWidth, 0.0f, 0.0f, currentHeight));

	/*Enable Depth Buffer*/
	renderer->EnableDepthBuffer(true);
	

	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		renderer->EnableAlphaBlending(true);
		float time = w->GetTimer()->GetTimeDelta();
		renderer->Update(time);
		renderer->DrawString(std::to_string(viewPosition.x) + " " + std::to_string(viewPosition.y) + " " + std::to_string(viewPosition.z), Vector2(20, 20));
		renderer->DrawString(std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(speed), Vector2(5, 5));
		
		
		w->LockMouseToWindow(screenLock);
		w->SetTitle(std::to_string(time));

		/*Screen Control*/
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_L)) {
			if (screenLock) {
				screenLock = false;
			}
			else {
				screenLock = true;
			}
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F)) {
			if (wireFrame) {
				wireFrame = false;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				wireFrame = true;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}

		/*Camera Controls*/
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			viewPosition += Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * time * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			viewPosition -= Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * Vector3(-1, 0, 0) * time * speed;
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition += Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1) * time * speed;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition -= Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * Vector3(0, 0, -1) * time * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			viewPosition.y -= time * 0.005;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			viewPosition.y += time * 0.005;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_PLUS)) {
			speed += 0.0005;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_MINUS)) {
			speed -= 0.0005;
		}

		/*Reset Camera*/
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_E)) {
			viewPosition = (Vector3(0, 0, 0));
			renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_1)) {
			speed = 1.0;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_2)) {
			speed = 0.1;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_3)) {
			speed = 0.01;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_4)) {
			speed = 0.001;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_5)) {
			speed = 0.0001;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_6)) {
			speed = 0.00001;
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_7)) {
			speed = 0.000001;
		}

		/*Set Mouse variables*/
		vec = Window::GetMouse()->GetRelativePosition();
		pitch += vec.y;
		yaw += vec.x;


		//Bounds check the pitch, to be between straight up and straight down
		pitch = min(pitch, 90.0f);
		pitch = max(pitch, -90.0f);

		if (yaw < 0) {
			yaw += 360.0f;
		}
		if (yaw > 360.0f) {
			yaw -= 360.0f;
		}

		renderer->SetViewMatrix(Matrix4::Rotation(pitch, Vector3(1, 0, 0)) * Matrix4::Rotation(yaw, Vector3(0, 1, 0)) * Matrix4::Translation(-viewPosition));
		renderer->Render();
	}

	delete renderer;
	delete tG;
	Window::DestroyGameWindow();
}
