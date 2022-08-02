#include <iostream>
#include <vector>
using namespace std;

void printSudoku(int arr[9][9]){

  cout<<"----------------------------"<<endl;
  for(int r=0;r<9;r++){
    for(int c=0;c<9;c++){
      cout<<arr[r][c]<<" ";
    }
    cout<<endl;
  }
  cout<<"----------------------------"<<endl;

}

bool canPlace(int arr[9][9], int row, int col, int n){

  if(arr[row][col]!=0) return false;
  bool status = true;

  int gridx = (col / 3)*3;
  int gridy = (row / 3)*3;

  for(int i=0; i<9; i++){

    if(arr[row][i] == n){ status = false; break;}
    if(arr[i][col] == n){ status = false; break;}
    if(arr[gridy + i / 3][gridx +i %3] == n){ status = false; break;}
  }
  return status;
}

void nextEmpty(int arr[9][9], int row, int col, int& nrow, int& ncol){
  int index=9*9;
  for(int i=row*9+col+1;i<9*9;i++){

    if(arr[i/9][i%9]==0){
      index=i;
      break;
    }
  }

  nrow = index / 9;
  ncol = index % 9;
}

void copyArray(int arr[9][9], int arrcpy[9][9]){

  for(int y=0;y<9;y++)
    for(int x=0;x<9;x++)
      arrcpy[y][x]= arr[y][x];
}
vector<int> findPlacebles(int arr[9][9], int r , int c){

  vector<int> cps={};
  for(int i=1;i<=9;i++){
    if(canPlace(arr,r,c,i))
    cps.push_back(i);
  }
  return cps;
}

bool solveSudoku(int arr[9][9], int row, int col){

  if(row>8) return true;
  if(arr[row][col]!=0){
      int nextcol, nextrow;
      nextEmpty(arr,row,col,nextrow,nextcol);
      return solveSudoku(arr,nextrow,nextcol);
    }
  
  vector<int> placeables=findPlacebles(arr,row,col);

  if(placeables.size()==0) {return false;};

  bool status=false;
  for(int i=0;i<placeables.size();i++){

    int n = placeables[i];
    int arrcpy[9][9];
    copyArray(arr, arrcpy);
    arrcpy[row][col]=n;

    int nextcol, nextrow;
    nextEmpty(arrcpy,row,col,nextrow,nextcol);

    if(solveSudoku(arrcpy,nextrow, nextcol)){
      copyArray(arrcpy,arr);
      status = true;
      break;
    }
  }
  return status;
}

int main(){

  int board[9][9]={
    {5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
  };

  printSudoku(board);
  if(solveSudoku(board,0,0)){
    cout<<"Succeesfully solved Sudoku\n"<<endl;
  };

  printSudoku(board);

}