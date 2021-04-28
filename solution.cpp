#include <fstream>
#include <sstream>
#include <iostream>

#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

#include "solution.hpp"

using namespace std;


void Solution::getallData(){
    cout << "画像サイズ(横,縦) : (" << this->width << "," << this->height << ")" << endl;
    cout << "最大輝度値 : " << this->max_value<< endl;
    cout << "xSplit 横の分割数の分割数 : " << this->xSplit << endl;
    cout << "ySplit 横の分割数の分割数 : " << this->ySplit << endl;
    simulateXYGred();
    cout << "selectLimmit 選択可能回数 : " << this->Limmit << endl;
    cout << "selectedRate 選択レート : " << this->selectRate << endl;
    cout << "exRate 交換レート:" << this->exRate << endl;
}

void Solution::simulateXYGred(){
    for(int i =0;i<this->ySplit;i++){
        for(int j = 0;j<this->xSplit;j++){
            cout << "⬜️" ;
        }
        cout << endl;
    }
}
//get
unsigned int Solution::getWidth(){
    return this->width;
}
unsigned int Solution::getHeight() {
    return this->height;
}
unsigned int Solution::getMax_value() {
    return this->max_value;
}
unsigned int Solution::getXSplit(){
    return this->xSplit;
}
 unsigned int Solution::getYSplit(){
    return this->xSplit;
}
unsigned int Solution::getLimmit(){
    return this->Limmit;
}
 unsigned int Solution::getSelectRate(){
     return this->selectRate;
}
 unsigned int Solution::getExRate(){
     return this->exRate;
}
//set
void Solution::setWidth(unsigned int width){
    this->width = width;
}
void Solution::setHeight(unsigned int height){
    this->height = height;
}
void Solution::setMax_value(unsigned int max_value){
    this->max_value = max_value;
}
void Solution::setXSplit(unsigned int xSplit){
    this->xSplit = xSplit;
}
void Solution::setYSplit(unsigned int ySplit){
    this->ySplit = ySplit;
}
void Solution::setLimmit(unsigned int Limmit){
    this->Limmit = Limmit;
}
void Solution::setSelectRate(unsigned int selectRate){
    this->selectRate = selectRate;
}
void Solution::setExRate(unsigned int exRate){
    this->exRate = exRate;
}
//コンストラクタ
Solution::Solution(
unsigned int width, /* 画像の横サイズ */
unsigned int height, /* 画像の縦サイズ */
unsigned int max_value, /* 最大輝度値 */
unsigned int xSplit,  //xSplit 横の分割数の分割数
unsigned int ySplit,  //ySplit 縦の分割数の分割数
unsigned int Limmit, //selectLimmit 選択可能回数
unsigned int selectRate, //selectedRate 選択レート
unsigned int exRate //exchangeRate 交換レート
){
    cout << "genelate new solution data" << endl;
    this->width = width;
    this->height = height;
    this->max_value = max_value;
    this->xSplit = xSplit;
    this->ySplit = ySplit;
    this->Limmit = Limmit;
    this->selectRate = selectRate;
    this->exRate = exRate;
};
