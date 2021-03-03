//
//  StackNode.h
//  Chapter_5
//
//  Created by Hayden Crabb on 10/31/18.
//  Copyright © 2018 Coconut Productions. All rights reserved.
//

#ifndef StackNode_h
#define StackNode_h

struct stackNode {
    int row = 0;
    int column = 0;
    bool checkedTop = false;
    bool checkedRight = false;
    bool checkedDown = false;
    bool checkedLeft = false;
    bool setFirstAsT = false;
    
    stackNode * next;
    stackNode * previous;
};


#endif /* StackNode_h */
