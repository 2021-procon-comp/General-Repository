#ifndef INCLUDE_GUARD_DRAW_HPP //これはインクルードガードと呼ばれるもので、二重インクルードを防ぐためのもの
#define INCLUDE_GUARD_DRAW_HPP
//このファイルは主にppmファイルをGUIとして描画する関数を書いたもの
#include <fstream>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

void read_txtheader(string *magic_number,int *gridx,int *gridy,int *select_limit,
                    int *select_rate,int *change_rate,int *picture_width,
                    int *picture_height,int *max_light,int *grid_size){ //受け取ったテキストファイルのヘッダーを読み込みます
    
    ifstream file("output.txt");
    string line_string;
    int line_number =0;
    
    //各数値をファイルから読み取ります
    
    getline(file, line_string);
    *magic_number = line_string;
    
    cout <<"マジックナンバー:"<<*magic_number << endl;
    
    file >> line_number;
    *gridx = line_number;
    file >> line_number;
    *gridy = line_number;
    
    cout << "横分割数:" << *gridx << " " << "縦分割数:" <<*gridy << endl;
    
    file >> line_number;
    *select_limit = line_number;
    
    cout << "選択可能回数:" << *select_limit << endl;
    
    file >> line_number;
    *select_rate = line_number;
    file >> line_number;
    *change_rate = line_number;
    
    cout << "選択コスト変換レート:" << *select_rate << " " << "交換コスト変換レート:" <<*change_rate << endl;
    
    file >> line_number;
    *picture_width = line_number;
    file >> line_number;
    *picture_height = line_number;
    
    cout << "画像の横サイズ:" << *picture_width << " " << "画像の縦サイズ:" << *picture_height << endl;
    
    file >> line_number;
    *max_light = line_number;
    
    cout << "最大輝度値:" << *max_light << endl;
    
    *grid_size = *picture_width / *gridx;
    cout << "分割画像の一辺のサイズ:" << *grid_size << endl;
}

typedef struct ido{ //盤面を管理する構造体
    int gox;
    int goy;
    int rot;
} Ido;

void swap(Ido &a, Ido &b){ //swap関数
    Ido tmp;
    tmp = a;
    a = b;
    b = tmp;
}

struct pixel16{//16進数のvector配列を管理する構造体
    string r;
    string g;
    string b;
};

struct pixel10{//10進数のvector配列を管理する構造体
    int r;
    int g;
    int b;
};

struct answer{
    string xy;
    int x;
    int y;
    int r;
    string s;
};

int xh(char c){ //16進を10進に
    int x;
    if(c <= '9') x = c-'0';
    else x = (c<'G') ? (c-'A'+10) : (c-'a'+10);
    return x;
}

char hx(int x){ //10進を16進に
    char r;
    if(x <= 9) r = x+'0';
    else r = x+'A'-10;
    return r;
}

vector<vector<pixel10>> read_txtdata(int width,int height){ //データを読み込みます
    vector<vector<pixel10>> data10(height,vector<pixel10>(width));//10進数でRGB値を保存
    std::ifstream file("output.txt");
    char tmp[2];
    string trash;
    for(int i = 0;i < 6; i++) std::getline(file, trash);//ヘッダーは要らないので読み取るだけ
    
    for(int i = 0;i < height; i++){
        for(int j = 0;j < width; j++){ //2重for文で1文字ずつ読み取り2文字に合体してRGBとして構造体に保存
            file.get(tmp[0]);
            file.get(tmp[1]);
            data10[i][j].r = xh(tmp[0])*16 + xh(tmp[1]);
            
            file.get(tmp[0]);
            file.get(tmp[1]);
            data10[i][j].g = xh(tmp[0])*16 + xh(tmp[1]);
            
            file.get(tmp[0]);
            file.get(tmp[1]);
            data10[i][j].b = xh(tmp[0])*16 + xh(tmp[1]);
        }
        //file.get(one_size);//textに改行がある際にコメントアウトを外すこと
        //file.get(one_size);
    }
    return data10;//10進数のデータを返す
}

void write_movedata(vector<vector<Ido>> m){
    ofstream file("input.txt");
    file << m.size() << " " << m[0].size() << endl;
    for(int j = 0; j < m[0].size(); j++){
        for(int i = 0; i < m.size(); i++){
            for(int y = 0; y < m[0].size(); y++){
                for(int x = 0; x < m.size(); x++){
                    if(m[x][y].gox == i && m[x][y].goy == j){
                        file << x << " " << y << " " << m[x][y].rot << " ";
                    }
                }
            }
        }
        file << endl;
    }
}



#endif
