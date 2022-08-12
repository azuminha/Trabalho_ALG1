#include <stdio.h>
#define tam 50

void bubble_sort(int array[tam], int col);
void create_matrix( int matrix[tam][tam], int x, int y );
void matrixcpy( int matrixcpy[tam][tam], int matrix[tam][tam], int x, int y );
void show_matrix( int matrix[tam][tam], int x, int y );
void change_lines( int matrix[tam][tam], int col, int linx, int liny );
void change_colums( int matrix[tam][tam], int lin, int colx, int coly );
int is_square_matrix( int x, int y );
int change_diag( int matrix[tam][tam], int lin, int col );
int is_sym_matrix( int matrix[tam][tam], int lin, int col );
int is_magic_square( int matrix[tam][tam], int lin, int col );
int is_latin_square( int matrix[tam][tam], int lin, int col );
int is_permut_matrix(int matrix[tam][tam], int lin, int col);

int main(){
  int matrix[tam][tam], new_matrix[tam][tam];
  int lin, col;
  printf("linha: coluna:\n");
  scanf("%d %d", &lin, &col);
  create_matrix(matrix, lin, col);
  matrixcpy(new_matrix, matrix, lin, col);
  printf("%d\n", is_permut_matrix(new_matrix, lin, col));
  show_matrix(new_matrix, lin, col);
  
  return 0;
}

int is_permut_matrix(int matrix[tam][tam], int lin, int col){
  int soma = 1, soma1, soma2;
  int teste[tam][tam];
  matrixcpy(teste, matrix, lin, col);
  
  for(int i=0; i<lin; ++i){
    soma1 = soma2 = 0;
    for(int j=0; j<col; ++j){
      soma1 += matrix[i][j];
      soma2 += matrix[j][i];
    }
    if (soma1 != soma || soma2 != soma) return 0;
  }

  for(int i=0; i<lin; ++i){
    bubble_sort(teste[i], col);
  }
  //show_matrix(teste, lin,col);
  //verifica os valores
  for(int i=0; i<lin; ++i){
    for(int j=0; j<col; ++j){
      if(teste[i][j] != 0 && j<col-1) return 0;
      else if (teste[i][col-1] != 1) return 0;
    }
  }

  return 1;
}

void bubble_sort(int array[tam], int col){
  int aux;
  for (int i=0; i<col; ++i){
    for (int j=0; j<col; ++j){
      if (array[i] < array[j]){
	aux = array[i];
	array[i] = array[j];
	array[j] = aux;
      }
    }
  }
}

int is_latin_square( int matrix[tam][tam], int lin, int col){
  int soma = 0, soma1, soma2;
  int teste[tam][tam];
  matrixcpy(teste, matrix, lin, col);
  
  for(int i=1; i<=lin; ++i)
    soma += i;
  
  for(int i=0; i<lin; ++i){
    soma1 = soma2 = 0;
    for(int j=0; j<col; ++j){
      soma1 += matrix[i][j];
      soma2 += matrix[j][i];
    }
    if (soma1 != soma || soma2 != soma) return 0;
  }

  //arruma matriz
  for(int i=0; i<lin; ++i){
    bubble_sort(teste[i], col);
  }
  //verifica os valores
  for(int i=0; i<lin; ++i){
    for(int j=0; j<col; ++j){
      if(teste[i][0] != 1 ) return 0;
      else if (teste[i][j] != teste[i][j-1] + 1) return 0;
    }
  }

  return 1;
}

int is_magic_square( int matrix[tam][tam], int lin, int col ){
  int soma, aux;
  soma = aux = 0;
  for (int i=0; i<lin; ++i){
    soma += matrix[i][i];
  }
  for (int i=0; i<lin; ++i){
    aux += matrix[i][lin-1-i];
  }
  if( aux != soma) return 0;

  for (int i=0; i<lin; ++i){
    aux = 0;
    for (int j=0; j<col; ++j){
      aux += matrix[i][j]; 
    }
    if ( aux != soma ) return 0;
  }

  for (int i=0; i<lin; ++i){
    aux = 0;
    for (int j=0; j<col; ++j){
      aux += matrix[j][i]; 
    }
    if ( aux != soma ) return 0;
  }
  
  return 1;
  
}

int is_sym_matrix(int matrix[tam][tam], int lin, int col){
  //int transposta[tam][tam];
  int ver=1;
  if( !is_square_matrix(lin, col) )
    return 0;
  else{
    /*criar At
    for( int i=0; i<lin; ++i ){
      for( int j=0; j<col; ++j ){
	transposta[j][i] = matrix[i][j];
      }
      }*/
    for( int i=0; i<lin; ++i ){
      for( int j=0; j<col; ++j ){
	if( matrix[j][i] != matrix[i][j] ){
	  ver = 0;
	}
      }
    }
    
    return ver;
  }
}

int is_square_matrix(int x, int y){
  return (x==y) ? 1:0;
}

int change_diag(int matrix[tam][tam], int lin, int col){
  int aux, soma=lin-1;
  if(!is_square_matrix(lin, col)){
    printf("Impossivel, nao e uma matrix quadrada\n");
    return 0;
  }else{
    for( int i=0; i<lin; ++i){
      aux = matrix[i][i];   
      matrix[i][i] = matrix[i][soma-i];
      matrix[i][soma-i] = aux;
    }
    return 1;
  }
}

void change_colums(int matrix[tam][tam], int lin, int colx, int coly){
  int aux;
  for (int i=0; i<lin; ++i){
    aux = matrix[i][colx-1];
    matrix[i][colx-1] = matrix[i][coly-1];
    matrix[i][coly-1] = aux;
  }
}

//                    matriz            tamanha da coluna, linhas para trocar
void change_lines(int matrix[tam][tam], int col, int linx, int liny){
  int aux;
  for (int i=0; i<col; ++i){
    aux = matrix[linx-1][i];
    matrix[linx-1][i] = matrix[liny-1][i];
    matrix[liny-1][i] = aux;
  }
}

void show_matrix( int matrix[tam][tam], int x, int y){
  for( int i=0; i<x; ++i){
    for( int j=0; j<y; ++j){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void matrixcpy(int matrixcpy[tam][tam], int matrix[tam][tam], int x, int y ){
  for (int i=0; i<x; ++i){
    for (int j=0; j<y; ++j){
      matrixcpy[i][j] = matrix[i][j];
    }
  }
}

void create_matrix(int matrix[tam][tam], int x, int y){
  for (int i=0; i<x; ++i){
    for (int j=0; j<y; ++j){
      scanf("%d", &matrix[i][j]);
    }
  }
}

