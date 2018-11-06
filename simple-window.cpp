#include <stdio.h> // printf
#include <unistd.h> // sleep
#include <string>

#include <GLFW/glfw3.h>

bool running = true;

int window_width = 1024;
int window_height = 768;


std::string engine_version = "Game Engine v0.1";

bool create_main_window( int windowWidth, int windowHeight );
void clean_up();

int main()
{
  int time_running_sec = 0;

  printf( (engine_version + "\n").c_str() );

  // Create Main Window
  if ( !create_main_window( window_width, window_height ) )
    {
      printf( "Failed to create main window!\n" );
    }

  // Start Game Engine
  while ( running )
    {
      printf( "run time(sec): %i\n", time_running_sec );
      sleep( 1 );
      time_running_sec++;
      if ( time_running_sec == 30 )
	{
	  printf( "Time has reached 30s. Engine Done.\n" );
	  clean_up();
	  return 0;
	}
    }
  return 0;
}

bool create_main_window( int windowWidth, int windowHeight )
{
  if ( !glfwInit() )
    {
      printf( "Failed to initialize GLFW!\n" );
      return false;
    }
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); // Set minimum OpenGl Version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3 ); // Set maximum OpenGl Version
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  GLFWwindow* window;
  window = glfwCreateWindow(windowWidth, windowHeight, engine_version.c_str(), NULL, NULL);

  return true;
}

void clean_up()
{
  printf( "clean up - engine terminated!\n" );
  glfwTerminate();
}
