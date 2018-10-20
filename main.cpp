//
//  helpers.h
//  pl-a1
//
//  Created by Aleida Olvera on 9/28/18.
//  Copyright © 2018 Aleida Olvera. All rights reserved.
//

// Free free to use constructs #included below.

#include <iostream>
#include <vector>
#include <queue>
#include "helpers.h"

using namespace std;


/************************
 ****** main **************
 **************************/
// Two Modes or Options for execution:
// (option 1) no commandline arg: repeatedly calls the reader to facilitate the active interpreter
// (option 2) ADD THIS:  if provided a commandline arg, should read and interpret RuM code in the file, once complete,
// then it should continue with option 1

int main() {
    while(true) {
        reader(); // read input and store globally to userinput
        
        if (userinput[inputleng] == ENDOFINPUT) {
            queue <Token> tokenList;
            try {
                tokenList = tokenize();
            } catch (const invalid_argument& e) {
                cout << "There was an error tokenizing expression:\n" << e.what() << endl;
            }
            string final_result, result;
            // cout << "Evaluating expression entered...\n";
            try {
                final_result = eval_queue(tokenList, result);
            } catch (const invalid_argument& e) {
                cout << "There was an error parsing expression:\n" << e.what();
            }
            cout << final_result << endl;
            // cout << "Input read into buffer, ready to tokenize." << endl;
        }
        else {
            cout << "Input Error: token found but end of input expected:  " << userinput[inputleng] << endl;
        }
    }
    
    return 0;
}
