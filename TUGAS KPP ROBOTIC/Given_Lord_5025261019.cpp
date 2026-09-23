#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second

// Arah pergerakan: atas, bawah, kiri, kanan
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
string dir[] = {"UP","DOWN","LEFT","RIGHT"};

int row, col;
char grid[100][100];
int total_dist = 0;

// BFS untuk cari rute terpendek antar titik
string bfs(int sr, int sc, int tr, int tc) {
    int ans = -1;
    queue<pair<int,int>> q;
    vector<vector<int>> dist(row, vector<int>(col, -1));
    vector<vector<int>> pa_dir(row, vector<int>(col, -1)); // Simpan arah parent buat reconstruct path
    
    q.push({sr, sc});
    dist[sr][sc] = 0;
    
    while(!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        // Target ketemu, simpan jarak lalu stop
        if (dist[tr][tc] != -1) {
            ans = dist[tr][tc];
            break;
        }
        
        // Cek 4 tetangga
        for (int i = 0; i < 4; i++) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            
            if (nr >= 0 && nc >= 0 && nr < row && nc < col) {
                // Hindari tembok ('#', 'X') dan cell yang udah dikunjungi
                if (grid[nr][nc] != '#' && grid[nr][nc] != 'X' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    pa_dir[nr][nc] = i; // Catat langkah yang diambil
                    q.push({nr, nc});
                }
            }
        }
    }

    // Gagal nemu jalan
    if (dist[tr][tc] == -1) {
        return "NO PATH AVAILABLE";
    }
    
    // Trace back langkah dari target balik ke start
    int cur_r = tr; 
    int cur_c = tc;
    vector<string> path;
    string anspath;
    
    while(cur_r != sr || cur_c != sc) {
        int d = pa_dir[cur_r][cur_c];
        path.pb(dir[d]);
        
        // Mundur ke parent
        cur_r -= dx[d];
        cur_c -= dy[d];
    }
    
    total_dist += ans;
    
    // Balik urutan path agar dari start -> target
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) {
            anspath += ", ";
        }
        anspath += path[i];
    }

    return anspath;
}

int main () {
    cin >> row >> col;
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> grid[i][j];
        }
    }
    
    int sr, sc, fr, fc, gr, gc;
    
    // Lokasi kuis: S = Start, F = Flag, G = Goal/Base
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 'S') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'F') {
                fr = i; fc = j;
            } else if (grid[i][j] == 'G') {
                gr = i; gc = j;
            }
        } 
    }

    // Perjalanan 2 tahap: Start -> Bendera, lalu Bendera -> Base
    string flagpath = bfs(sr, sc, fr, fc);
    string basepath = bfs(fr, fc, gr, gc);

    // Output status akhir
    if (flagpath == "NO PATH AVAILABLE" || basepath == "NO PATH AVAILABLE") {
        cout << "MAP LOADED       : " << row << " X " << col << endl;
        cout << "START POSITION   : (" << sr << "," << sc << ")" << endl;
        cout << "PATH TO FLAG     : " << flagpath << endl;
        cout << "FLAG CAPTURED    : CANT REACHED FLAG" << endl;
        cout << "PATH TO BASE     : " << basepath << endl;
        cout << "BASE REACHED     : CANT REACHED BASE" << endl;
        cout << "MISSION FAILED" << endl;
        cout << "TOTAL MOVES      : " << total_dist << endl;
    } else {
        cout << "MAP LOADED       : " << row << " X " << col << endl;
        cout << "START POSITION   : (" << sr << "," << sc << ")" << endl;
        cout << "PATH TO FLAG     : " << flagpath << endl;
        cout << "FLAG CAPTURED    : (" << fr << "," << fc << ")" << endl;
        cout << "PATH TO BASE     : " << basepath << endl;
        cout << "BASE REACHED     : (" << gr << "," << gc << ")" << endl;
        cout << "MISSION COMPLETE" << endl;
        cout << "TOTAL MOVES      : " << total_dist << endl;
    }
}