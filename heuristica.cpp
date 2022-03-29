#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct items {
  int i = -1;
  int j = -1;
  int val = 0;
};

int w(char a, char b) {
  if (a == b && a != '-') {
    return 2;
  } else {
    return -1;
  }
}

int main() {
  string a;
  string b;

  int n = 0;
  int m = 0;

  cin >> n >> m;
  cin >> a >> b;

  vector<vector<items>> H(n + 1, vector<items>(m + 1));

  items maior_valor;
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      if (i == 0 || j == 0) {
        H[i][j].val = 0;
      } else if (i > 0 && j > 0) {
        int diag = H[i - 1][j - 1].val + w(a[i - 1], b[j - 1]);
        int dele = H[i - 1][j].val - 1;
        int inse = H[i][j - 1].val - 1;

        H[i][j].val = max({0, diag, dele, inse});

        if (max({0, diag, dele, inse}) == diag) {
          H[i][j].i = i - 1;
          H[i][j].j = j - 1;
        } else if (max({0, diag, dele, inse}) == inse) {
          H[i][j].i = i;
          H[i][j].j = j - 1;
        } else if (max({0, diag, dele, inse}) == dele) {
          H[i][j].i = i - 1;
          H[i][j].j = j;
        }
        if (maior_valor.val < H[i][j].val) {
          maior_valor.i = i;
          maior_valor.j = j;
          maior_valor.val = H[i][j].val;
        }
      }
    }
  }
  // printa matriz
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      cout << H[i][j].val << "  ";
    }
    cout << endl;
  }
  cout << endl;

  items atual;
  string a_;
  string b_;
  atual.val = -1;
  atual.i = 1;
  atual.j = 1;
  do {
    if (atual.val == -1) {
      if (maior_valor.val >= 0) {
        a_ = a[maior_valor.i];
        b_ = b[maior_valor.j];
        atual.i = H[maior_valor.i][maior_valor.j].i;
        atual.j = H[maior_valor.i][maior_valor.j].j;
        atual.val = H[atual.i][atual.j].val;
      }
    } else {
      if (maior_valor.i == atual.i) {
        b_ += b[atual.j];
        a_ += '-';
        maior_valor.i = atual.i;
        maior_valor.j = atual.j;
        atual.i = H[maior_valor.i][maior_valor.j].i;
        atual.j = H[maior_valor.i][maior_valor.j].j;
        atual.val = H[maior_valor.i][maior_valor.j].val;
      } else if (maior_valor.j == atual.j) {
        a_ += a[atual.i];
        b_ += '-';
        maior_valor.i = atual.i;
        maior_valor.j = atual.j;
        atual.i = H[maior_valor.i][maior_valor.j].i;
        atual.j = H[maior_valor.i][maior_valor.j].j;
        atual.val = H[maior_valor.i][maior_valor.j].val;
      } else {
        a_ += a[atual.i];
        b_ += b[atual.j];
        maior_valor.i = atual.i;
        maior_valor.j = atual.j;
        atual.i = H[maior_valor.i][maior_valor.j].i;
        atual.j = H[maior_valor.i][maior_valor.j].j;
        atual.val = H[maior_valor.i][maior_valor.j].val;
      }
    }
  } while (atual.i >= 0 and atual.j >= 0);

  // area de print do resultado
    for(int i = a_.size()-1; i>0; i--){
      cout << a_[i];
    }
    cout << endl;
    for(int i = a_.size()-1; i>0; i--){
      if (b_[i] == a_[i]){
        cout << '*';
      } else {
        cout << '|';
      }
    }
    cout << endl;
    for(int i = b_.size()-1; i>0; i--){
      cout << b_[i];
    }
    cout << endl;
  return 0;
}