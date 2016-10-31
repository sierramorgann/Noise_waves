#include "ofApp.h"
#include "ofMesh.h"

int w = 100;
int h = 100;

float flying = 0;

ofColor water = (64, 164, 223);

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    for (int y = 0; y < h; y++) { //for each # of rows
        for (int x = 0; x < w; x++) { // for each # of columns
            mesh.addVertex(ofPoint((x - w/2) * 10, (y - h/2) * 10, 0 )); // make a new vertex
            mesh.addColor(water); // returns a color
        }
    }

    
    for (int y = 0; y < h-1; y++) { // with each iteration draw triangle
        for (int x = 0; x < w-1; x++) {
            int i1 = x + w * y;
            int i2 = x+1 + w * y;
            int i3 = x + w * (y+1);
            int i4 = x+1 + w * (y+1);
            
            mesh.addTriangle( i1, i2, i3 );
            mesh.addTriangle( i2, i4, i3 );
        }
        setNormals(mesh); //Set normals
        light.enable(); //enable light
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef(); //Get time
   
    flying += 0.1;
    
    float yoff = flying;
    for (int y=0; y<h; y++) {
        float xoff = 0;
        for (int x=0; x<w; x++) {
            int i = x + w * y; //Vertex index
            ofPoint p = mesh.getVertex( i ); //Get Perlin noise value
            float value = ofNoise( x * 0.04, y * 0.04, time * 0.5 ); //Change z-coordinate of vertex
            p.z = value * 100;
            mesh.setVertex( i, p ); //Change color of vertex
            mesh.setColor( i, ofColor(water) );
            xoff += 1;
        }
        yoff += 1;
    }
    setNormals(mesh); //Update the normals
}

//--------------------------------------------------------------
void ofApp::draw(){

    glEnable( GL_DEPTH_TEST );	//Enable z-buffering
    ofPushMatrix(); //Store the coordinate system
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 ); //Move the coordinate center to screen's center

    ofTranslate(-w/2, -h/2); //move to dispay in screen
    ofNoFill();
    ofRotate( 30, 1, 0, 0 );
    mesh.draw();//Draw mesh
    ofPopMatrix(); //Restore the coordinate system
    
}

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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