# Solution Class (solution.cpp)
各関数の説明
## Solution::Solution(...)
コンストラクタです。引数は変数の数と同じ

    unsigned int width, /* 画像の横サイズ */
    unsigned int height, /* 画像の縦サイズ */
    unsigned int max_value, /* 最大輝度値 */
    unsigned int xSplit,  //xSplit 横の分割数の分割数
    unsigned int ySplit, //ySplit 縦の分割数
    unsigned int Limmit, //selectLimmit 選択可能回数
    unsigned int selectRate, //selectedRate 選択レート
    unsigned int exRate //exchangeRate 交換レート
の８つ。一気にデータを入力したいときは直接コンストラクタに、実際の処理では1とかをいれて初期化してからset関数を使用。

## unsigned int Solution::get~()
インスタンスクラスのデータを戻り値として取得します。private変数が8つあるので8種。
## void Solution::set~(unsigned int ~)
インスタンスの変数に値をセットします。
## void Solution::getalldata()
全ての変数の値を出力します。
## void Solution::simulateXYGred()
縦横分割を視覚化。いらない
