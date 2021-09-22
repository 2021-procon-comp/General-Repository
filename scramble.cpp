#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
using namespace std;
#define rep(i, b) for(int i = 0; i < int(b); i++)

int main(int argc, const char * argv[]) {
    ifstream in("input.txt");
    ofstream out("output.txt");
    random_device rnd;
    string str;
    int xx, yy, gx, gy, gs;
    
    in >> str;
    out << str << "\n";
    in >> gx;
    out << gx << " ";
    in >> gy;
    out << gy << "\n";
    in >> gs;
    out << gs << "\n";
    in >> gs;
    out << gs << " ";
    in >> gs;
    out << gs << "\n";
    in >> xx;
    out << xx << " ";
    in >> yy;
    out << yy << "\n";
    in >> gs;
    out << gs << "\n";
    gs = xx/gx;
    vector<vector<vector<vector<string>>>> map(gy, vector<vector<vector<string>>>(gx, vector<vector<string>>(gs, vector<string>(gs)))), map2(map);
    getline(in, str);
    getline(in, str);
    cout << str.size() << endl;
    
    int cnt = 0;
    rep(y, gy){
        rep(j, gs){
            rep(x, gx){
                rep(i, gs){
                    rep(six, 6) map[y][x][j][i] += str[cnt+six];
                    cnt += 6;
                }
            }
        }
    }
//    cout << map[0][0][1][0] << endl;
    
    vector<int> par(gx*gy);
    rep(i, gx*gy) par[i] = i;
    rep(i, gx*gy) swap(par[rnd()%(gx*gy-i)], par[gx*gy-i-1]);
    int nx, ny, r;
    rep(y, gy){
        rep(x, gx){
            nx = par[x+y*gx] % gx;
            ny = par[x+y*gx] / gx;
            r = rnd() % 4;
            if(x == 0 && y == 0) r = 0;
            if(r == 0){
                rep(j, gs) rep(i, gs){
                    map2[y][x][j][i] = map[ny][nx][j][i];
                }
            }
            else if(r == 1){
                rep(j, gs) rep(i, gs){
                    map2[y][x][j][i] = map[ny][nx][gs-i-1][j];
                }
            }
            else if(r == 2){
                rep(j, gs) rep(i, gs){
                    map2[y][x][j][i] = map[ny][nx][gs-j-1][gs-i-1];
                }
            }
            else {
                rep(j, gs) rep(i, gs){
                    map2[y][x][j][i] = map[ny][nx][i][gs-j-1];
                }
            }
        }
    }
    
    rep(y, gy){
        rep(j, gs){
            rep(x, gx){
                rep(i, gs){
                    out << map2[y][x][j][i];
                }
            }
        }
    }
}
