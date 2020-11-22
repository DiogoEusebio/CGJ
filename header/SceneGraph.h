#pragma once

#include <iostream>
#include <chrono>
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
		std::chrono::system_clock::time_point start_time, current_time;
		enum AnimationState {START, END, ONGOING, REVERSE};
		AnimationState state = START;
	public:
		void setRoot(SceneNode* node);
		SceneNode* getRoot();
		void setCamera(Camera* cam);
		void destroy();
		void draw();
		void translate(vec3 v);
		void animate();
	};
};
