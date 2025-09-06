#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 9
#define COLS 9
#define MINES 10

static int mine[ROWS][COLS], adj[ROWS][COLS], revv[ROWS][COLS], flagg[ROWS][COLS];

int in_bounds(int r,int c){ return r>=0 && r<ROWS && c>=0 && c<COLS; }

// place mines randomly, avoid safe cell
void place_mines(int safe_r,int safe_c){
  int placed=0;
  while(placed<MINES){
    int r=rand()%ROWS, c=rand()%COLS;
    if(mine[r][c]) continue;
    if(r==safe_r && c==safe_c) continue;
    mine[r][c]=1; placed++;
  }
}

// compute adjacent mine counts
void compute_adj(){
  for(int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++){
    if(mine[r][c]){ adj[r][c]=-1; continue; }
    int cnt=0;
    for(int dr=-1;dr<=1;dr++) for(int dc=-1;dc<=1;dc++){
      if(dr==0 && dc==0) continue;
      int nr=r+dr, nc=c+dc;
      if(in_bounds(nr,nc) && mine[nr][nc]) cnt++;
    }
    adj[r][c]=cnt;
  }
}

// display board (if reveal_all, show all mines)
void print_board(int reveal_all){
  printf("   "); for(int c=0;c<COLS;c++) printf("%d ",c); printf("\n");
  for(int r=0;r<ROWS;r++){
    printf("%d: ",r);
    for(int c=0;c<COLS;c++){
      if(reveal_all){
        if(mine[r][c]) printf("* "); else printf("%d ", adj[r][c]);
        continue;
      }
      if(flagg[r][c]){ printf("F "); continue; }
      if(!revv[r][c]){ printf(". "); continue; }
      if(mine[r][c]){ printf("* "); continue; }
      printf("%d ", adj[r][c]);
    }
    printf("\n");
  }
}

// recursively reveal neighbors
void flood(int r,int c){
  if(!in_bounds(r,c) || revv[r][c]) return;
  revv[r][c]=1;
  if(adj[r][c]!=0) return;
  for(int dr=-1;dr<=1;dr++) for(int dc=-1;dc<=1;dc++){
    if(dr==0 && dc==0) continue;
    flood(r+dr,c+dc);
  }
}

// reveal cell, return 0 if hit mine
int reveal_cell(int r,int c){
  if(!in_bounds(r,c) || revv[r][c]) return 1;
  if(flagg[r][c]) return 1;
  revv[r][c]=1;
  if(mine[r][c]) return 0;
  if(adj[r][c]==0) flood(r,c);
  return 1;
}

// check win condition
int all_clear(){
  for(int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++)
    if(!mine[r][c] && !revv[r][c]) return 0;
  return 1;
}

int main(void){
  srand((unsigned)time(NULL));
  for(int r=0;r<ROWS;r++) for(int c=0;c<COLS;c++) mine[r][c]=adj[r][c]=revv[r][c]=flagg[r][c]=0;
  printf("Minesweeper %dx%d with %d mines. Commands: r x y, f x y, q\n", ROWS,COLS,MINES);
  print_board(0);
  int first=1; char cmd; int x,y;
  while(1){
    printf("> ");
    if(scanf(" %c",&cmd)!=1) break;
    if(cmd=='q') break;
    if(cmd=='f'){
      if(scanf("%d %d",&x,&y)!=2){ printf("Invalid.\n"); continue; }
      if(!in_bounds(y,x)){ printf("Out of bounds.\n"); continue; }
      if(revv[y][x]){ printf("Already revealed.\n"); continue; }
      flagg[y][x]=!flagg[y][x];
    } else if(cmd=='r'){
      if(scanf("%d %d",&x,&y)!=2){ printf("Invalid.\n"); continue; }
      if(!in_bounds(y,x)){ printf("Out of bounds.\n"); continue; }
      if(first){ place_mines(y,x); compute_adj(); first=0; }
      if(!reveal_cell(y,x)){ printf("BOOM! (%d,%d)\n",x,y); print_board(1); return 0; }
      if(all_clear()){ printf("You win! 🎉\n"); print_board(1); return 0; }
    } else {
      printf("Commands: r x y, f x y, q\n");
    }
    print_board(0);
  }
  return 0;
}
