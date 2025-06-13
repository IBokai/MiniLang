#ifndef AST_NODE_H
#define AST_NODE_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../token/token.h"

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void printInfo() = 0;
    virtual int calculate() = 0;
};
#endif
