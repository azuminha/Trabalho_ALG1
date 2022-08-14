#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#define tam 50
#define altura 12

void bubble_sort(int array[tam], int col);
void create_matrix( int matrix[tam][tam], int x, int y);
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

void clear_matrixwin(int startY, int startX, int maxY, int maxX);
void show_matrix_win2( int matrix[tam][tam], int x, int y);

int yMax, xMax;
int startX, startY;

int main(){
  int matrix[tam][tam], new_matrix[tam][tam];
  int lin, col, lin1, lin2;


  /*  printf("linha: coluna:\n");
  scanf("%d %d", &lin, &col);
  create_matrix(matrix, lin, col);
  matrixcpy(new_matrix, matrix, lin, col);
  printf("%d\n", is_permut_matrix(new_matrix, lin, col));
  show_matrix(new_matrix, lin, col);
  */
  initscr();
  noecho();
  cbreak();

  const char * menu_itens[9] = {
  "Ler Matriz",
  "Trocar elementos da linha X pela linha Y",
  "Trocar elementos da coluna X pela coluna Y",
  "Trocar elementos da DP com DS",
  "Verificar se a matriz e simetrica",
  "Verificar se a matriz e um quadrado magico",
  "Verificar se a matriz e quadrado latino",
  "Verificar se a matriz e matriz de permutacao",
  "Sair"};
  
  int matrixwinY, matrixwinX;
  int mwinyMax, mwinxMax;
  
  getmaxyx(stdscr, yMax, xMax);
  getbegyx(stdscr, startY, startX);
  
  WINDOW * menuwin   = newwin(altura, xMax, startY, startX);
  WINDOW * matrixwin = newwin(yMax-altura, xMax/2, startY+altura, startX); 
  WINDOW * showwin   = newwin(yMax-altura, xMax/2, startY+altura, startX+xMax/2);
  
  getmaxyx(matrixwin, mwinyMax, mwinxMax);
  getbegyx(matrixwin, matrixwinY, matrixwinX);
  
  box(menuwin, 0, 0);
  box(matrixwin, 0, 0);
  box(showwin, 0, 0);

 
  mvwprintw(matrixwin, 0, 1, "Sua-Matriz");
  mvwprintw(showwin, 0, 1, "Resultado");
  mvwprintw(menuwin, 0, 1, "Menu");

  refresh();
  wrefresh(menuwin);
  wrefresh(matrixwin);
  wrefresh(showwin);

  keypad(menuwin, TRUE);
  int seta;
  int mark=0;
  int tem_matriz=0;
  //do{
  comeco:
  matrixcpy(matrix, new_matrix, lin, col); 
  while(1){
    for(int i = 0; i<9; ++i){
      if(i==mark)
        wattron(menuwin, A_REVERSE);
      mvwprintw(menuwin, i+2, 1, menu_itens[i]);
      wattroff(menuwin, A_REVERSE);
    }
    seta = wgetch(menuwin);

    switch(seta){
      case KEY_UP:
        mark--; 
            
        if(mark < 0)
          mark = 8;
        break;

      case KEY_DOWN:
        mark++; 
       
        if (mark >=9)
          mark = 0;     
        break;

      default:
        break;
    }
    if (mark==0)
      tem_matriz=1;
    
    if (seta==10 && tem_matriz || mark==8 && seta==10)
      break;
    
  }



  if(mark==0){  
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
      mvprintw(startY+altura+1,startX+1, "Digite quantas linhas e colunas a matriz tera, e pressione enter: ");
      refresh();
      scanf("%d", &lin);
      mvprintw(startY+altura+2,startX+1,"Linhas: %d", lin);
      refresh();
      scanf("%d", &col);
      mvprintw(startY+altura+3,startX+1,"Colunas: %d", col);
      refresh();
      mvprintw(startY+altura+4,startX+1,"Pressione uma tecla para continuar...");
      getch();
      clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
      create_matrix(matrix, lin, col);    
      matrixcpy(new_matrix, matrix, lin, col);    
  }
  if(mark==1){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    mvprintw(startY+altura+1,startX+1, "Digite o valor das linhas e clique enter");
    refresh();
    scanf("%d", &lin1);
    mvprintw(startY+altura+2,startX+1,"Linha: %d", lin1);
    refresh();
    scanf("%d", &lin2);
    mvprintw(startY+altura+3,startX+1,"Linha: %d", lin2);
    refresh();
    mvprintw(startY+altura+4,startX+1,"Pressione uma tecla para continuar...");
    getch();
    change_lines(matrix, col, lin1, lin2);
    show_matrix(matrix, lin, col);
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    show_matrix_win2(new_matrix, lin, col);
  }
 
  if(mark==2){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    mvprintw(startY+altura+1,startX+1, "Digite o valor das colunas e clique enter");
    refresh();
    scanf("%d", &lin1);
    mvprintw(startY+altura+2,startX+1,"Linha: %d", lin1);
    refresh();
    scanf("%d", &lin2);
    mvprintw(startY+altura+3,startX+1,"Linha: %d", lin2);
    refresh();
    mvprintw(startY+altura+4,startX+1,"Pressione uma tecla para continuar...");
    getch();
    change_colums(matrix, col, lin1, lin2);
    show_matrix(matrix, lin, col);
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    show_matrix_win2(new_matrix, lin, col);
  }
 
  if(mark==3){
    
    change_diag(matrix, lin, col);
    show_matrix(matrix, lin, col);
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    show_matrix_win2(new_matrix, lin, col);
  }
  if(mark==4){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    
    if(is_sym_matrix(matrix, lin, col)){
      mvprintw(yMax/2+6,xMax/4-11,"E uma matriz simetrica");
      refresh();
    }else{
      mvprintw(yMax/2+6,xMax/4-13,"Nao e uma matriz simetrica");
      refresh();
    }
  }
   if(mark==5){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    
    if(is_magic_square(matrix, lin, col)){
      mvprintw(yMax/2+6,xMax/4-10,"E um quadrado magico");
      refresh();
    }else{
      mvprintw(yMax/2+6,xMax/4-12,"Nao e um quadrado magico");
      refresh();
    }
  }
  if(mark==6){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    
    if(is_latin_square(matrix, lin, col)){
      mvprintw(yMax/2+6,xMax/4-10,"E um quadrado latino");
      refresh();
    }else{
      mvprintw(yMax/2+6,xMax/4-12,"Nao e um quadrado latino");
      refresh();
    }
  }
  if(mark==7){
    clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
    
    if(is_permut_matrix(matrix, lin, col)){
      mvprintw(yMax/2+6,xMax/4-12,"E uma matriz permutacao");
      refresh();
    }else{
      mvprintw(yMax/2+6,xMax/4-14,"Nao e uma matriz permutacao");
      refresh();
    }
  }

  if(mark==8)
    goto sair;
  goto comeco;
  sair:
  //}while(mark != 8);

  //create_matrix(matrix, 3, 3);
  //getch();
  //clear_matrixwin(startY+altura, startX,yMax-altura, xMax/2);
  //create_matrix(matrix, 3, 3);
 
 

  
  endwin();

  
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
      mvprintw(startY+altura+1+i, startX+xMax/2+1+5*j,"%d", matrix[i][j]);
      refresh();
    }
    //printf("\n");
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
      mvprintw(startY+altura+1,startX+1, "Digite os numeros e pressione espaco ou enter:");
      refresh();
      scanf("%d", &matrix[i][j]);
      mvprintw(startY+altura+2+i,startX+1+5*j,"%d", matrix[i][j]);
      refresh();
    }
  }
}

void clear_matrixwin(int startY, int startX, int maxY, int maxX){
  for(int i=startY+1; i<maxY; i++){
    for(int j=startX+1; j<maxX-1; ++j){
      mvprintw(i, j, " ");
    }
  }
}

void show_matrix_win2( int matrix[tam][tam], int x, int y){
  for( int i=0; i<x; ++i){
    for( int j=0; j<y; ++j){
      mvprintw(startY+altura+2+i,startX+1+5*j,"%d", matrix[i][j]);
      refresh();
    }
    //printf("\n");
  }
}