#include <iostream>
#include <string>
#include <math.h> 
#include <GL/glew.h>
#include <cstring>
#include <fstream>

#define VERTICES 0
#define COLORS 3

namespace egn
{
	class Shader
	{
	public:
		GLuint VertexShaderID, FragmentShaderID, ProgramID = 0;
		GLint ModelMatrix_UID, ViewMatrix_UID, ProjectionMatrix_UID, Color_UID;
		const GLuint UBO_BP = 0;
	public:
		void createShaderProgram(const std::string& vertexShaderF, const std::string& fragmentShaderF);
		void destroyShaderProgram();
	protected:
		const GLuint loadShader(const GLuint program_id, const GLenum shader_type, const std::string& filename);
		const std::string read(const std::string& filename);
		const GLuint checkCompilationError(const GLuint shader_id, const std::string& filename);
		void checkLinkageError(const GLuint program_id);
	};
}