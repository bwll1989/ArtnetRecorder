#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    receiver.setup();
    receiver.stopThread();
    pixdata1.allocate(512, 512, 1);
    pixdata1.setColor((0));
    texGray.allocate(pixdata1);
    WindowWidth=512;
    WindowHeight=512;
    ofSetWindowShape(WindowWidth,WindowHeight);
    isRecording=false;
    ofSetFrameRate(60);
    ofSetWindowTitle("ArtnetRecorder");
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->setWidth(WindowWidth);
//    gui->addHeader(":: drag me to reposition ::");
//    //设置可拖拽
    gui->addFRM();
    //显示fps
    gui->addButton("click")->setLabel("Click to record");
    gui->setVisible(false);
    ofSetWindowPosition(ofGetScreenWidth()/2-WindowWidth/2, ofGetScreenHeight()/2-WindowHeight/2);
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    data= new unsigned char[512];
}

//--------------------------------------------------------------
void ofApp::update(){
    
   
    list<unsigned int> universeList;
    
    while(receiver.hasMessage())
    //循环接收所有universes数据，直到所有universe,全部接收一遍
    {
        pixdata.allocate(512, 1, 1);
            receiver.getNextData(m);
            dataSize = m.getSize();
            m.readTo(data);
            if (std::find(universeList.begin(), universeList.end(), m.getUniverse())==universeList.end()) {
                universeList.push_back(m.getUniverse());
//                //每个循环获取universe列表
                pixdata.setFromPixels(data, 512, 1, OF_PIXELS_GRAY);
////                将获取的universe,每个数据分别作为颜色填入pixdata中
                pixdata.pasteInto(pixdata1, 0, m.getUniverse());
////                将pixdata的值粘贴到pixdata1中对应universe的行中
//                cout<<m.getUniverse()<<endl;
                pixdata.clear();
            }else{
                //如果universe数值重复，跳出循环
                cout<<universeList.size()<<endl;
                texGray.allocate(pixdata1);
                pixdata.clear();

                break;
                //跳出while循环
            }


    }
    
//
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(receiver.isThreadRunning()){
        texGray.draw(0,0);
    }
    
//
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(),2), 20, 20);
    cout<<"*******************************"<<endl;
        
}
void ofApp::onButtonEvent(ofxDatGuiButtonEvent(e)){
    if(e.target->is("click")){
        isRecording=!isRecording;
        if(isRecording==true){
            gui->getButton("click")->setLabel("Recording");
            receiver.startThread();
        }else{
            gui->getButton("click")->setLabel("Click to record");
            receiver.stopThread();
        }
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='g'){
        if(gui->getVisible()){
            gui->setVisible(false);
        }else{
            gui->setVisible(true);
        }
    }
    if(key=='p'||key==' '){
        isRecording=!isRecording;
        if(isRecording==true){
            gui->getButton("click")->setLabel("Recording");
            receiver.startThread();
        }else{
            gui->getButton("click")->setLabel("Click to record");
            receiver.stopThread();
        }
    }

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
