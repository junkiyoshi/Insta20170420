#pragma once

#include "ofMain.h"
#include "ofxBullet.h"

class ofApp : public ofBaseApp{

	public:

		~ofApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxBulletWorldRigid world;

		void onCollision(ofxBulletCollisionData& cdata);

		//ofCamera camera;
		ofEasyCam camera;

		float obstruction_size = 30;
		ofColor obstructions_color[5];
		vector<ofxBulletSphere*> obstructions;

		vector<ofColor> spheres_color;
		vector<ofxBulletSphere*> spheres;
};
