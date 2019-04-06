#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	for (int z = -120; z <= 120; z += 30) {

		int start = ofGetFrameNum() * 0.5 + (z + 150) * 0.1;
		for (int param_start = start; param_start < start + 100; param_start += 10) {

			vector<glm::vec3> vertices;
			vector<glm::vec3> sub_vertices;
			for (int param = param_start; param <= param_start + 8; param++) {

				glm::vec3 location = glm::vec3(this->make_point(300, param), z + 10);
				glm::vec3 sub_location = glm::vec3(this->make_point(300, param), z - 10);

				vertices.push_back(location);
				sub_vertices.push_back(sub_location);

				if (param % 25 == 0) {

					std::reverse(sub_vertices.begin(), sub_vertices.end());

					ofBeginShape();
					ofVertices(vertices);
					ofVertices(sub_vertices);
					ofEndShape(true);

					vertices.clear();
					sub_vertices.clear();

					vertices.push_back(location);
					sub_vertices.push_back(sub_location);
				}
			}

			std::reverse(sub_vertices.begin(), sub_vertices.end());

			ofBeginShape();
			ofVertices(vertices);
			ofVertices(sub_vertices);
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}