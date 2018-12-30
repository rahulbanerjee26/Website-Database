/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: baner103
 *
 * Created on November 29, 2018, 2:23 PM
 */

#include <iostream>
#include <sstream>
#include "DBentry.h"
#include "TreeNode.h"
#include "TreeDB.h"

using namespace std;

int main(int argc, char** argv) {
    TreeDB Websites;
    string line;
    cout<<"> ";
    getline(cin,line);
    while(!cin.eof()){
        string cmnd;
        stringstream lin(line);
        lin>>cmnd;
        //Insert
        if(cmnd == "insert"){
            string _name;
            unsigned int IP;
            string status;
            bool stat;
            lin>>_name>>IP>>status;
            //sets status to true/false based on user's input
            if(status == "active")
                stat = true;
            else
                stat = false;
            DBentry* item = new DBentry(_name,IP,stat);
            if(Websites.insert(item))
                cout<<"Success"<<endl;
            else
                cout<<"Error: entry already exists"<<endl;
        }
        //Search
        if(cmnd == "find"){
            string _name;
            lin>>_name;
            DBentry* item = Websites.find(_name);
            if(item == nullptr)
                cout<<"Error: entry does not exist"<<endl;
            else
                cout<<*item;
        }
        //Delete one node
        if(cmnd == "remove"){
            string _name;
            lin>>_name;
            if(Websites.remove(_name))
                cout<<"Success"<<endl;
            else
                cout<<"Error: entry does not exist"<<endl;
        }
        //Display all nodes
        if(cmnd == "printall"){
            cout<<Websites;
        }
        //Print the probecount
        if(cmnd == "printprobes"){
            string _name;
            lin>>_name;
            DBentry* item = Websites.find(_name);
            if(item == nullptr)
                cout<<"Error: entry does not exist"<<endl;
            else{
                Websites.printProbes();
            }
        }
        //Delete All
        if(cmnd == "removeall"){
            Websites.clear();
            cout<<"Success"<<endl;
        }
        //Count number of Active Nodes
        if(cmnd == "countactive"){
            Websites.countActive();
        }
        //Update the status of node
        if(cmnd == "updatestatus"){
            string _name,status;
            lin>>_name>>status;
            bool stat;
            //sets status to true/false based on user's input
            if(status == "active")
                stat = true;
            else
                stat = false;
            DBentry* item = Websites.find(_name);
            if(item == nullptr)
                cout<<"Error: entry does not exist"<<endl;
            else{
                item->setActive(stat);
                cout<<"Success"<<endl;
            }
        }
        cout<<"> ";
        getline(cin,line);
    }
    return 0;
}

