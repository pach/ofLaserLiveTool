ofLaserAnimTool
===============

a toolbox to play and animate with laser.

The first block of an ilda lasers animation software based on openframeworks.

The software is for now completely in work in progress and their is still a lot to do before thinking of a really usable software. Soon! ;)

dependencies : 
- ofxCurvesTools
- ofxEtherdream : https://github.com/memo/ofxEtherdream
- ofxILDA : https://github.com/OmerShapira/ofxIlda
- ofxPolylineMerger : https://github.com/pach/ofxPolylineMerger
- ofxUI : https://github.com/rezaali/ofxUI
- ofxTween : https://github.com/arturoc/ofxTween


To build your own animation, you should herit from AnimatedStuff.h
Each AnimatedStuff class has a vector of polylines to send to the laser.

in your own animation class you'll have to :
- call the super class destructor in your class destructor
- implement the setup(string name) function
  -> call the super class setup
  -> name a type for the animation
  -> do your stuff, create your UI
- implement the update() function
  -> do your stuff to update your polyline(s)

in AnimManager.cpp
- add a #include for your new class
- in setupGui -> add a button for your new class
- in GuiEvent -> do something with that button
- in createNewAnimation -> create a new animation of your new kind if your button is used
   -> type as to be the type you named in the class;