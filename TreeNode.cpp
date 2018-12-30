#include "TreeNode.h"

TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
    left = nullptr;
    right = nullptr;
}

void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}

void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}

TreeNode* TreeNode::getRight() const{
    return right;
}

TreeNode* TreeNode::getLeft() const {
    return left; 
}

DBentry* TreeNode::getEntry() const{
    return entryPtr;
}

TreeNode::~TreeNode(){
    delete entryPtr;
}
