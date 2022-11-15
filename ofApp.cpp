#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int span = 20;
	float threshold = 0.55;
	float frame_param = ofGetFrameNum() * 0.05;
	float coordinate_param = 0.0065;
	ofColor face_color, line_color;

	for (int len = 300; len >= 280; len -= 5) {

		face_color.setHsb(ofMap(len, 280, 300, 0, 255), 180, 255);
		line_color = ofColor(0);
		int z = len + span * 0.1;

		float angle;
		glm::highp_mat4 rotation;
		for (int i = 0; i <= 6; i++) {

			for (int x = -len; x <= len; x += span) {

				for (int y = -len; y <= len; y += span) {

					if (i <= 4) {

						angle = PI * 0.5 * i;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
					}

					if (i == 5) {

						angle = PI * 0.5;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
					}

					if (i == 6) {

						angle = PI * 0.5 * 3;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
					}


					glm::vec3 noise_location = glm::vec4(x, y, z, 0) * rotation;
					auto noise_value = ofNoise(glm::vec4(noise_location * coordinate_param, frame_param));
					if (noise_value < threshold) { 
					
						glm::vec3 loc_1 = glm::vec4(x - span, y, z, 0) * rotation;
						auto noise_1 = ofNoise(glm::vec4(loc_1 * coordinate_param, frame_param));
						glm::vec3 loc_2 = glm::vec4(x, y + span, z, 0) * rotation;
						auto noise_2 = ofNoise(glm::vec4(loc_2 * coordinate_param, frame_param));
						glm::vec3 loc_3 = glm::vec4(x + span, y, z, 0) * rotation;
						auto noise_3 = ofNoise(glm::vec4(loc_3 * coordinate_param, frame_param));
						glm::vec3 loc4 = glm::vec4(x, y - span, z, 0) * rotation;
						auto noise_4 = ofNoise(glm::vec4(loc4 * coordinate_param, frame_param));

						vector<glm::vec3> vertices;

						vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

						auto index = this->face.getNumVertices();
						this->face.addVertices(vertices);

						this->face.addColor(face_color);
						this->face.addColor(face_color);
						this->face.addColor(face_color);
						this->face.addColor(face_color);

						this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
						this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
					}
					else {

						glm::vec3 loc_1 = glm::vec4(x - span, y, z, 0) * rotation;
						auto noise_1 = ofNoise(glm::vec4(loc_1 * coordinate_param, frame_param));
						glm::vec3 loc_2 = glm::vec4(x, y + span, z, 0) * rotation;
						auto noise_2 = ofNoise(glm::vec4(loc_2 * coordinate_param, frame_param));
						glm::vec3 loc_3 = glm::vec4(x + span, y, z, 0) * rotation;
						auto noise_3 = ofNoise(glm::vec4(loc_3 * coordinate_param, frame_param));
						glm::vec3 loc4 = glm::vec4(x, y - span, z, 0) * rotation;
						auto noise_4 = ofNoise(glm::vec4(loc4 * coordinate_param, frame_param));

						vector<glm::vec3> vertices;

						vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
						vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

						if (noise_1 < threshold || x == -len) {

							this->frame.addVertex(vertices[0]);
							this->frame.addVertex(vertices[3]);

							this->frame.addColor(line_color);
							this->frame.addColor(line_color);

							this->frame.addIndex(this->frame.getNumVertices() - 1);
							this->frame.addIndex(this->frame.getNumVertices() - 2);
						}

						if (noise_2 < threshold || y == len) {

							this->frame.addVertex(vertices[2]);
							this->frame.addVertex(vertices[3]);

							this->frame.addColor(line_color);
							this->frame.addColor(line_color);

							this->frame.addIndex(this->frame.getNumVertices() - 1);
							this->frame.addIndex(this->frame.getNumVertices() - 2);
						}

						if (noise_3 < threshold || x == len) {

							this->frame.addVertex(vertices[1]);
							this->frame.addVertex(vertices[2]);

							this->frame.addColor(line_color);
							this->frame.addColor(line_color);

							this->frame.addIndex(this->frame.getNumVertices() - 1);
							this->frame.addIndex(this->frame.getNumVertices() - 2);
						}

						if(noise_4 < threshold || y == -len) {

							this->frame.addVertex(vertices[0]);
							this->frame.addVertex(vertices[1]);

							this->frame.addColor(line_color);
							this->frame.addColor(line_color);

							this->frame.addIndex(this->frame.getNumVertices() - 1);
							this->frame.addIndex(this->frame.getNumVertices() - 2);

						}
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());
	ofRotateX(ofGetFrameNum() * 1.5);

	this->face.draw();
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}