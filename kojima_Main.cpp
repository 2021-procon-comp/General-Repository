//プログラムを実行、理解する際は以下を読んでおくことを推奨する
//このプログラムはppmファイルをtxtに変換した後に使うものである
//VScodeでtxtファイルを読み取る際.cppや.hppと同じsrcフォルダに入れるのではなく、起動フォルダであるAppに入れること
//vector<vector<pixel10>> data(picture_size[0],vector<pixel10>(picture_size[1]));みたいなのが度々出てくるが、これは構造体型vector配列というものである
//OpenSiv3Dを使っているため、わからないところは公式サイトで調べるといいhttps://siv3d.github.io/ja-jp/
//Siv3Dのmain関数はMain()でないと動かないため、必ず大文字にすること
//まじで変数多すぎて申し訳ない

#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "draw.hpp"
#include "output.hpp"

using namespace std;
#define rep(i, b) for(int i = 0; i < int(b); i++)

struct oparation{//操作の情報を保存する構造体
    string select_position;//選択画像位置
    int change_times;//交換回数
    string change_oparation;//交換操作
};

int Main()
{
    string magic_number; //マジックナンバー
    int gridx;//分割数
    int gridy;
    int select_limit;//選択可能回数
    int select_rate;//選択コスト変換レート
    int change_rate;//交換コスト変換レート
    int picture_width;//画像の縦横の大きさ
    int picture_height;
    int max_light; //最大輝度値
    int grid_size; //分割画像の一辺のサイズ
    int num_of_block;//分割された画像の数gridx*gridy
    
    int change_select_1=100000;
    int change_select_2=100000;
    int change_select_1_grid_img_x;
    int change_select_1_grid_img_y;
    int change_select_2_grid_img_x;
    int change_select_2_grid_img_y;
    
    bool grid_judge=0;//分割しているかの判定
    bool select_judge=0;//選択しているかの判定
    bool change_judge=0;//交換モードかの判定
    bool sorting_judge=1;//並べ替えモードかの判定
    bool answer_judge=0;
    
    int cursor_x=0;//クリックした際のx座標
    int cursor_y=0;//クリックした際のy座標
    
    int grid_img_x=0;//分割した画像の左上のx座標
    int grid_img_y=0;//分割した画像の左上のy座標
    
    int select_grid=0;//選択した分割画像の座標
    DynamicTexture texture_tmp;//分割画像を移動させる際に使うテンプ
    Image image_tmp;//画像内の座標と数値を入れ替える際に使うテンプ
    
    
    String select_grid16=U"00";//選択している座標の16進数表記
    
    const Font font(15, Typeface::Bold);//GUIに表示するフォントの定義
    
    vector<oparation> opalog;
    
    read_txtheader(&magic_number,&gridx,&gridy,&select_limit,
                   &select_rate,&change_rate,&picture_width,
                   &picture_height,&max_light,&grid_size);//ヘッダーを読み取る関数
    
    vector<vector<pixel10>> data(picture_width,vector<pixel10>(picture_height));//main関数内でデータを保存する
    
    data = read_txtdata(picture_width, picture_height);//読み取ったデータを保存
    
    num_of_block=gridx*gridy;//分割画像数の計算
    
    Window::Resize(picture_width+gridx*40, picture_height+gridx*40);//ウィンドウ生成
    Scene::SetBackground(Color(230, 230, 230));//背景色設定

    Image image(picture_width, picture_height, Palette::White);//分割前の画像の作成
    DynamicTexture texture(image);//分割前の画像を管理するクラス
    
    vector<DynamicTexture> block_grid;//分割後の画像を管理するクラス

    vector<vector<Ido>> mov(gridx, vector<Ido>(gridy));
    rep(y, gridy) rep(x, gridx){
        mov[x][y].gox = x;
        mov[x][y].goy = y;
        mov[x][y].rot = 0;
    }
    
    ifstream an("answer.txt");
    int ansc;
    string anss;
    char ansh;
    an >> anss >> ansc;
    vector<answer> ans(ansc);
    rep(i, ansc) {
        an >> ans[i].xy >> ans[i].r >> ans[i].s;
        ans[i].x = xh(ans[i].xy[0]);
        ans[i].y = xh(ans[i].xy[1]);
    }
    
    vector<Image> block;//分割画像を保存するvector配列
    for(int i=0;i<num_of_block;i++){
        block.emplace_back(grid_size, grid_size, Palette::White);//vector配列を一個ずつ拡張
    }
    
    for(int i_y=0;i_y<gridy;i_y++){
        for(int i_x=0;i_x<gridx;i_x++){
            for(int y=0;y<grid_size;y++){
                for(int x=0;x<grid_size;x++){
                    block[i_y*gridx+i_x][y][x]=Color(data[y + grid_size*i_y][x+grid_size*i_x].r,
                                                     data[y + grid_size*i_y][x+grid_size*i_x].g,
                                                     data[y + grid_size*i_y][x+grid_size*i_x].b);
                    //画像データを分割して保存する
                }
            }
            block_grid.emplace_back(block[i_y*gridx+i_x]);//vector配列を一個ずつ拡張
        }
    }
    
    int space = 0;
    while (System::Update())//Siv3Dでの動作を入れる
    {
        if(SimpleGUI::Button(U"分割", Vec2(picture_width+gridx*10, 20))){
            grid_judge=1;
            space=3;//分割ボタンを押したときの処理
        }
        if(SimpleGUI::Button(U"結合", Vec2(picture_width+gridx*10, 60))){
            grid_judge=0;
            space=0;//結合ボタンを押したときの処理
        }
        if(SimpleGUI::Button(U"選択解除", Vec2(picture_width+gridx*10, 100))){
            select_judge=0;//選択解除ボタンを押したときの処理
            select_grid=0;
        }
        if(SimpleGUI::Button(U"交換モード", Vec2(picture_width+gridx*10, 140))){
            select_judge=0;//選択解除ボタンを押したときの処理
            select_grid=0;
            change_judge=1;
            sorting_judge=0;
        }
        if(SimpleGUI::Button(U"並べ替えモード", Vec2(picture_width+gridx*10, 180))){
            sorting_judge=1;
            change_judge=0;
        }
        if(SimpleGUI::Button(U"確認モード", Vec2(picture_width+gridx*10, 220))){
            sorting_judge=0;
            change_judge=0;
            answer_judge=1;
        }
        for(int i_y=0;i_y<gridy;i_y++){
            for(int i_x=0;i_x<gridx;i_x++){
                block_grid[i_y*gridx+i_x].draw(i_x*grid_size+i_x*space, i_y*grid_size+i_y*space);//分割画像描画
            }
        }
        if(!change_judge){
            font(U"選択している座標:{}, {}"_fmt(select_grid%gridx, select_grid/gridx, Window::ClientSize())).draw(picture_width+gridx*10, 250, ColorF(0.25));
        }else{
            font(U"選択している座標:{}, {}"_fmt(select_grid%gridx+1, select_grid/gridx+1, Window::ClientSize())).draw(picture_width+gridx*10, 250, ColorF(0.25));
        }
        
        
        /*font(select_grid16).draw(picture_width+gridx*10, 210, ColorF(0.25));
        font(U"選択回数:2").draw(picture_width+gridx*10, 240, ColorF(0.25));
        font(U"移動:URULDL").draw(picture_width+gridx*10, 270, ColorF(0.25));*/
        if(sorting_judge){
            if(MouseL.down()){//分割画像をクリックして選択した際の表示
                for(int i_y=0;i_y<gridy;i_y++){
                    for(int i_x=0;i_x<gridx;i_x++){
                        cursor_x=Cursor::Pos().x;//カーソルの座標を代入
                        cursor_y=Cursor::Pos().y;
                        if(cursor_x >= i_x*grid_size+i_x*space && cursor_x <= (i_x+1)*grid_size+i_x*space &&
                           cursor_y >= i_y*grid_size+i_y*space && cursor_y <= (i_y+1)*grid_size+i_y*space){//判定を計算
                            grid_img_x=i_x*grid_size+i_x*space;//分割画像の左上のx,y座標を代入
                            grid_img_y=i_y*grid_size+i_y*space;
                            select_grid=i_y*gridx+i_x;//どの分割画像を選んだのか保存する
                        }
                    }
                }
                select_judge=1;
            }
        }
        if(select_judge){
            Rect(grid_img_x, grid_img_y, grid_size, grid_size)
            .drawFrame(4, 0, Palette::Black);
            if(KeyUp.down()){//上キーを押したとき
                if(select_grid-gridx<0){//一番上の画像を選択した際の処理
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid+gridx*(gridy-1)];
                    block_grid[select_grid+gridx*(gridy-1)]=texture_tmp;//①swap関数のようにTextureクラスの画像と画像を交換
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid+gridx*(gridy-1)];
                    block[select_grid+gridx*(gridy-1)]=image_tmp;//②こちらも同じくImageクラス上で交換
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx][gridy-1]);
                    select_grid+=gridx*(gridy-1);//③選択している画像の番号を変換
                }else{//一番上の画像以外なら
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid-gridx];
                    block_grid[select_grid-gridx]=texture_tmp;//①
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid-gridx];//②
                    block[select_grid-gridx]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx][select_grid/gridx-1]);
                    select_grid-=gridx;//③
                }
            }
            if(KeyDown.down()){//下キーを押したとき
                if(select_grid+gridx>num_of_block-1){
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid-gridx*(gridy-1)];
                    block_grid[select_grid-gridx*(gridy-1)]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid-gridx*(gridy-1)];
                    block[select_grid-gridx*(gridy-1)]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx][0]);
                    select_grid-=gridx*(gridy-1);
                }else{
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid+gridx];
                    block_grid[select_grid+gridx]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid+gridx];
                    block[select_grid+gridx]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx][select_grid/gridx+1]);
                    select_grid+=gridx;
                }
            }
            if(KeyRight.down()){//右キーを押したとき
                if((select_grid+1)%gridx==0){
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid-(gridx-1)];
                    block_grid[select_grid-(gridx-1)]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid-(gridx-1)];
                    block[select_grid-(gridx-1)]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[0][select_grid/gridx]);
                    select_grid-=(gridx-1);
                }else{
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid+1];
                    block_grid[select_grid+1]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid+1];
                    block[select_grid+1]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx+1][select_grid/gridx]);
                    select_grid++;
                }
            }
            if(KeyLeft.down()){//左キーを押したとき
                if(select_grid%gridx==0){
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid+(gridx-1)];
                    block_grid[select_grid+(gridx-1)]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid+(gridx-1)];
                    block[select_grid+(gridx-1)]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[gridx-1][select_grid/gridx]);
                    select_grid+=(gridx-1);
                }else{
                    texture_tmp=block_grid[select_grid];
                    block_grid[select_grid]=block_grid[select_grid-1];
                    block_grid[select_grid-1]=texture_tmp;
                    
                    image_tmp=block[select_grid];
                    block[select_grid]=block[select_grid-1];
                    block[select_grid-1]=image_tmp;
                    
                    swap(mov[select_grid%gridx][select_grid/gridx], mov[select_grid%gridx-1][select_grid/gridx]);
                    select_grid--;
                }
            }
            if(KeyX.down()){//Xキーを押したとき回転90度
                block_grid[select_grid].fill(block[select_grid].rotate90());
                mov[select_grid%gridx][select_grid/gridx].rot += 1;
                mov[select_grid%gridx][select_grid/gridx].rot %= 4;
                //Imageを90度回転させTextureクラスに保存
            }
            if(KeyZ.down()){
                block_grid[select_grid].fill(block[select_grid].rotate270());
                mov[select_grid%gridx][select_grid/gridx].rot += 3;
                mov[select_grid%gridx][select_grid/gridx].rot %= 4;
                //Imageを270度回転させTextureクラスに保存
            }
            grid_img_x=(select_grid%gridx)*(grid_size+space);//選択している画像の左上の座標を更新
            grid_img_y=(select_grid/gridx)*(grid_size+space);
        }
        select_grid16 = Unicode::Widen(conversion(select_grid%gridx, select_grid/gridx));
        
        if(change_judge){
            if(MouseL.down()){
                if(change_select_1==100000){
                    for(int i_y=0;i_y<gridy;i_y++){
                        for(int i_x=0;i_x<gridx;i_x++){
                            cursor_x=Cursor::Pos().x;//カーソルの座標を代入
                            cursor_y=Cursor::Pos().y;
                            if(cursor_x >= i_x*grid_size+i_x*space && cursor_x <= (i_x+1)*grid_size+i_x*space &&
                               cursor_y >= i_y*grid_size+i_y*space && cursor_y <= (i_y+1)*grid_size+i_y*space){//判定を計算
                                change_select_1_grid_img_x=i_x*grid_size+i_x*space;//分割画像の左上のx,y座標を代入
                                change_select_1_grid_img_y=i_y*grid_size+i_y*space;
                                change_select_1=i_y*gridx+i_x;//どの分割画像を選んだのか保存する
                            }
                        }
                    }
                }else{
                    for(int i_y=0;i_y<gridy;i_y++){
                        for(int i_x=0;i_x<gridx;i_x++){
                            cursor_x=Cursor::Pos().x;//カーソルの座標を代入
                            cursor_y=Cursor::Pos().y;
                            if(cursor_x >= i_x*grid_size+i_x*space && cursor_x <= (i_x+1)*grid_size+i_x*space &&
                               cursor_y >= i_y*grid_size+i_y*space && cursor_y <= (i_y+1)*grid_size+i_y*space){//判定を計算
                                change_select_2_grid_img_x=i_x*grid_size+i_x*space;//分割画像の左上のx,y座標を代入
                                change_select_2_grid_img_y=i_y*grid_size+i_y*space;
                                change_select_2=i_y*gridx+i_x;//どの分割画像を選んだのか保存する
                            }
                        }
                    }
                    if(change_select_2 != 100000){
                        texture_tmp=block_grid[change_select_2];
                        block_grid[change_select_2]=block_grid[change_select_1];
                        block_grid[change_select_1]=texture_tmp;
                        
                        image_tmp=block[change_select_2];
                        block[change_select_2]=block[change_select_1];
                        block[change_select_1]=image_tmp;
                        
                        change_select_1=100000;
                        change_select_2=100000;
                    }
                }
            }
        }
        
        if(answer_judge){
            answer_judge=0;
            rep(i, ansc){
                cout << ans[i].r << endl;
                select_grid = ans[i].x + ans[i].y * gridx;
                rep(j, ans[i].r){
                    ansh = ans[i].s[j];
                    cout << ansh;
                    if(ansh == 'U'){//上キーを押したとき
                        cout << "a";
                        if(select_grid-gridx<0){//一番上の画像を選択した際の処理
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid+gridx*(gridy-1)];
                            block_grid[select_grid+gridx*(gridy-1)]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid+gridx*(gridy-1)];
                            block[select_grid+gridx*(gridy-1)]=image_tmp;
                            
                            select_grid+=gridx*(gridy-1);
                        }else{//一番上の画像以外なら
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid-gridx];
                            block_grid[select_grid-gridx]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid-gridx];
                            block[select_grid-gridx]=image_tmp;
                            
                            select_grid-=gridx;
                        }
                    }
                    if(ansh == 'D'){//下キーを押したとき
                        if(select_grid+gridx>num_of_block-1){
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid-gridx*(gridy-1)];
                            block_grid[select_grid-gridx*(gridy-1)]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid-gridx*(gridy-1)];
                            block[select_grid-gridx*(gridy-1)]=image_tmp;
                            
                            select_grid-=gridx*(gridy-1);
                        }else{
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid+gridx];
                            block_grid[select_grid+gridx]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid+gridx];
                            block[select_grid+gridx]=image_tmp;
                            
                            select_grid+=gridx;
                        }
                    }
                    if(ansh == 'R'){//右キーを押したとき
                        if((select_grid+1)%gridx==0){
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid-(gridx-1)];
                            block_grid[select_grid-(gridx-1)]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid-(gridx-1)];
                            block[select_grid-(gridx-1)]=image_tmp;
                            
                            select_grid-=(gridx-1);
                        }else{
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid+1];
                            block_grid[select_grid+1]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid+1];
                            block[select_grid+1]=image_tmp;
                            
                            select_grid++;
                        }
                    }
                    if(ansh == 'L'){//左キーを押したとき
                        if(select_grid%gridx==0){
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid+(gridx-1)];
                            block_grid[select_grid+(gridx-1)]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid+(gridx-1)];
                            block[select_grid+(gridx-1)]=image_tmp;
                            
                            select_grid+=(gridx-1);
                        }else{
                            texture_tmp=block_grid[select_grid];
                            block_grid[select_grid]=block_grid[select_grid-1];
                            block_grid[select_grid-1]=texture_tmp;
                            
                            image_tmp=block[select_grid];
                            block[select_grid]=block[select_grid-1];
                            block[select_grid-1]=image_tmp;
                            
                            select_grid--;
                        }
                    }
                }
            }
            rep(i, anss.size()){
                rep(j, xh(anss[i])){
                    block_grid[i].fill(block[i].rotate90());
                }
            }
        }
    }
    write_movedata(mov);
    return 1;
}
