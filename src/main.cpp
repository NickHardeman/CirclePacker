#include "ofAppGlutWindow.h"
#include "testApp.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 810, 810, OF_WINDOW);
	ofRunApp(new testApp());
}
