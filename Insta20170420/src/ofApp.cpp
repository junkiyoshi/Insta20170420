#include "ofApp.h"

ofApp::~ofApp() {

	for (ofxBulletSphere* tmp : this->obstructions) {
		delete tmp;
	}

	for (ofxBulletSphere* tmp : this->spheres) {
		delete tmp;
	}

	this->obstructions.clear();
	this->spheres.clear();
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Bullet");
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	world.setup();
	world.enableCollisionEvents();
	ofAddListener(world.COLLISION_EVENT, this, &ofApp::onCollision);
	world.setGravity(ofVec3f(0, 10, 0));
	//world.enableDebugDraw();
	world.setCamera(&camera);

	//camera.setTarget(ofVec3f(0, size / 2.f, 0));

	ofxBulletSphere* obstruction = new ofxBulletSphere();
	obstruction->create(world.world, ofVec3f(0, 0, 0), 0.0f, this->obstruction_size);
	obstruction->add();
	this->obstructions.push_back(obstruction);

	obstruction = new ofxBulletSphere();
	obstruction->create(world.world, ofVec3f(this->obstruction_size * 3, 0, 0), 0.0f, this->obstruction_size);
	obstruction->add();
	this->obstructions.push_back(obstruction);

	obstruction = new ofxBulletSphere();
	obstruction->create(world.world, ofVec3f(this->obstruction_size * -3, 0, 0), 0.0f, this->obstruction_size);
	obstruction->add();
	this->obstructions.push_back(obstruction);

	obstruction = new ofxBulletSphere();
	obstruction->create(world.world, ofVec3f(0, 0, this->obstruction_size * 3), 0.0f, this->obstruction_size);
	obstruction->add();
	this->obstructions.push_back(obstruction);

	obstruction = new ofxBulletSphere();
	obstruction->create(world.world, ofVec3f(0, 0, this->obstruction_size * -3), 0.0f, this->obstruction_size);
	obstruction->add();
	this->obstructions.push_back(obstruction);

	for (int i = 0; i < 5; i++) {
		this->obstructions_color[i] = ofColor(255);
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	if (ofGetFrameNum() % 15 == 0) {
		ofxBulletSphere* sphere = new ofxBulletSphere();
		sphere->create(world.world, ofVec3f(ofRandom(this->obstruction_size * -3, this->obstruction_size * 3), -120.f, ofRandom(this->obstruction_size * -3, this->obstruction_size * 3)), 1.0f, 5.0);
		sphere->setRestitution(1.0);
		sphere->add();
		this->spheres.push_back(sphere);

		ofColor color;
		color.setHsb(ofRandom(255), 255, 255);
		this->spheres_color.push_back(color);
	}

	world.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	glEnable(GL_DEPTH_TEST);

	camera.begin();

	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	
	//world.drawDebug();

	for (int i = 0; i < this->spheres.size(); i++) {
		ofSetColor(this->spheres_color[i]);
		this->spheres[i]->draw();
	}
	

	for (int i = 0; i < this->obstructions.size(); i++) {
		ofSetColor(this->obstructions_color[i]);
		this->obstructions[i]->draw();
	}

	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::onCollision(ofxBulletCollisionData& cdata) {

	int obs_index = -1;
	int sph_index = -1;

	for (int i = 0; i < this->obstructions.size(); i++) {
		if (*this->obstructions[i] == cdata) {
			cout << "Collision Obstractions : " << i << " | ";
			obs_index = i;
		}
	}

	for (int i = 0; i < this->spheres.size(); i++) {
		if (*this->spheres[i] == cdata) {
			cout << "Collision Spheres : " << i << " | ";
			sph_index = i;
		}
	}

	if (obs_index != -1 && sph_index != -1) {
		this->obstructions_color[obs_index] = this->spheres_color[sph_index];
	}

	cout << endl;
}