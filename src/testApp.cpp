#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    background.allocate(1197, 1188, OF_IMAGE_COLOR_ALPHA);
    brush.allocate(brushWidth, brushWidth, OF_IMAGE_COLOR_ALPHA);
    
    background.loadImage("piet-mondrian.jpg");
    brush.loadImage("brush.png");
    brush.update();

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    background.draw(0, 0);
    brush.draw(brushCoords.x, brushCoords.y);

}


void testApp::absorbColor(float mouseX, float mouseY){
    
    for (int x = 0; x < brushWidth; x++) {
        for (int y = 0; y < brushWidth; y++){
            brush.setColor(x, y, background.getColor(mouseX + x, mouseY + y));
        }
    }
    brush.update();
    
}

void testApp::smudge(float mouseX, float mouseY){
    
    for (int x = 0; x < brushWidth; x++) {
        for (int y = 0; y < brushWidth; y++){
            ofColor brushPixelColor = brush.getColor(x, y);
            ofColor backgroundPixelColor = background.getColor(mouseX + x, mouseY + y);
            
            float dist = ofDist(x, y, brushWidth/2, brushWidth/2);
            float c2 = sqrt( pow(brushWidth / 2, 2.0) + pow(brushWidth / 2, 2.0) );
            float blurDist = ofMap(dist, 0.0, c2 , 0.0, 1.0);
            
            backgroundPixelColor.r = ofLerp(brushPixelColor.r, backgroundPixelColor.r, blurDist);
            backgroundPixelColor.g = ofLerp(brushPixelColor.g, backgroundPixelColor.g, blurDist);
            backgroundPixelColor.b = ofLerp(brushPixelColor.b, backgroundPixelColor.b, blurDist);
            //backgroundPixelColor *= brushPixelColor;
            background.setColor(mouseX + x, mouseY + y, backgroundPixelColor);
            brush.setColor(x, y, backgroundPixelColor);
        }
    }
    background.update();
    brush.update();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    brushCoords.x = x;
    brushCoords.y = y;
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    
//    for (int i = 1; i < steps + 1; i++){
//        float lerpedX = ofLerp(brushCoords.x, x, i / steps);
//        float lerpedY = ofLerp(brushCoords.y, y, i / steps);
//        
//
//        
//    }
    
     smudge(x, y);
    
    brushCoords.x = x;
    brushCoords.y = y;


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    absorbColor(x, y);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
