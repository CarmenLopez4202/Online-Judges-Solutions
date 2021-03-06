/*******************************************
 ***Problema: Shortest Bridge
 ***ID: 934
 ***Juez: LeetCode
 ***Tipo: DFS, Flood-fill
 ***Autor: Jhosimar George Arias Figueroa
 *******************************************/

class Solution {
public:
    struct Position{
        int x, y;
        Position(int _x, int _y):x(_x), y(_y){}
        Position(){}
    };
    
    #define COMP (1<<30)
    #define INIT 10
    int dx[4] = {0,  0, 1, -1};
    int dy[4] = {1, -1, 0,  0};
    
    void floodfill(vector<vector<int>> &A, int x, int y, int comp, queue<Position> &Q){
        int h = A.size(), w = A[0].size();
        A[x][y] = comp;
        for( int i = 0 ; i < 4 ; ++i ){
            int nx = x + dx[i], ny = y + dy[i];
            if( nx >= 0 && ny >= 0 && nx < h && ny < w ){
                if( A[nx][ny] == 0 && comp == COMP){
                    Q.push(Position(nx, ny));
                    A[nx][ny] = INIT;
                }
                else if( A[nx][ny] == 1 )
                    floodfill(A, nx, ny, comp, Q);
            }
        }
    }
    
    int bfs(vector<vector<int> > &A, queue<Position> &Q ){
        int h = A.size(), w = A[0].size();
        while( !Q.empty() ){
            Position current = Q.front(); Q.pop();
            int x = current.x, y = current.y;
            for( int i = 0 ; i < 4 ; ++i ){
                int nx = x + dx[i], ny = y + dy[i];
                if( nx >= 0 && ny >= 0 && nx < h && ny < w){

                    if(A[nx][ny] == 0){
                        A[nx][ny] = A[x][y] + 1;
                        Q.push(Position(nx, ny));
                    }else if( A[nx][ny] == COMP + 1 ){
                        return A[x][y] + 1 - INIT;
                    }
                }
            }
        }
        return -1;
    }
    
    int shortestBridge(vector<vector<int>>& A) {
        int h = A.size(), w = A[0].size();
        queue<Position> Q;
        int comp = COMP;
        for( int i = 0 ; i < h ; ++i ){
            for( int j = 0; j < w ; ++j ){
                if( A[i][j] == 1 ){
                    floodfill(A, i, j, comp++, Q);
                }
            }
        }
        return bfs(A, Q);     
    }
};
