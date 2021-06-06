#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct Color{
  double r;
  double g;
  double b;
}Pixel;

//SplitBlock DATA[xgrid * ygrid];

class SplitBlock{
private:
//各変数
     //分割画像の番号
     int SplitNumber; //0 - n ( 00 - zz )
    
    //実際の画像データ (保存形式は要検討)
     Pixel data;
    
     //分割画像の隣接画像の保存関数　隣接画像がない場合 -> -1
     string up;
     string bottom;
     string left;
     string right;

     //分割画像の隣接画像の類似度 -> 0 - 100
     const int upAP;
     const int bottomAP;
     const int leftAP;
     const int rightAP;

     //向き 0,1,2,3
     const int direction;

     //分割画像の隣接画像の保存関数4つに値が入っているか？　(true : false)
     bool completeRestore;

     //分割画像の種類　例（角 : 3, 辺 : 2, 内部 : 1)
     const int type;

public:
  //get系
    int getSplitNumber();
    string getup();
    string getbottom();
    string getleft();
    string getright();
    const int getupAP();
    const int getbottomAP();
    const int getleftAP();
    const int getrightAP();
    const int getdirection();
    bool getcompleteRestore();
    const int gettype();
  //set系
    void setSplitNumber(int num);
    void setup(string num);
    void setbottom(string num);
    void setleft(string num);
    void setright(string num);
    void setupAP(int num);
    void setbottomAP(int num);
    void setleftAP(int num);
    void setrightAP(int num);
    void setdirection(int num);
    void setcompleteRestore(bool num);
    void settype(int num);
    
//constract
SplitBlock(
                int SplitNumber,
                string up,
                string bottom,
                string left,
                string right,
                const int upAP,
                const int bottomAP,
                const int leftAP,
                const int rightAP,
                const int direction,
                bool completeRestore,
                const int type
           );

//destruct
    

};
