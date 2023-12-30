#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

struct Forest {
  int weight;
  int root;
};


struct Tree {
  int left;
  int right;
  int parent;
};

struct Code {
    int length;
    string coding;
};

Forest forest[256];
Tree tree[520];
Code code[520];
FILE* f, * g;

void getMin(Forest forest[], int size_forest, int& pos1, int& pos2) {
    pos1 = 0;
    pos2 = 0;
    for (int i = 0; i <= size_forest; i++) {
        if (forest[i].weight < forest[pos1].weight) {
            pos1 = i;
        }
    }
    if (pos2 == pos1){
        pos2 = 1;
    }
    for (int i = 0; i <= size_forest; i++) {
        if (forest[pos2].weight > forest[i].weight && i!= pos1) {
            pos2 = i;
        }
    }
}

int main()
{

    f = fopen("input.txt", "rb");
    g = freopen("output.txt", "w", stdout);

  int freq[256];
  for (int i = 0; i < 256; i++)
    freq[i] = 0;

  unsigned char ch;

  while (fscanf(f, "%c", &ch) != -1)
    freq[ch]++;
  //for (auto x : freq)
  //  cout << x << ' ';

  int size_forest = -1;
  int size_tree = -1;

  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
        size_forest++;
        size_tree++;
        forest[size_forest].root = size_forest;
        forest[size_forest].weight = freq[i];
    }
  }

  for(int i = 0; i <= size_forest; i++){
    tree[i].left = -1;
    tree[i].right = -1;
    tree[i].parent = -1;
  }

  int pos1 = 0;
  int pos2 = 0;

  while (size_forest > 0) {
    getMin(forest, size_forest, pos1, pos2);
    size_tree++;
    //size_forest--;
    tree[size_tree].left = forest[pos1].root;
    tree[size_tree].right = forest[pos2].root;
    tree[size_tree].parent = -1;

    tree[forest[pos1].root].parent = size_tree;
    tree[forest[pos2].root].parent = size_tree;

    forest[pos1].weight += forest[pos2].weight;
    forest[pos1].root = size_tree;
    forest[pos2] = forest[size_forest];
    size_forest--;
    //size_tree++;

  }
  for (int i = 0; i < size_tree; i++) {
    cout << tree[i].left << ' ' << tree[i].right << ' ' << tree[i].parent << '\n';
  }
    cout << endl << endl << endl;

    int cnt = 0;
    for(int i = 0; i < size_tree; i++){
        int n = i;
        while(tree[n].parent != -1){
            if (tree[tree[n].parent].left == tree[n].parent){
                code[i].coding += '0';
                code[i].length++;
            }
            else if (tree[tree[n].parent].right == tree[n].parent){
                code[i].coding += '1';
                code[i].length++;
            }
            n = tree[n].parent;
        }
        reverse(code[i].coding.begin(), code[i].coding.end());
        cout << code[i].coding << ' ' << code[i].length << endl;
        cnt++;

    }


    unsigned char byte = 0, cnt_bit = 0;
    while(fscanf(f, "%c", &ch) != -1){
        auto temp_code = code[ch];
        for(int i = 0; i < temp_code.length; i++){
            byte <<= 1;
            byte += temp_code.coding[i];
            cnt_bit++;
            if(cnt_bit == 8){
                fprintf(g, "%c", byte);
                byte = 0;
                cnt_bit = 0;
            }
        }
    }


    //for (int i = 0; i < cnt; i++) {
      //  cout << code[i].length << ' ' << code[i].coding;
    //}

}

//aaaaaabbbbbbbbbbcaaaaaabbbbbbbbbcddddbbbbcceeeeeeeeeeeeedddbbbdeeeeebbbbbcccccceeeebbbbcccccbbbbbeee
