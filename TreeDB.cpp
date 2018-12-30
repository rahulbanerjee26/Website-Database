#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

TreeDB::TreeDB(){
    root = nullptr;
    probesCount = 0;
}

bool TreeDB::insertHelp(DBentry* item, TreeNode* location){
    //Key matches
    if(item->getName() == location->getEntry()->getName()){
        delete item;
        return false;
    }
    //Inserts to the left if Key is smaller
    if(item->getName() < location->getEntry()->getName() ){
        if(location->getLeft() == nullptr){
            TreeNode* node = new TreeNode(item);
            location->setLeft(node);
            return true;
        }
        else
           return insertHelp(item, location->getLeft());
    }
    //Inserts to the right if Key is bigger
    if(item->getName() > location->getEntry()->getName() ){
        if(location->getRight() == nullptr){
            TreeNode* node = new TreeNode(item);
            location->setRight(node);
            return true;
        }
        else
            return insertHelp(item, location->getRight());
    }
    
}

bool TreeDB::insert(DBentry* newEntry){
    //To insert first node, i.e root node
    if(root == nullptr){
        TreeNode* node = new TreeNode(newEntry);
        root = node;
        root->setLeft(nullptr);
        root->setRight(nullptr);
        return true;
    }
    else
       return insertHelp(newEntry, root);
}

//pre-order traversal
DBentry* TreeDB::search(string name, TreeNode* location){
    if(location == nullptr) //base case
        return nullptr;
    probesCount++;
    if(name == location->getEntry()->getName())
        return location->getEntry();
    if(name < location->getEntry()->getName())
        return search(name,location->getLeft());
    if(name > location->getEntry()->getName())
        return search(name,location->getRight());
}

DBentry* TreeDB::find(string name){
    if(root == nullptr)
        return nullptr;
    probesCount = 0;
    return search(name,root);
}

TreeNode* TreeDB::maximum(TreeNode* location){
    if(location->getRight() == nullptr)
        return location;
    return maximum(location->getRight());
}

TreeNode* TreeDB::deleteHelp(string name, TreeNode* location){
    if(location == nullptr) //Base Case
        return location;
    else if(name < location->getEntry()->getName()){
      location->setLeft( deleteHelp(name,location->getLeft()) );
    }
    else if(name > location->getEntry()->getName()){
      location->setRight( deleteHelp(name,location->getRight()) );
    }
    if(name == location->getEntry()->getName()){
        //Case: Node has no chile,i.e its a leaf 
        if(location->getLeft() == nullptr && location->getRight() == nullptr){
            delete location;
            return nullptr;
        }
        //Case: Node has one child
        else if(location->getLeft() == nullptr && location->getRight() != nullptr){
             TreeNode* temp = location->getRight();
             delete location;
             return temp;
        }
        else if(location->getLeft() != nullptr && location->getRight() == nullptr){
             TreeNode* temp = location->getLeft();
             delete location;
             return temp;
        }
        //Case: Node has two children
        else if(location->getLeft() != nullptr && location->getRight() != nullptr){
            //returns max node in left subtree
            TreeNode *temp= maximum(location->getLeft());
            //Copies data of max node in left subtree to the node to be deleted
            location->getEntry()->setName(temp->getEntry()->getName());
            location->getEntry()->setIPaddress(temp->getEntry()->getIPaddress());
            location->getEntry()->setActive(temp->getEntry()->getActive());
            //deletes the max node in the left subtree and adjusts links accordingly
            location->setLeft( deleteHelp(temp->getEntry()->getName(),location->getLeft()) );
        }
    }
    return location;
}

bool TreeDB::remove(string name){
    if(root == nullptr)
        return false;
    DBentry* item = find(name);
    if(item == nullptr)
        return false;
    else{
        root = deleteHelp(name,root);
        return true;
    }
}

//Traverses and deletes all nodes
void TreeDB::deleteAll(TreeNode* location){
    if(location == nullptr)
        return;      
    deleteAll(location->getLeft());
    deleteAll(location->getRight());
    delete location;
}

void TreeDB::clear(){
    if(root == nullptr)
        return; 
    else
    deleteAll(root);
    root = nullptr;
}

void TreeDB::printProbes() const{
    cout<<probesCount<<endl;
}

int TreeDB::countActiveHelp(TreeNode* location, int total) const{
    if(location == nullptr )
        return total;
    if(location->getEntry()->getActive())
        total++;
    //Keeps on adding to the previous value of total 
    total = countActiveHelp(location->getLeft(),total);
    total = countActiveHelp(location->getRight(),total);
    return total;
}

void TreeDB::countActive() const{
    int total=0;
    if(root == nullptr){
        cout<<"0";
        return;
    }
    cout<< countActiveHelp(root,total)<<endl;
}

//In-order traversal to display in ascending order
void TreeDB::displayAll(TreeNode* location){
    if(location == nullptr)
        return;
    displayAll(location->getLeft());
    cout<<*(location->getEntry());
    displayAll(location->getRight());

}

//overloading << operator
ostream& operator<< (ostream& out, TreeDB& rhs){
    if(rhs.root == nullptr)
        return (out);
    rhs.displayAll(rhs.root);
}

TreeDB::~TreeDB(){
    clear();
}
