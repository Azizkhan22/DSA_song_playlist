#include <iostream>
#include "playList.h"       //Header file added 
using namespace std;
int main(){
    playList album;         //playList class object made
    char song[50];
    char artist[40];
    char file[30];
    int choice;                 //Main menu
    do{
        cout<< "\nMenu:\n";
        cout<< "1. Add Song at the end              2. Add Song at the start\n";
        cout<< "3. Add Song after a song            4. Play Song\n";
        cout<< "5. Play Next Song                   6. Play Previous Song\n";
        cout<< "7. Search a song                    8. Delete a song\n";
        cout<< "9. Display play list                10. Display play list reverse\n";
        cout<< "11. Load play list                  12. Save play list\n";
        cout<< "13. Exit\n";
        cout<< "Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cin.ignore();               //clearing buffer
            cout<<"Enter Song name: ";
            cin.getline(song,50);
            cout<<"Enter Artist name: ";
            cin.getline(artist,40);
            album.addSong_end(song,artist);     //adding song at the end
            break;
        case 2:
            cin.ignore();
            cout<<"Enter Song name: ";
            cin.getline(song,50);
            cout<<"Enter Artist name: ";\
            cin.getline(artist,40);
            album.addSong_start(song,artist);       //Adding the song at the the start
            break;
        case 3:
            cin.ignore();
            cout<<"After which song you want to add the new song\n";
            char s[50];
            cin.getline(s,50);
            cout<<"Enter Song name you want to add: ";
            cin.getline(song,50);
            cout<<"Enter Artist name: ";\
            cin.getline(artist,40);
            album.addSong_pos(song,artist,s);   //Song added after the song specified by the user
            break;
        case 4:
            album.playSong();  //Current pointed Song being played 
            break;
        case 5:
            album.nextSong();   //Current updated to the next song
            break;
        case 6:
            album.prevSong();      //Current updated to the prev song
            break;
        case 7:
            cin.ignore();
            cout<<"Enter the song you want to search\n";
            cin.getline(song,50);
            album.searchSong(song);     //Searching the specified song
            break;
        case 8:
            cin.ignore();
            cout<<"Enter the song you want to delete\n";
            cin.getline(song,50);
            album.deleteSong(song);     //deleting the specified song
            break;
        case 9:
            album.display();    //Displaying all the songs
            break;
        case 10:
            album.displayReverse();     //Displaying in reverse
            break;
        case 11:
            cin.ignore();
            cout<<"Enter the file name: ";
            cin.getline(file,30);
            album.loadPlaylist(file);     //Loading the file for playlist
            break;
        case 12:
            cin.ignore();
            cout<<"Enter the file name: ";
            cin.getline(file,30);
            album.savePlaylist(file);   //Saving the plalist in a file
            break;
        default:
            break;
        }
    }while (choice >=1 && choice < 13);

    return 0;
}