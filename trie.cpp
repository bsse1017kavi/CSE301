#include<bits/stdc++.h>
using namespace std;

#define ALPHABET_SIZE 26

struct TrieNode
{
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

TrieNode* makeNode()
{
    TrieNode *tNode = new TrieNode;
    for(int i=0;i<ALPHABET_SIZE;i++)
    {
        tNode->children[i] = NULL;
    }

    tNode->isEndOfWord = false;

    return tNode;
}

void insert(TrieNode *root,string key)
{
    TrieNode *current_node = root;
    for(int i=0;i<key.size();i++)
    {
        int index = key[i]-'a';
        if(!current_node->children[index])
        {
            current_node->children[index] = makeNode();
        }

        current_node = current_node->children[index];
    }

    current_node->isEndOfWord = true;
}

bool search(TrieNode *root,string key)
{
    TrieNode *current_node = root;
    for(int i=0;i<key.length();i++)
    {
        int index = key[i]-'a';

        if(!current_node->children[index])
        {
            return false;
        }

        current_node = current_node->children[index];
    }

    return (current_node!=NULL && current_node->isEndOfWord);
}

int main(void)
{
    TrieNode *root = makeNode();

    string keys[] = {"dragon","demon","go","gone"};

    int n = sizeof(keys)/sizeof(keys[0]);

    for(int i=0;i<n;i++)
    {
        insert(root,keys[i]);
    }

    while(true)
    {
        string temp;
        cin >> temp;

        if(temp=="q") break;

        search(root,temp)?cout <<"Yes\n":cout << "No" << endl;
    }
}
