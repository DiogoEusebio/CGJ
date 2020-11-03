#include "../header/Shader.h"

void egn::Shader::createShaderProgram(const std::string& vs_file, const std::string& fs_file)
{	
	ProgramID = glCreateProgram();

	GLuint VertexShaderID = loadShader(ProgramID, GL_VERTEX_SHADER, vs_file);
	GLuint FragmentShaderID = loadShader(ProgramID, GL_FRAGMENT_SHADER, fs_file);
	glBindAttribLocation(ProgramID, VERTICES, "inPosition");

	glLinkProgram(ProgramID);
	checkLinkageError(ProgramID);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	ModelMatrix_UID = glGetUniformLocation(ProgramID, "ModelMatrix");
	ViewMatrix_UID = glGetUniformLocation(ProgramID, "ViewMatrix");
	ProjectionMatrix_UID = glGetUniformLocation(ProgramID, "ProjectionMatrix");
	Color_UID = glGetUniformLocation(ProgramID, "u_Color");

}

const GLuint egn::Shader::loadShader(const GLuint program_id, const GLenum shader_type, const std::string& filename)
{
	const GLuint shader_id = glCreateShader(shader_type);
	const std::string scode = read(filename);
	const GLchar* code = scode.c_str();
	glShaderSource(shader_id, 1, &code, 0);
	glCompileShader(shader_id);
	checkCompilationError(shader_id, filename);
	glAttachShader(program_id, shader_id);
	return shader_id;
}

const std::string egn::Shader::read(const std::string& filename)
{
	std::ifstream ifile(filename);
	std::string shader_string, line;
	while (std::getline(ifile, line))
	{
		shader_string += line + "\n";
	}
	return shader_string;
}

void egn::Shader::destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramID);
}

const GLuint egn::Shader::checkCompilationError(const GLuint shader_id, const std::string& filename)
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, log);
		std::cerr << "[" << filename << "] " << std::endl << log;
		delete[] log;
	}
	return compiled;
}

void egn::Shader::checkLinkageError(const GLuint program_id)
{
	GLint linked;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		char infolog[1024];
		glGetProgramInfoLog(ProgramID, 1024, NULL, infolog);
		std::cout << "The program failed to link with the error:" << infolog << std::endl;
	}
}
