#include <iostream>
#include <fstream>
#include "playList.h"

using namespace std;

Node::Node(char* s,char* a) : next(nullptr), prev(nullptr) {
    for (int i=0; i<50; i++){
        song[i] = s[i];             //Construcutor of Node class
        artist[i] = a[i];
    }
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* n) {
    next = n;
}

Node* Node::getPrev() {
    return prev;
}

void Node::setPrev(Node* p) {
    prev = p;
}
char* Node::getSong(){
    return Node::song;
} 
char* Node::getArtist(){
    return Node::artist;
} 
            //Constructor for playList Class

playList::playList() : head(nullptr), current(head) {}

void playList::addSong_end(char* songName,char* artistName) {
    Node* newnode = new Node(songName, artistName);  // a new node with the song name
    if (head == nullptr) {
        head = newnode;
        head->setNext(head);  // Circular reference to itself
        head->setPrev(head);
        return;
    }

    Node* temp = head;
    while (temp->getNext() != head) {  //Traverse to the last node
        temp = temp->getNext();
    }

    temp->setNext(newnode);    // Link the last node to the new node
    newnode->setPrev(temp);    // Set the previous pointer of the new node
    newnode->setNext(head);    // Circular: new node points to head
    head->setPrev(newnode);    // Circular: head's previous points to new node
}

void playList::addSong_start(char* songName,char* artistName) {
    Node* newnode = new Node(songName, artistName); 
    if (head == nullptr) {
        head = newnode;
        head->setNext(head);  // Circular reference to itself
        head->setPrev(head);
        return;
    }
    Node* last = head->getPrev(); // Last node
    newnode->setNext(head);
    newnode->setPrev(last);
    head->setPrev(newnode);
    last->setNext(newnode);
    head = newnode;
}

bool playList::searchSong(char* song_search) {
    if (head == nullptr) {
        return false;  // Empty playlist
    }

    current = head;
    do {
        char* song = current->getSong();
        int i = 0;
        
        // Comparing the two strings character by character
        while (song[i] != '\0' && song_search[i] != '\0') {
            if (song[i] != song_search[i]) {
                break;  
            }
            i++;
        }

        if (song[i] == '\0' && song_search[i] == '\0') {
            return true;  // Song found
        }

        current = current->getNext();  // Move to the next node
    } while (current != head); 

    return false;  // Song not found
}

void playList::addSong_pos(char* songName, char* artist, char* pos){
    if (head == nullptr){
        cout<<"Play list is empty\n";
    }

    if (searchSong(pos) == true){
        Node* newnode = new Node(songName,artist);
        newnode->setNext(current->getNext());
        newnode->setPrev(current);
        current->setNext(newnode);
        current = head;
    }
    else{
        cout<<"Song not found!\n";
    }
}

void playList::deleteSong(char* song){
    if (head == nullptr){
        cout<<"Play list is empty\n";
        return;
    }
    if (searchSong(song) == true){
        Node* toDelete = current;
        toDelete->getPrev()->setNext(toDelete->getNext());
        toDelete->getNext()->setPrev(toDelete->getPrev());
        
        if (toDelete== head) { // If deleting head, update head
            head = toDelete->getNext();
        }
        delete toDelete;
        current = head;  
        cout << "Song deleted from the playlist.\n";
    }
    else{
        cout<<"Song not found!\n";
    }
}

void playList::playSong(){
    if (head == nullptr){
        cout<<"Play list is empty\n";
        return;
    }
    if (current == nullptr) {
        current = head; // playing from the head if current is nullptr
    }
    
    char* song = current ->getSong();
    char* artist = current -> getArtist();
    cout<<"\t\t\tNow playing -> "<<song<<" by "<<artist<<endl;
    
}
void playList::nextSong(){
    if (current == nullptr) {
        cout << "No current song to play next.\n";
        return; 
    }
    current = current->getNext();
    playSong();
}

void playList::prevSong(){
    if (current == nullptr) {
        cout << "No current song to play previous.\n";
        return; 
    }
    current = current->getPrev();
    playSong();
}

void playList::display(){
    if (head == nullptr){
        cout<<"Play list is empty\n";
    }
    else {
        Node* temp = head;
        int i=1;
        do {
            char* s = temp->getSong();
            char* a = temp-> getArtist();
            cout<<i<<": Song name: "<<s<<" | "<<"Artist name: "<<a<<endl;
            temp = temp->getNext();
            i++;
        }while (temp != head);
    }
}

void playList::displayReverse(){
    if (head == nullptr){
        cout<<"Play list is empty\n";
    }
    else {
        Node* temp = head->getPrev();
        int i=1;
        do {
            char* s = temp->getSong();
            char* a = temp-> getArtist();
            cout<<i<<": Song name: "<<s<<" | "<<"Artist name: "<<a<<endl;
            temp = temp->getPrev();
        }while (temp->getPrev() != head);
    }
}

void playList::savePlaylist(char* filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    Node* temp = head;
    if (temp == nullptr) {
        cout<< "Playlist is empty.\n";
        return;
    }

    do {
        outFile << temp->getSong() << "," << temp->getArtist() << "\n"; // Save song and artist
        temp = temp->getNext();
    } while (temp != head);

    outFile.close();
    cout << "Playlist saved successfully.\n";
}

void playList::loadPlaylist(char* filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    char song[50], artist[40];
    while (inFile.getline(song, 50, ',') && inFile.getline(artist, 40)) {
        addSong_end(song, artist); // Use the method to add songs to the playlist
    }

    inFile.close();
    cout << "Playlist loaded successfully.\n";
}
