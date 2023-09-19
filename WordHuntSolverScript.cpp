#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>


using namespace std;

vector<vector<string>> board(4, vector<string>(4, "x"));
vector<string> anslist;


struct TrieNode{
    map<string, TrieNode*> next;
    bool full_word = false;
};

struct TrieNode*head = new TrieNode;

void make_trie()
{
    ifstream dictionary_file;
    dictionary_file.open("dictionary.txt");
    string word;
    if(dictionary_file.is_open()){
        while(!dictionary_file.eof()){
            struct TrieNode *curr = head;
            getline(dictionary_file, word);
            for(int i = 0; i< word.length(); i++)
            {
                string letter = string(1,word[i]);
                if((curr->next).find(letter) == (curr->next).end()){
                    (curr ->next)[letter] = new TrieNode;
                }
                curr = (curr -> next)[letter];
                if(i==word.length()-1){
                    curr -> full_word = true;
                }
            }
        }
    }
}

void search(vector<vector<string>> board, int r, int c, string word, vector<vector<int>> visited, TrieNode* node){
        
        if(r < 0 || r >= 4 || c < 0 || c >= 4){
            return;
        }
        if(visited[r][c] > 0){
            return;
        }
        if((node -> next).find(board[r][c]) == (node -> next).end()){
            return;
        }
    
        word = word + board[r][c];

        visited.at(r).at(c)++;

        if(word.length() >= 3 && (node->next)[board[r][c]] -> full_word){
            anslist.push_back(word);
        }
        vector<pair<int,int>> directions = 
            {make_pair(1,0),
            make_pair(0,1),
            make_pair(-1,0),
            make_pair(0,-1),
            make_pair(1,-1),
            make_pair(-1,1),
            make_pair(1,1),
            make_pair(-1,-1)
            };

        for(pair<int, int> elem : directions){
            int x = elem.first;
            int y = elem.second;
            int new_r = r + x;
            int new_c = c + y;
            search(board, new_r, new_c, word, visited, (node->next)[board[r][c]]);
        }
    visited.at(r).at(c) = 0;
}

bool compareLength (const string &a, const string &b){
   return a.length() < b.length();
}


int main(){
    make_trie();
    cout<<"Word hunt is a game where players are given a 4x4 board with random letters"<<endl;
    cout<<"Players must drag their finger across the board to mkae as many words as possible"<< endl;
    cout<<"The longer the word the more points the word will yield for the player"<<endl;
    cout<<"the player with the most points at the end fo the time limit wins the game"<<endl;
    cout<<"This program will help you find all the valid words in any given word hunt board."<<endl;
    cout<<endl;
    cout<<"To find all the words you need to enter the letters in your board like so: "<<endl;
    cout<<endl;
    cout<<" a | b | c | d "<<endl;
    cout<<" e | f | g | h "<<endl;
    cout<<" i | j | k | l "<<endl;
    cout<<" m | n | o | p "<<endl;
    cout<<endl;
    cout<<"Example Input for the board above: abcdefghijklmnop"<<endl;
    cout<<endl;
    cout<< "Enter Board: "<< endl;
    string input;
    cin >> input;
    while(input.size() != 16){
        cout<<"Invalid Input, Try Again: "<<endl;
        cin >> input;
    }
    int count = 0;
    string let;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            let = string(1,input[count]);
            board[i][j] = let;
            count++;
        }
    }
    

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            vector<vector<int>> visited(4, vector<int>(4, 0));
            search(board, i, j, "", visited, head);
        }
    }
    anslist.erase(std::unique(anslist.begin(), anslist.end()), anslist.end());

    std::sort(anslist.begin(), anslist.end(), compareLength);
    
    int wordScore=0;
    int totScore=0;

    cout << "Valid Words: " << endl;
    cout <<endl;
    
    for (const std::string &s : anslist) {
        if(s.size() == 3){
            wordScore = 100;
        }else if(s.size() == 4){
            wordScore = 400;
        }else if(s.size() == 5){
            wordScore = 800;
        }else if(s.size() == 6){
            wordScore = 1400;
        }else if(s.size() == 7){
            wordScore = 2200;
        }else if(s.size() == 8){
            wordScore = 3200;
        }else if(s.size() == 9){
            wordScore = 4400;
        }
        totScore = totScore + wordScore;
        std::cout << s << " (Word Score: " << wordScore << ")" <<endl; 
        cout<<endl;
    }
    cout << "Total Score: " << totScore<< endl;

}