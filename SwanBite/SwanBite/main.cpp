#include <SDL3/SDL.h>
#include <SDL3/SDL_Main.h>
#include <string>

//Window Dimensions
constexpr int kWindowWidth{ 640 };
constexpr int kWindowHeight{ 480 };

bool Init();

bool LoadMedia();

void Close();

//Global vars
//Window to render to
SDL_Window* gWindow{ nullptr };

//Surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

//Image to render
SDL_Surface* gHelloWorld{ nullptr };

bool Init() {
	bool success{ true };

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("title", kWindowWidth, kWindowHeight, 0);
		if (gWindow == nullptr){
			SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool LoadMedia() {
	bool success{ true };

	//Load splash image
	std::string imagePath{ "./img.bmp" };
	gHelloWorld = SDL_LoadBMP(imagePath.c_str());

	if (gHelloWorld == nullptr) {
		SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
		success = false;
	}

	return success;
}

void Close() {
	//Clean up
	SDL_DestroySurface(gHelloWorld);
	gHelloWorld = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gScreenSurface = nullptr;

	//Quit out subsystems
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	//Exit code
	int exitCode{ 0 };

	//Initialize
	if (!Init())
	{
		SDL_Log("Unable to initialize program!\n");
		exitCode = 1;
	}
	else
	{
		//Load media
		if (!LoadMedia())
		{
			SDL_Log("Unable to load media!\n");
			exitCode = 2;
		}
		else {
			bool quit{ false };

			SDL_Event e;
			SDL_zero(e);


			//Main Loop
			while (!quit) {
				//Check if player is pressing a button
				while (SDL_PollEvent(&e) != 0) {

					if (e.type == SDL_EVENT_KEY_DOWN) { 
					
					}

					//Quit if player Xs out the window
					if (e.type == SDL_EVENT_QUIT) {
						quit = true;
					}
				}

				//Fill surface with white
				SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

				//Render image on screen
				SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

				//Update surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}

	Close();

	return exitCode;
}