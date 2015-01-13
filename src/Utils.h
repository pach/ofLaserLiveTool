//
//  Utils.h
//  LaserLiveTool
//
//  Created by pach on 03/01/15.
//
//

#pragma once

#include "ofMain.h"

static vector<string> getOSCcmd(string msg){
    vector<string> returnOSC;
    
    string cmd ;
    
    int ces = msg.find_first_of("/");
    
    if (ces != -1) {
        if (ces == 0){
            msg = msg.substr(ces+1);
            cmd = msg;
            ces = msg.find_first_of("/");
            if (ces != -1) {
                cmd = msg.substr(0, ces);
                msg = msg.substr(ces);
            }
        }
        else{
            cmd = msg.substr(0, ces);
            msg = msg.substr(ces);
        }
    }
    
    returnOSC.push_back(cmd);
    returnOSC.push_back(msg);
    
    return returnOSC;
}
