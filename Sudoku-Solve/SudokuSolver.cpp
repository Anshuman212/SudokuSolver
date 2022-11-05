#include <iostream>
#include <fstream>
using namespace  std;
 /*
  Let's define a class that manipulates the structure of the values of the sudoku puzzle

  */
 class sudokuFrame {
     int sudoku[9][9];//hold all the values of the matrix
     int editMat[9][9]; // hold the editable values of the matrix
     //let's call in the menu() function to display the the menu readable format
 public:
     sudokuFrame() {
         sudokuMenu();
     }

 private:
    void  sudokuMenu() {
         cout << "\n=====================================================\n";
         cout << "                    Darth Sudoku Solver\n";
         cout << "======================================================\n\n";
         cout << "Let's get Started\n";
         cout << "Input the puzzle\n";
         cout << "Can do it in either of two ways\n";
         cout << "\t1. Input the puzzle by entering the values manually. (Press 1)\n";
         cout << "\t2. Input the puzzle by reading a file with values in it. (Press 2)\n";
         cout << "\t   Note-The file must not have a name > 20 characters.\n";
         cout << "\t   The file must be in the same directory as this C++ file.\n";
         cout << "\t   The file must have all 81 values seperated with spaces.\n";
         cout << "\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
         cout << "\t   --> ";


     int choice;
     cin >> choice;
     if(choice == 1){
         readValues(); // if choice is input values
     }
     else if(choice == 2){
         readValueFile(); // if choice is to read from file
     }
     else{ // if user doesn't input either of the above
         while (true) {
             cout << "Wrong Input.. Enter again\n";
             cout << "\t    -----------------> ";
             cin >> choice;
             if (choice == 1) readValues();
             else if (choice == 2) readValueFile();
             else continue;
             break;
             }
         }
    }
    // function to take input of the values
 private: void readValues() {
         cout << "Enter the values in specified order\n";
         cout << "FOR AN EMPTY CELL ENTER 0\n";
         int row,column;
         for(row =0;row<9;row++){
             for(column = 0; column<9;column++){
                 int val;
                 cout << "Enter the values for cell["<< (row+1) << "]["<< (column+1)<<"]\n";
                 cin>>val;
                 if(!(val>=0&&val<=9)){ // checking for the boundary conditions
                     while(true){
                         cout << "Seems values is incorrect.. Enter again!";
                         cin>>val;
                         if(val>=0 && val<=9) break;
                     }
                 }
                 sudoku[row][column]=val;
                 if(val == 0){
                     editMat[row][column] = 0;
                 }
                 else {
                     editMat[row][column] = 1;
                 }
             }
             cout << "displaying row just to differentiate\n";
         }
     }
 private:void readValueFile(){
         char filename[40];
         cout << "\n Enter the name of the file that contains the puzzle\n";
         cout << " ==================================>\n";
         cin>>filename;
         ifstream infile; // opening file for reading
         infile.open(filename,ios::in);
         int row,column;
         for(row = 0;row<9;row++){
             for(column = 0;column<9;column++){
                 int readval;
                 infile>>readval;
                 if(!(readval>=0 && readval<=9)){
                     cout << "seems the entered file has wrong value of row:- " << row+1 << " column:- "<< column+1;
                     exit(EXIT_FAILURE);

                 }
                 sudoku[row][column] = readval;
                 if( sudoku[row][column] == 0) editMat[row][column] = 0;
                 else editMat[row][column] = 1;
                 if(infile.eof()) break; // breaking if the end of the file is reached
             }
         }
         infile.close();
     }
    // assigns passed in value to specified row column
 public:void setCellValue(int row,int column,int num){
         if(editMat[row][column]==0) sudoku[row][column] = num;
     }
     //getting value of a specific cell
 public:int getCellValue(int row,int column){
         return sudoku[row][column];
     }
     //  returning if the value is editable 1 for true 0 for false
 public:int isEditable(int row,int column){
         return (editMat[row][column]-1)*(-1);
     }
     // let's define a fuction to clear all the values from the cell except the original ones
 public:void clearFrame(int row, int column){
         int jcount=0;
         int r,col;
         for(int r=row;r<9;r++){
             if(jcount==0)col=column;
             else col=0;
             for(;col<9;col++){
                 if(editMat[r][col] == 0) sudoku[r][col] = 0;
             }
             jcount++;
         }
     }
     // displaying the frame along with some ANSI colour codes
 public:void displayFrame(){
         cout<<"\033[0;36m++==========================================++";
         int row,column;
         for(row=0;row<9;row++){
             int cell=1;
             cout<<"\n\033[0;36m||";
             for(column=0;column<9;column++){
                 if(cell == 3){
                     cout<<"\033[0m "<<sudoku[row][column]<<" ";
                     cout<<"\033[0;36m||";
                     cell=1;
                 }
                 else {
                     cout << "\033[0m "<< sudoku[row][column]<<" ";
                     cell++;
                 }
             }
             if(row%3!=2) cout<<"\n\033[0;36m++-----------++-----------++-----------++";
             else cout<<"\n\033[0;36m++=====================================++";
         }
     }
 };
 // defining another class that provides us to iterate through all the possibilities of any specified cell .. this
 // object uses linked list
 class possibilities{

     struct node{
         int val;
         struct node* next;
     }; // structure of the node
     typedef struct node* Node;
     Node head; // the head node
     Node pos; // iterator variable
     // initializing the head node
 public:possibilities(){
         head = new struct node;
         head -> next = NULL;
     }
     // destructor to destroy the linked list once it's lifespan is over via calling the destroy()
 public:~possibilities(){
         destroy();
     }
// function that takes in a number and adds it as node to the linked list
 public:void append(int num){
         Node temp = new struct node;
         temp->val = num;
         temp->next = NULL;
         pos = head;
         while(pos != NULL){
             if(pos ->next==NULL){
                 pos->next=temp;
                 break;
             }
             pos=pos->next;
         }
     }
     // an operator overload just to provide the feel for array
 public: int operator[](int index){
         int count=0;
         pos=head->next;
         while(pos != NULL){
             if(count==index) return pos->val;
             pos=pos->next;
             count++;
         }
         return -1;
     }
     // print function to print the values of all the nodes in the linked list;
 public: void print(){
         pos=head->next;
         while (pos != NULL){
             cout << pos->val << " ":
             pos=pos->next;
         }
          cout << "\n";
     }
     // function to print the length of the linked list
 public: int length(){
         pos= head->next;
         int count=0;
         while(pos != NULL){
             pos=pos->next;
             count++;
         }
         return count;
     }

     // takes in possibilities object and copies the content into THIS object
 public:void copy(possibilities Possibilities){
         int lastlength = Possibilities.length();
         int it =0;
         pos= head;
         for(it=0;it<lastlength;it++){
             Node temp = new struct node;
             temp->next=NULL;
             temp->val = Possibilities[it];
             pos->next= temp;
             pos= pos->next;
         }
     }
     // the destroy function
 private:void destroy(){
         Node temp;
         pos=head;
         while(pos != NULL){
             temp=pos;
             pos=pos->next;
              delete temp;
         }
     }

 };

 // defining a class that takes in the sudoku object and solves the puzzle
 class SudokuSolver{
     int recursiveCount ;
     sudokuFrame frame; // frame object
     // defining a constructor to intialize the count and calls the solve function to solve the puzzle
 public:SudokuSolver(){
         recursiveCount=0;
         cout<<"\nCalculating possibilities...\n";
         cout<<"Backtracking across puzzle....\n";
         cout<<"Validating cells and values...\n\n";

         solve();
         cout << "Your Puzzle has been solve\n";
         displayFrame();
         cout << "\n\n";

     }
     // method that validates the value in a specific cell is valid or not
 private:bool cellValueValid(int row, int column, int currValue){
         int rit,colit;
         //checking if value exits in the same column
         for(rit=0;rit<9;rit++){
             if(rit != row){
                 int compareValues = frame.getCellValue(rit,column);
                 if(compareValues == currValue) return false;
             }
         }
         // method to check the values in the same row
         for(colit=0;colit<9;colit++){
             if(colit!=column){
                 int compareValue = frame.getCellValue(row,colit);
                 if(compareValue == currValue) return false;
             }
         }
         // checking if the value exits in the 3x3 matrix
         if(ThreeByThreeGridValid(row,column,currValue) == false) return false;
         return  true;
     }
     // method that checks if the same value exists in the 3x3 matrix
 private:bool ThreeByThreeGridValid(int row, int column,int currentValue){
         int rowStart= (row/3)*3;
         int rowEnd = rowStart+2;
         int columnStart = (column/3)*3;
         int columnEnd = columnStart+2;
         int rit,colit;
         for(rit = rowStart;rit<=rowEnd;rit++){
             for(colit=columnStart;colit<=columnEnd;colit++){
                 if(frame.getCellValue(rit,colit) == currentValue) return false;
             }
         }
         return true;
     }
     //method to get the possibilities and assign them to the possibility list
 private:possibilities getCellPossibilities(int row,int column){
         int it =0;
         possibilities Possibilities;
         for(it=1;it<=9;it++){
             if(cellValueValid(row,column,it)== true) Possibilities.append(it);
         }
         return Possibilities;
     }
     // recursive method that does all the work if the value is valid goes to the other cell else backtracks
 private:int singleCellSolve(int row,int column){
         statsIncrement();
         // used to see the number of times the function is called
         if(frame.isEditable(row,column) == true){
             possibilities Possibilities;
             Possibilities.copy(getCellPossibilities(row,column));
             int posLength = Possibilities.length();
             int posItr=0,newRow=row,newCol=column;
             for(posItr=0;posItr<posLength;posItr++){ //iterate over the possible values
                 int possibility = Possibilities[posItr];
                 frame.setCellValue(row,column,possibility);
                //now increment the row/col values for the next set of recursion
                if(column<8)column+=1;
                else if(column==8){
                    if(row == 8) return 1; // denotes success
                    newRow = row+1;
                    newCol=0;
                }
                else{
                    if(singleCellSolve(newRow,newCol) ==0){
                        //if wrong clear the frame and start over
                        frame.clearFrame(newRow,newCol);
                    }
                    else return 1;
                }
             }
             return 0;
         }
         else{
             int newRow=row,newCol = column;
             //increment the row and col
             if(column<8) newCol=column+1;
             else if(column==8){
                 if(row==8) return 1;
                 newRow=row+1;
                 newCol=0;
             }
             return singleCellSolve(newRow,newCol);
         }

     }
     // method to call the recursive singleCellSolve and print the success or failure
 private:void Solve(){
         int success = singleCellSolve(0,0);
     }
     //display the sudoku frame by calling displayFrame();
 private:void displayFrame(){
         frame.displayFrame();
     }
     // increments the count variable and tracks the recursion
 private:void statsIncrement(){
         recursiveCount++;
     }
     //method to display the number of times the recursion occurs
 private:void statsPrint(){
         cout << "The recursive function recursively called "<< recursiveCount<< "times\n";
     }

 };
 int main(){
     SudokuSolver ss;
     return 0;
 }
