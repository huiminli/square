#include "stdafx.h"
#include "timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct SDL {
public:
	~SDL() {
		SDL_Quit();
	}
};

struct SDL_WindowDeleter
{
	void operator()(SDL_Window *window) const
	{
		SDL_DestroyWindow(window);
	}
};

struct SDL_GLContextDeleter {
	void operator()(SDL_GLContext glContext) const
	{
		SDL_GL_DeleteContext(glContext);
	}
};

void startMainLoop() {
  //The frames per second
  const int FRAMES_PER_SECOND = 20;

  //Main loop flag
  bool quit = false;
  
  //Event handler
  SDL_Event e;

  //The frame rate regulator
  Timer fps;

  //Temp variable for testing frame
  int frame = 1;

  //While application is running
  while( !quit )
  {
    //Start the frame timer
    fps.start();

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 )
    {
      //User requests quit
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
      
      //Handle event on models
    }

    //Update screen and render
    printf("current frame: %d", frame);

    //Increment the frame counter
    frame++;

    //If we want to cap the frame rate
    if((fps.get_ticks() < 1000 / FRAMES_PER_SECOND ))
    {
      //Sleep the remaining frame time
      SDL_Delay((1000 / FRAMES_PER_SECOND ) - fps.get_ticks());
    }
  }
}

int main( int argc, char* args[] )
{
  SDL sdl;
  if(SDL_Init( SDL_INIT_VIDEO ) < 0)
  {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  std::unique_ptr<SDL_Window, SDL_WindowDeleter> window(SDL_CreateWindow(
      "SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));

  if(!window)
  {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
      return 1;
  }

  std::unique_ptr<void, SDL_GLContextDeleter> glContext(SDL_GL_CreateContext(window.get()));

  glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRectf(0.0, 0.0, 100.0, 100.0);
  SDL_GL_SwapWindow(window.get());

  startMainLoop();

  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
