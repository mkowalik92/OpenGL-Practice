#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
  // Shader program ID
  unsigned int shaderProgramID;
  Shader (const char* vsPath, const char* fsPath)
  {
    // Strings holding vertex/fragment shader source code
    std::string vsCodeStr, fsCodeStr;
    // Declare file streams
    std::ifstream vsFileStream, fsFileStream;
    // Make sure ifstream objects can throw exceptions
    vsFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
      // Open fsFileStream
      vsFileStream.open(vsPath);
      fsFileStream.open(fsPath);
      // Declare string streams
      std::stringstream vsStringStream, fsStringStream;
      // Read file buffer into string buffer
      vsStringStream << vsFileStream.rdbuf();
      fsStringStream << fsFileStream.rdbuf();
      // Close file streams
      vsFileStream.close();
      fsFileStream.close();
      // Convert string buffer object to string
      vsCodeStr = vsStringStream.str();
      fsCodeStr = fsStringStream.str();
    }
    catch (std::ifstream::failure error)
    {
      printf("error: Unable to read shader file!\n");
    }

    // Convert string to char* because OpenGL is written in C
    const char* vsCode = vsCodeStr.c_str();
    const char* fsCode = fsCodeStr.c_str();

    // Temporary vertex and fragment shader ID's
    unsigned int vertexShader, fragmentShader;

    // Create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Set source code for vertex shader
    glShaderSource(vertexShader, 1, &vsCode, NULL);
    // Compile vertex shader
    glCompileShader(vertexShader);
    // Check if vertex shader compilation was successful
    CheckCompileErrors(vertexShader, "VERTEX");

    // Create fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Set source for fragment shader
    glShaderSource(fragmentShader, 1, &fsCode, NULL);
    // Compile fragment shader
    glCompileShader(fragmentShader);
    // Check if fragment shader compilation was successful
    CheckCompileErrors(fragmentShader, "FRAGMENT");

    // Create shader program
    shaderProgramID = glCreateProgram();
    // Attach vertex and fragment shaders to shader program
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    // Link shaders
    glLinkProgram(shaderProgramID);
    // Check if shader linking was successful
    CheckCompileErrors(shaderProgramID, "PROGRAM");
    // Delete shaders after linking to shader program (no longer needed)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }
  void Use ()
  {
    glUseProgram(shaderProgramID);
  }

private:
  void CheckCompileErrors (unsigned int ID, std::string type)
  {
    int success;
    char errorMessage[1024];
    if (type != "PROGRAM")
    {
      glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
      if (!success)
      {
        glGetShaderInfoLog(ID, 1024, NULL, errorMessage);
        printf("error: %s SHADER compilation failure!\n%s\n", type.c_str(), errorMessage);
      }
    }
    else
    {
      glGetProgramiv(ID, GL_LINK_STATUS, &success);
      if (!success)
      {
        glGetProgramInfoLog(ID, 1024, NULL, errorMessage);
        printf("error: SHADER %s linking failure!\n%s\n", type.c_str(), errorMessage);
      }
    }
  }
};
#endif
