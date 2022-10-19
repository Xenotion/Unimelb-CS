/* 
  Program to print and play checker games.
  Skeleton program written by Artem Polyvyanyy, artem.polyvyanyy@unimelb.edu.au,
  September 2021, with the intention that it be modified by students
  to add functionality, as required by the assignment specification.

  Student Authorship Declaration:

  (1) I certify that except for the code provided in the initial skeleton file,
  the program contained in this submission is completely my own individual
  work, except where explicitly noted by further comments that provide details
  otherwise. I understand that work that has been developed by another student,
  or by me in collaboration with other students, or by non-students as a result
  of request, solicitation, or payment, may not be submitted for assessment in
  this subject. I understand that submitting for assessment work developed by
  or in collaboration with other students or non-students constitutes Academic
  Misconduct, and may be penalized by mark deductions, or by other penalties
  determined via the University of Melbourne Academic Honesty Policy, as
  described at https://academicintegrity.unimelb.edu.au.

  (2) I also certify that I have not provided a copy of this work in either
  softcopy or hardcopy or any other form to any other student, and nor will I
  do so until after the marks are released. I understand that providing my work
  to other students, regardless of my intention or any undertakings made to me
  by that other student, is also Academic Misconduct.

  (3) I further understand that providing a copy of the assignment specification
  to any form of code authoring or assignment tutoring service, or drawing the
  attention of others to such services and code that may have been made
  available via such a service, may be regarded as Student General Misconduct
  (interfering with the teaching activities of the University and/or inciting
  others to commit Academic Misconduct). I understand that an allegation of
  Student General Misconduct may arise regardless of whether or not I personally
  make use of such solutions or sought benefit from such actions.

  Signed by: JUNG-HYUN AN
  Dated:     15/10/2021

*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* some #define's from my sample solution ------------------------------------*/
#define BOARD_SIZE          8       // board size
#define ROWS_WITH_PIECES    3       // number of initial rows with pieces
#define CELL_EMPTY          '.'     // empty cell character
#define CELL_BPIECE         'b'     // black piece character
#define CELL_WPIECE         'w'     // white piece character
#define CELL_BTOWER         'B'     // black tower character
#define CELL_WTOWER         'W'     // white tower character
#define COST_PIECE          1       // one piece cost
#define COST_TOWER          3       // one tower cost
#define TREE_DEPTH          3       // minimax tree depth
#define COMP_ACTIONS        10      // number of computed actions

/* one type definition from my sample solution -------------------------------*/
#define WHITE 0
#define BLACK 1
#define TOWER 1
#define NOT_TOWER 0
#define INITIAL_WHITE_NUM 12
#define INITIAL_BLACK_NUM 12
#define BORDER "====================================="
#define BORDER2 "+---+---+---+---+---+---+---+---+"
#define HEADER "A   B   C   D   E   F   G   H"
#define INITIAL_DEPTH 0

typedef unsigned char board_t[BOARD_SIZE][BOARD_SIZE];  // board type

// declaring structs as type variables 

typedef struct grid Grid;
typedef struct piece Piece;
typedef struct path_t path_t;
typedef struct node_t node_t;

// functions 

Piece *createPiece(int team, int tower);
Grid *createGrid(int width, int height);
int piece_to_string(Piece *piece);
void printGrid(Grid *grid);
void lay_out_white_black(Grid *grid);
void freePiece(Piece *piece);
void freeBoard(Grid *grid); 
void freeGrid(Grid *grid);
int c_2_i(char row);
void print_function();
int boardCost(Grid *grid);
void errors(Grid *grid, char ini_row, int ini_col, 
            char fin_row, int fin_col, int count);
void capture_piece(Grid *grid, char ini_row, int ini_col, 
                   char fin_row, int fin_col);
void deep_copy_piece(Piece *old, Piece *new);
void deep_copy_grid(Grid *old, Grid *new);
int minimax(node_t *node_t, Grid *grid, int depth, int isMax);
int maxNode_t(node_t *left, int value);
int minNode_t(node_t *left, int value);

//struct for grid
struct grid {
  Piece*** board;
  int width;
  int height;
};

//struct for piece
struct piece {
  int team;
  int tower;
};

//struct for path
struct path_t {
  path_t *next;
};

//struct for nodes 
struct node_t {
  Grid *grid;
  int boardCost;
  path_t *pathHead;
};

//main function
int main(int argc, char *argv[]) {

  //prints the chekcers game
  print_function();

  return 0;
}


void print_function() {
  //creates grid
  Grid *grid = createGrid(BOARD_SIZE, BOARD_SIZE);

  //print initial lines
  printf("BOARD SIZE: %dx%d\n", BOARD_SIZE, BOARD_SIZE);
  printf("#BLACK PIECES: %d\n", INITIAL_BLACK_NUM);
  printf("#WHITE PIECES: %d\n", INITIAL_WHITE_NUM);

  //lay pieces on the grid and print
  lay_out_white_black(grid);
  printGrid(grid);
  
  char ini_row, fin_row, next_move;
  int ini_col, fin_col, count = 1;

  //scan the input txt file for rows and columns
  while((scanf(" %c%d-%c%d ", &ini_row, &ini_col, &fin_row, &fin_col) == 4) || 
        (scanf("%c", &next_move) == 1)) {
    
    //check whether the move is valid 
    errors(grid, ini_row, ini_col, fin_row, fin_col, count);

    printf("%s\n", BORDER);
    
    //if statements for checking whether its black or white turn
    if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == WHITE) {
      printf("WHITE ACTION #%d: ", count);
      printf("%c%d-%c%d\n", ini_row, ini_col, fin_row, fin_col);

      if (fin_col - ini_col != 1) {
        capture_piece(grid, ini_row, ini_col, fin_row, fin_col);
      }
    } 
    
    else if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == BLACK) {
      printf("BLACK ACTION #%d: ", count);
      printf("%c%d-%c%d\n", ini_row, ini_col, fin_row, fin_col);

      if (ini_col - fin_col != 1) {
        capture_piece(grid, ini_row, ini_col, fin_row, fin_col);
      }
    }
    
    //counter to track which players turn it is
    count += 1;
    
    //turn a piece into a tower if one reaches the end of the board
    if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == BLACK) {

      if (fin_col == 1) {
        grid->board[ini_col - 1][c_2_i(ini_row)]->tower = TOWER;
      }

    } else if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == WHITE) {

      if (fin_col == BOARD_SIZE) {
        grid->board[ini_col - 1][c_2_i(ini_row)]->tower = TOWER;
      }

    }

    //moving the pieces
    Piece *from = grid->board[ini_col - 1][c_2_i(ini_row)];
    Piece *to = grid->board[fin_col - 1][c_2_i(fin_row)];
    grid->board[ini_col - 1][c_2_i(ini_row)] = NULL;
    grid->board[fin_col - 1][c_2_i(fin_row)] = from;
    
    printf("BOARD COST: %d\n", boardCost(grid));

    //free the memory allocated to the piece and print the final grid
    freePiece(to);
    printGrid(grid);
    
  }
  freeGrid(grid);
}

void capture_piece(Grid *grid, char ini_row, int ini_col, 
  char fin_row, int fin_col) {
  
  //when capturing, calculating the position of the captured piece 
  //using (a+b)/2
  int captured_piece_row = (c_2_i(fin_row) + c_2_i(ini_row)) / 2;
  int captured_piece_col = (fin_col-1 + ini_col-1) / 2;

  //turn captured piece into NULL and free it 
  grid->board[captured_piece_col][captured_piece_row] = NULL;
  freePiece(grid->board[captured_piece_col][captured_piece_row]);

}

void errors(Grid *grid, char ini_row, int ini_col, 
  char fin_row, int fin_col, int count) {
  
  //when both initial col and row are outside the board
  if (ini_col > BOARD_SIZE || c_2_i(ini_row) > 7) {
    printf("ERROR: Source cell is outside of the board.\n");
    exit(0);
  }

  //when both final col and row are outside the board
  if (fin_col > BOARD_SIZE || c_2_i(fin_row) > 7) {
    printf("ERROR: Target cell is outside of the board.\n");
    exit(0);
  }
  
  //when the initial row and col does not have a piece
  if (grid->board[ini_col - 1][c_2_i(ini_row)] == NULL) {
    printf("ERROR: Source cell is empty.\n");
    exit(0);
  }

  //when the final row an col already has a piece so cannot be moved
  if (grid->board[fin_col - 1][c_2_i(fin_row)] != NULL) {
    printf("ERROR: Target cell is not empty.\n");
    exit(0);
  }

  //if the initial row and col holds a wrong piece in each turn
  if (count % 2 == 0 && 
      grid->board[ini_col - 1][c_2_i(ini_row)]->team == BLACK) {
    printf("ERROR: Source cell holds opponent's piece/tower.\n");
    exit(0);
  }

  if (count % 2 != 0 && 
      grid->board[ini_col - 1][c_2_i(ini_row)]->team == WHITE) {
    printf("ERROR: Source cell holds opponent's piece/tower.\n");
    exit(0);
  }

  //make sure the piece only moves diagonally/forward and backwards too
  //if the piece is a tower
  if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == WHITE && 
      grid->board[ini_col - 1][c_2_i(ini_row)]->tower == NOT_TOWER) {

    if ((c_2_i(ini_row) == c_2_i(fin_row)) || (fin_col <= ini_col)) {
      printf("ERROR: Illegal action.\n");
      exit(0);

    }
    
    if ((ini_col - fin_col == 2) && (c_2_i(ini_row) - c_2_i(fin_row) == 2 || 
         c_2_i(fin_row) - c_2_i(ini_row) == 2)) {

      if (grid->board[(fin_col-1 + ini_col-1) / 2][(c_2_i(fin_row) + 
          c_2_i(ini_row)) / 2] == NULL) {
        printf("ERROR: Illegal action.\n");
        exit(0);
      }

    }
  }

  if (grid->board[ini_col - 1][c_2_i(ini_row)]->team == BLACK && 
      grid->board[ini_col - 1][c_2_i(ini_row)]->tower == NOT_TOWER) {

    if ((c_2_i(ini_row) == c_2_i(fin_row)) || (fin_col >= ini_col)) {
      printf("ERROR: Illegal action.\n");
      exit(0);
    }

    if ((fin_col - ini_col == 2) && (c_2_i(ini_row) - c_2_i(fin_row) == 2 || 
         c_2_i(fin_row) - c_2_i(ini_row) == 2)) {

      if (grid->board[(fin_col-1 + ini_col-1) / 2][(c_2_i(fin_row) + 
          c_2_i(ini_row)) / 2] == NULL) {
        printf("ERROR: Illegal action.\n");
        exit(0);
      }

    }
  }

}

//converting row in char type to int type for calculation
int c_2_i(char row) {
  return row - 'A';
}

//calculating board cost 
int boardCost(Grid *grid) {
  int i, j, b = 0, w = 0, B = 0, W = 0, boardcost = 0;

  //loop through every piece on the board and count the number of each pieces
  for (i = 0; i < BOARD_SIZE; i++) {
    for (j = 0; j < BOARD_SIZE; j++) {

      //if empty continue
      if(grid->board[i][j] == NULL){
        continue;
      }
      
      //if black and/or tower increment by 1
      if (grid->board[i][j]->team == BLACK) {
        if (grid->board[i][j]->tower == TOWER) {
          B++;
        } else {
          b++;
        }

      //if white and/or tower increment by 1
      } else if (grid->board[i][j]->team == WHITE) {
        if (grid->board[i][j]->tower == TOWER) {
          W++;
        } else {
          w++;
        }
      }
    }
  }

  //total board cost calcualtion
  boardcost = COST_PIECE * b + COST_TOWER * B - COST_PIECE* w - COST_TOWER * W;
  return boardcost;
}

//function for creating piece
Piece *createPiece(int team, int tower) {
  //allocate memory of each piece
  Piece *piece = malloc(sizeof(*piece));
  piece->team = team;
  piece->tower = tower;
  return piece;
}

//function for creating grid
Grid *createGrid(int width, int height) {
  //allocate memory of the grid
  Grid *grid = malloc(sizeof(*grid));
  //null all the pieces on the board
  grid->board = calloc(height, sizeof(Piece**) * height);
  for(int i=0;i<height;i++){
      grid->board[i] = calloc(width, sizeof(Piece*) * width);
  }
  grid->width = width;
  grid->height = height;
  
  return grid;
}

//function for converting piece to string 
int piece_to_string(Piece *piece) {
  //if the piece is null then print '.'
  if (piece == NULL){
    return CELL_EMPTY;
  }
  
  //if white then 'w' or 'W'
  else if (piece->team == WHITE) {
    if (piece->tower == TOWER) {
      return CELL_WTOWER;
    } else if (piece->tower == NOT_TOWER) {
      return CELL_WPIECE;
    }
  }

  //if black then 'b' or 'B'
  else if (piece->team == BLACK) {
    if (piece->tower == TOWER) {
      return CELL_BTOWER;
    } else if (piece->tower == NOT_TOWER) {
      return CELL_BPIECE;
    }
  }
  return 0;
}

//function for printing the layout the grid
void printGrid(Grid *grid) {

  printf("     %s\n", HEADER);
  printf("   %s\n", BORDER2);

  for(int i=0;i<grid->height;i++){
    printf(" %d |", i+1);

    for(int j=0;j<grid->width;j++){
       printf(" %c |", piece_to_string(grid->board[i][j]));

      if(j == grid->width-1){
        printf("\n");
      }

    }

    printf("   %3s\n", BORDER2);
  }
}

//function for putting the pieces onto the empty grid using createpiece function
void lay_out_white_black(Grid *grid) {

  //row 1, 3
	for (int i = 0; i < 3; i+=2) {
		for (int j = 1; j < BOARD_SIZE; j+=2) {
			grid->board[i][j] = createPiece(0, 0);
		}
	}
  
  //row 2
	for (int i = 0; i < 7; i+=2) {
		grid->board[1][i] = createPiece(0, 0);
	}

  //row 7
	for (int i = 1; i < BOARD_SIZE; i+=2) {
		grid->board[6][i] = createPiece(1, 0);
	}

  //row 6, 8
	for (int i = 5; i < BOARD_SIZE; i+=2) {
		for (int j = 0; j < 7; j+=2) {
			grid->board[i][j] = createPiece(1, 0);
		}
	}
}

//freeing the piece after use
void freePiece(Piece *piece){
    if(piece == NULL){
        return;
    }
    
    free(piece);
}

//freeing the board after use
void freeBoard(Grid *grid){
    if(grid == NULL){
        return;
    }
    
    for(int i=0;i<grid->width;i++){
        for(int j=0;j<grid->width;j++){
            freePiece(grid->board[i][j]);
        }
        free(grid->board[i]);
    }
    free(grid->board);
}

//freeing the grid after use
void freeGrid(Grid *grid){
    if(grid == NULL){
        return;
    }
    
    freeBoard(grid);
    free(grid);
}

//function for deep copying the piece to eliminate source error 
void deep_copy_piece(Piece *old, Piece *new) {
  new->team = old->team;
  new->tower = old->tower;
}

//function for deep copying the grid to eliminate source error 
void deep_copy_grid(Grid *old, Grid *new) {

  new->width = old->width;
  new->height = old->height;

  //use nested for loops to create a new grid and copy all the items from the 
  //old board
  for(int i=0;i<new->height;i++){

    for(int j=0;j<new->width;j++){
      Piece *piece = NULL;

      if(old->board[i][j] != NULL){

        if (old->board[i][j]->team == BLACK) {

          if (old->board[i][j]->tower == TOWER) {
            piece = createPiece(1, 1);
          } else {
            piece = createPiece(1, 0);
          }

        } else {
          if (old->board[i][j]->tower == TOWER) {
            piece = createPiece(0, 1);
          } else {
            piece = createPiece(0, 0);
          }

        }
         
         deep_copy_piece(old->board[i][j], piece);
      }
      new->board[i][j] = piece;
    }
  }
}

//minimax function 
int minimax(node_t *node_t, Grid *grid, int depth, int isMax) {

    int i, j;

    //movevement array in order from NE, SE, SW, NW direction to move each piece
    int move_1[4][2] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    int move_2[4][2] = {{-2, 2}, {2, 2}, {2, -2}, {-2, -2}};  

    //terminate when depth of 3 is reached
    if (depth == 3) {
      return node_t->boardCost;
    }
    
    //when the piece wants to maximise (a.k.a: black turn)
    if (isMax) {

        //loop through the board for each piece
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {

                for (int k = 0; k < 4; k++) {
                    //allocate memory
                    node_t = malloc(sizeof(*node_t));

                    //create a new grid to deep copy the grid and pieces
                    Grid *n_grid = createGrid(BOARD_SIZE, BOARD_SIZE);
                    deep_copy_grid(grid, n_grid);
                    
                    //move the pieces from the original location to the new
                    //location on the new board
                    Piece *to = grid->board[i+move_1[k][0]][j+move_1[k][1]];
                    Piece *from = n_grid->board[i][j];
                    
                    //capture or move 
                    if (to != NULL) {
                      Piece *to = n_grid->board[i+move_1[k][0]][j+move_1[k][1]];    
                    } else {
                      Piece *to = n_grid->board[i+move_2[k][0]][j+move_2[k][1]];
                      n_grid->board[i+move_1[k][0]][j+move_1[k][1]] = NULL;
                    }

                    //make origin place null
                    n_grid->board[i][j] = NULL;
                    n_grid->board[i+move_1[k][0]][j+move_1[k][1]] = from;
                    
                    freePiece(to);
                    //calculate the boardcost of the new board
                    node_t->boardCost = boardCost(n_grid);  

                    node_t->boardCost = minNode_t(node_t, minimax(node_t, grid, 
                                                  depth + 1, !isMax));

                    free(node_t);
                    printGrid(n_grid);
                }

            }
        }
        return node_t->boardCost;  

    //when the piece wants to minimise (a.k.a: white turn)
    } else {

        //loop through the board for each piece
        for (i = 0; i < BOARD_SIZE; i++) {
            for (j = 0; j < BOARD_SIZE; j++) {

                for (int k = 0; k < 4; k++) {
                    //allocate memory
                    node_t = malloc(sizeof(*node_t));

                    //create a new grid to deep copy the grid and pieces
                    Grid *n_grid = createGrid(BOARD_SIZE, BOARD_SIZE);
                    deep_copy_grid(grid, n_grid);
                    
                    //move the pieces from the original location to the new
                    //location on the new board
                    Piece *to = grid->board[i+move_1[k][0]][j+move_1[k][1]];
                    Piece *from = n_grid->board[i][j];
                    
                    //capture or move 
                    if (to != NULL) {
                      Piece *to = n_grid->board[i+move_1[k][0]][j+move_1[k][1]];    
                    } else {
                      Piece *to = n_grid->board[i+move_2[k][0]][j+move_2[k][1]];
                      n_grid->board[i+move_1[k][0]][j+move_1[k][1]] = NULL;
                    }

                    //make origin place null
                    n_grid->board[i][j] = NULL;
                    n_grid->board[i+move_1[k][0]][j+move_1[k][1]] = from;
                    
                    freePiece(to);
                    //calculate the boardcost of the new board
                    node_t->boardCost = boardCost(n_grid);    

                    node_t->boardCost = minNode_t(node_t, minimax(node_t, grid, 
                                                  depth + 1, isMax));

                    free(node_t);
                    printGrid(n_grid);
                }

            }
        }
        return node_t->boardCost; 
    }
  return 0;
}

//calculating the max boardcost of the two nodes
int maxNode_t(node_t *left, int value) {
  if (left->boardCost >= value) {
    return left->boardCost;
  } else {
    return value;
  }
}

//calculating the min boardcost of the two nodes
int minNode_t(node_t *left, int value) {
  if (left->boardCost <= value) {
    return left->boardCost;
  } else {
    return value;
  }
}

// algorithms are fun

/* THE END -------------------------------------------------------------------*/