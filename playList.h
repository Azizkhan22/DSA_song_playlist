#ifndef PLAYLIST_H
#define PLAYLIST_H

class Node {
private:
    char song[50];
    char artist[40];
    Node* next;
    Node* prev;

public:
    Node(char* song,char* artist);
    Node* getNext();            
    void setNext(Node* n);      
    Node* getPrev();            
    void setPrev(Node* p);      
    char* getSong();
    char* getArtist();
};

class playList {
private:
    Node* head;
    Node* current;

public:
    playList();
    void addSong_end(char* songName, char* artist);  
    void addSong_start(char* songName, char* artist);
    void addSong_pos(char* songName, char* artist, char* pos);
    void deleteSong(char* song);
    void playSong();
    void nextSong();
    void prevSong();
    void display();
    void displayReverse();
    bool searchSong(char* song_search);
    void savePlaylist(char* file);
    void loadPlaylist(char* file);
};

#endif 
