#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#define SIZE 9          //盤の大きさ//
#define FREE 0          
#define MARU 1          //先手//
#define BATU (-1)       //後手//
#define LINE 8          //勝ち筋の数
#define MARU_WIN 1      //先手の勝利//
#define BATU_WIN (-1)   //後手の勝利//
#define DRAW 0          //引き分け//
#define MAX_VALUE 2     //勝利する評価//
#define MIN_VALUE (-2)  //敗北する評価//
 
int think_maru(int n);  //先番の打ち方
int think_batu(int n);  //後手の打ち方
void memset(char v[]);  //初期化

/*勝ち筋の表記*/
const char line[LINE][3] = {      
    0, 1, 2,  3, 4, 5,  6, 7, 8,    //横の筋//
    0, 3, 6,  1, 4, 7,  2, 5, 8,    //縦の筋//
    0, 4, 8,  2, 4, 6,              //斜めの筋//
};

/*盤面の表記*/
char board[SIZE]; 

void memset(char v[]){
    for(int i=0; i<SIZE; i++) {
        v[i] = FREE;
    }
}

/*勝利判定を行う関数*/
int check_winner (void) {
    for(int i=0; i<LINE; i++){              //8本の直線を調べる
        int piece = board[ line[i][0] ];    //駒の種類
        if(piece != FREE &&                 //盤上に駒が置かれている
           piece == board[ line[i][1] ] &&  //盤上に置かれている
           piece == board[ line[i][2] ]) {  //盤上に置かれている
                return (piece == MARU ? MARU_WIN : BATU_WIN);   //駒の種類が先手が後手
           }
    }
    return DRAW;                            //結果が引き分け
}

/*先手の打ち方*/
int think_maru(int n) {
    int v, value = MIN_VALUE;               //先手の場合、価値が大きい方を
    for(int i=0; i<SIZE; i++) {             //盤上を全探索をしてみる
        if(board[i] != FREE) continue;      //盤上に石があるか
        board[i] = MARU;                    //試しに盤上に先手の石を置いてみる
        v = check_winner();                 //仮に石を置いてみて確かめる
        /*価値が引き分けて引数のnがSIZEを超えるまで見てみる*/
        if(v == DRAW && n < SIZE - 1) v = think_batu(n+1);  
        if(v > value) value = v;            //value(-2)よりvの価値が大きい場合
        board[i] = FREE;                    //試しに置いた石を消しておく
    }
    return value;                           //価値の結果を返す
}

/*後手の打ち方(先手の打ち方と同じ部分は省略)*/
int think_batu( int n ) {
    int v, value = MAX_VALUE;               //後手の場合、価値が小さい方を
    for(int i=0; i<SIZE; i++) {
        if(board[i] != FREE) continue;
        board[i] = BATU;
        v = check_winner();
        if(v == DRAW && n < SIZE - 1) v = think_maru(n + 1);
        if(v < value) value = v;            //value(2)より価値が小さい場合
        board[i] = FREE;
    }
    return value;
}

int main() {
    int v;
    for(int i=0; i<SIZE; i++) {
        memset(board);      //初期化
        board[i] = MARU;    //初手の打ち方を調べる
        v = think_batu(1);  //後手から考える
        cout << "初手 " << i << ": 評価値 " << v << endl; 
    }
}