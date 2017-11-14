@Grab(group="org.lwjgl", module="lwjgl", version="3.1.3")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="3.1.3")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="3.1.3")

//Windows 
@Grab(group="org.lwjgl", module="lwjgl", version="3.1.3",classifier="natives-windows")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="3.1.3",classifier="natives-windows")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="3.1.3",classifier="natives-windows")
//Linux  
@Grab(group="org.lwjgl", module="lwjgl", version="3.1.3",classifier="natives-linux")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="3.1.3",classifier="natives-linux")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="3.1.3",classifier="natives-linux")   

import org.lwjgl.*;
import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryStack.*;
import static org.lwjgl.system.MemoryUtil.*;
//
println(System.getProperty("os.name"));
//
if ( !glfwInit() )
    throw new IllegalStateException("Unable to initialize GLFW");

final int width = 640;
final int height = 480;

glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
long window = glfwCreateWindow(width, height, "Hello World!", NULL, NULL);
if ( window == NULL )
    throw new RuntimeException("Failed to create the GLFW window");

monitor = glfwGetPrimaryMonitor();
mode = glfwGetVideoMode(monitor);
printf("%d %d\n",mode.width(),mode.height());
glfwSetWindowPos(window, (int)(mode.width()/2 - width/2), (int)(mode.height()/2 - height/2));

glfwMakeContextCurrent(window);
glfwSwapInterval(1);
glfwShowWindow(window);

GL.createCapabilities();
// Set the clear color
glClearColor(0.2f, 0.3f, 0.3f, 0.0f);

while ( !glfwWindowShouldClose(window) )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
    glfwSwapBuffers(window); // swap the color buffers
    // Poll for window events. The key callback above will only be
    // invoked during this call.
    glfwPollEvents();
}

glfwDestroyWindow(window);
glfwTerminate();
