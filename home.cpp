#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "constellations.cpp"
#include "clusters.cpp"
#include "index_retrieve.cpp"
#include "correlationf.cpp"
#include "mst.cpp"
#include "table.cpp"

using namespace std;

int main()
{
    home:
    cout<<"************** ASTROEYE **************\n";
    cout<<"\nPlease refer to the codes and functions mentioned below to execute tasks:\n";
    cout<<"Code\tFunction\n";
    cout<<"1.\tGive catalog and observed object data to get the indexing of your observed objects within image.\n"
    <<"2.\tGive a converted starry night sky image to get the possible constellations present in it.\n"
    <<"3.\tGive coordinates to find clusters of galaxies.\n"
    <<"4.\tGive data on galaxies to find the shortest path/route between galaxies based on autocorrelated distance.\n"
    <<"5.\tExit\n"
	<<"Please Press Enter after completing any function to return to this screen\n";

    int ch = 0;
    while(ch<1 || ch>5){
        cout<<"Enter you ch: ";
        cin>>ch;
        if(ch<1 || ch>5){
            cout<<"Please Enter a valid code to execute function: \n";
        }
    }

    switch(ch){
        case 1: 
            getchar();
            indrev();
            getch();
            goto home;
        case 2:
            getchar();
            constellation();
            getch();
            goto home;
        case 3:
            getchar();
            cluster();
            getch();
            goto home;
        case 4:
            getchar();
            tb();
			cr();
			MST();
            getch();
            goto home;
        case 5:
            break;
    }

    cout<<"Thank YOU for using AstroEye!!"<<endl<<endl;
    getch();


    return 0;
}