#ifndef solution_hpp
#define solution_hpp

#include <fstream>
#include <sstream>
#include <iostream>

#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

class Solution{
public:
    //各関数
    void getallData();
    void simulateXYGred();
    //get
    unsigned int getWidth(); /* 画像の横サイズ */
    unsigned int getHeight(); /* 画像の縦サイズ */
    unsigned int getMax_value(); /* 最大輝度値 */
    unsigned int getXSplit(); //xSplit 横の分割数
    unsigned int getYSplit(); //ySplit 縦の分割数
    unsigned int getLimmit(); //selectLimmit 選択可能回数
    unsigned int getSelectRate(); //selectedRate 選択レート
    unsigned int getExRate(); //exchangeRate 交換レート
    //set
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setMax_value(unsigned int max_value);
    void setXSplit(unsigned int xSplit);
    void setYSplit(unsigned int ySplit);
    void setLimmit(unsigned int Limmit);
    void setSelectRate(unsigned int selectRate);
    void setExRate(unsigned int exRate);
    //コンストラクタ
    Solution(
    unsigned int width, /* 画像の横サイズ */
    unsigned int height, /* 画像の縦サイズ */
    unsigned int max_value, /* 最大輝度値 */
    unsigned int xSplit,  //xSplit 横の分割数の分割数
    unsigned int ySplit, //ySplit 縦の分割数
    unsigned int Limmit, //selectLimmit 選択可能回数
    unsigned int selectRate, //selectedRate 選択レート
    unsigned int exRate //exchangeRate 交換レート
    );
    
private:
    //各変数
        unsigned int width; /* 画像の横サイズ */
        unsigned int height; /* 画像の縦サイズ */
        unsigned int max_value; /* 最大輝度値 */
        unsigned int xSplit;  //xSplit 横の分割数
        unsigned int ySplit; //ySplit 縦の分割数
        unsigned int Limmit; //selectLimmit 選択可能回数
        unsigned int selectRate; //selectedRate 選択レート
        unsigned int exRate; //exchangeRate 交換レート
};

#endif /* solution_hpp */
