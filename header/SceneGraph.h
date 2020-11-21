#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Constants.h"
#include "SceneNode.h"

namespace egn
{
	class SceneGraph {
	protected:
		SceneNode* root;
		Camera* camera;
		float animationTime = 0.0f;
	public:
		void setRoot(SceneNode* node);
		SceneNode* getRoot();
		void setCamera(Camera* cam);
		void destroy();
		void draw();
	};
};
