#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000
/** Dana Sobhi Section 1 **/
struct AVLnode;
typedef struct AVLnode *AVL_T;
AVL_T ElemenateNode(AVL_T t, char key[]);
struct AVLnode{
  //  char Data[MAXSIZE];
char Course[250];
char CreditHours[50];
char CourseCode[250];
char Department[250];
char topics[MAXSIZE];

    AVL_T Left;
    AVL_T Right;
    int Height;
};

int getHeight (AVL_T t){
    if(t==NULL)
        return -1; //if the node is empty return -1
    else
        return t->Height; //else return the height of the node
}
int MAX (int x, int y){ //function to return max number
    if(x>y) //if x higher than y
        return x; //return x
    else
        return y; //return y
}
int getBal(AVL_T t) // function to return the balance by calculating the deference between node heights
    {           // so we can know if we need to re sort the tree to be balanced
        if (t == NULL)
            return 0; //tree is empty return 0
        return getHeight(t->Left) - getHeight(t->Right); //else calculate the height from left and from right and return it
    }
AVL_T singleRotateLeft(AVL_T x) { //function to rotate the tree to the left once
    AVL_T y; //construct a temp tree to work on
    y         = x->Right; // get valued from x->right
    x->Right  = y->Left; //let the right side of x equals to the left side of y
    y->Left = x; // set left side of y  , x.

    x->Height = 1 + MAX(getHeight(x->Left) , getHeight(x->Right)); //set the height for x
    y->Height = 1 + MAX(getHeight(x) , getHeight(y->Right)); //set the height for y

    return y; //return y.
}
AVL_T singleRotateRight(AVL_T y) {//function to rotate the tree to the right once
    AVL_T x; //construct a temp tree to work on
    x        = y->Left;// get valued from y->left
    y->Left  = x->Right;  //let the left side of y equals to the right side of x
    x->Right = y; // set right side of x  , y .

    y->Height = 1 + MAX(getHeight(y->Right) , getHeight(y->Left));//set the height for y
    x->Height = 1 + MAX(getHeight(y) , getHeight(x->Left)); //set the height for x

    return x; //return x
}
AVL_T doubleRotateLeft(AVL_T K3) { //function to do left then right rotate to the tree " double left "
    K3->Left  = singleRotateLeft(K3->Left);
    return singleRotateRight(K3);
}
AVL_T doubleRotateRight(AVL_T K3) { //function to do right then left rotate to the tree " double right "
    K3->Right  = singleRotateRight(K3->Right);
    return singleRotateLeft(K3);
}
//////////////////////////////////////////////////////////////////////
AVL_T insert (AVL_T t, char Course[],char CreditHours[],char CourseCode[],char Department[],char topics[]){
    if(t==NULL){
        t=malloc(sizeof (struct AVLnode)); //create a new node if the tree is empty
    strcpy(t->Course,Course); //copy the course into course  of the tree
    strcpy(t->CreditHours,CreditHours); //copy the credit hours into the credit hours of the tree
    strcpy(t->CourseCode,CourseCode); // course code into course code
    strcpy(t->Department,Department); //department into department
    strcpy(t->topics,topics); //topics into topics

       t->Height=0; //the height is zero
        t->Left= t->Right=NULL; //there's no children.

    }
    else if(strcmp(CourseCode , t-> CourseCode)<0){//if there's a tree check whether the course code is lower than the node
        t->Left=insert(t->Left,Course,CreditHours,CourseCode,Department,topics); //then it goes to the left
        if(getHeight(t->Left) - getHeight(t->Right) >= 2){//if the height more than 2
            if(strcmp(CourseCode , t->Left->CourseCode)<0) //if the course code less than t->Left->CourseCode
                t=singleRotateRight(t); //do a single rotate to right
            else
                t=doubleRotateLeft(t); //else single rotate to the left
        }
    }
    else if(strcmp(CourseCode , t->CourseCode)>0){//if the course code is higher than t->course code
        t->Right = insert(t->Right ,Course,CreditHours,CourseCode,Department,topics); //insert to the right
        if(getHeight(t->Right) - getHeight(t->Left) >= 2){ //check for balance
            if(strcmp(CourseCode , t->Right->CourseCode)>0) //if course code is higher than t->right->course code
                t=singleRotateLeft(t); //single rotate to the left
            else
                t=doubleRotateRight(t); //else to the right
        }
    }

    t->Height = 1 + MAX(getHeight(t->Right) , getHeight(t->Left)); //set the height of this node

    return t; //return the tree
}
//////////////////////////////////////////////////////////////////////
FILE *lastTree; //construct a file to save at
void printPreOrder(AVL_T t){ //function to print into the file   root -> left -> right .
    if(t!= NULL){  //while the tree is not empty
      fprintf(lastTree,"Course ID: %s  ||\t Name : %s \n",t->CourseCode,t->Course); //print the course id with the course name
      fprintf(lastTree,"Department : %s \n",t->Department); //department
      fprintf(lastTree,"\nNumber of hours And topic presented:\n");
      fprintf(lastTree,"\t%s \t %s\n",t->CreditHours,t->topics); // credit hour with topics
      fprintf(lastTree,"---------------------------------------------------------------\n");
      printPreOrder(t->Left); //do the left side of the tree
      printPreOrder(t->Right); //then the right side of the tree
    }
}
/////////////////////////////////////////////////////////////////////
void searchTree(AVL_T t,char key[]){

if(t !=NULL){ //while the node is not null
    if(strcmp(t->CourseCode,key)==0){//check if the code matches course code
      printf("Course ID: %s \t || Name : %s \n",t->CourseCode,t->Course); //print this data
      printf("\n topic presented:\n");
      printf("\t %s \n",t->topics); //with its topics
    }
      searchTree(t->Left,key); //check from the left side of the tree
      searchTree(t->Right,key); //check from the right side of the tree
}

}
/////////////////////////////////////////////////////////////////////
AVL_T updatingData(AVL_T t,char key[]){
if(t != NULL){// if the tree is not empty

if(strcmp(t->CourseCode,key)==0){ //check if the code key matches the course code of this node
    t = ElemenateNode(t,key); //remove old date

            printf("%s\n",key); //show the course code
            printf("Enter Course name:");
            char tempCourse[250];
            scanf("\n %[^\n]s",tempCourse); //get the name
            printf("Enter Course hours:");
            char tempHours[5];
            scanf("\n %[^\n]s",tempHours); //get the number of hours
            printf("Enter Course Department:");
            char tempDepartment[250];
            scanf("\n %[^\n]s",tempDepartment); //get the department name
            printf("Enter Course topics:");
            char temptopics[MAXSIZE];
            scanf("\n %[^\n]s",temptopics); //get the topics

            t=insert(t,tempCourse,tempHours,key,tempDepartment,temptopics); //insert them again into the tree
            return t; //return the tree
}

t->Left= updatingData(t->Left,key); //else check from the left
t->Right=  updatingData(t->Right,key); //else check from the right
}
}
/////////////////////////////////////////////////////////////////////
AVL_T smallestNode(AVL_T t){//find the min node of the tree
    AVL_T thisT = t;
    while (thisT->Left != NULL) //loop until there's no left.
       thisT= thisT->Left ;

       return thisT;
}
////////////////////////////////////////////////////////////////////

AVL_T readFile(AVL_T t){
    char string[1000]; // String we will store what we will scan from the file in.
    FILE* b = fopen("courses.txt","r"); // select the file to open, and scan it later
    if(b == NULL) // if the file does't exist print
        printf("File is empty!\n");
    else  //the file exist, then:
        while(fgets(string, sizeof(string), b) != NULL){
   // printf("%s\n",string);
    char * temp = strtok(string, ":"); //present course name
  //    printf("Course :%s\n",temp);
    char * temp2 = strtok(NULL, "#"); //present credit hours
  //      printf("CreditHours :%s\n", temp2 );
    char * temp3 = strtok(NULL, "#"); //present course code
 //       printf("CourseCode : %s\n", temp3 );
    char * temp4 = strtok(NULL, "/"); //present department name
 //       printf("Department :%s\n", temp4 );

    char * temp5 = strtok(NULL, "/"); //present topics
 //    printf( "Topic %s:\n",temp5 );
/*
for(int i =0; i< sizeof(string);i++){
    char * temp6 = strtok(NULL, ",");
if(temp6 == NULL)
    break;
}*/
// I Wanted to separate each subject , yet thinking about it it would be easier not to, and instead use it as one string.
t = insert(t , temp,temp2,temp3,temp4,temp5); //insert them into the tree
        }//until the end of the file .

    printf("The Input file has been read\n"); // print when this function read without problems
    fclose(b); // close the file we opened before
return t;//return the AVL tree.
}

///////////////////////////////////////////////////////////////////

AVL_T ElemenateNode(AVL_T t, char key[]){
if(t==NULL){ //if the tree is empty
        printf("Does not exist \n");
    return t; //return t
}

if(strcmp(key,t->CourseCode)<0){ // t->course code has a higher ASCII code than the key.
     t->Left = ElemenateNode(t->Left,key);//search on the left side on the tree " lower part"
}
else
if(strcmp(key,t->CourseCode)>0){// t->course code has a lower ASCII code than the key.
     t->Right = ElemenateNode(t->Right,key); //search on the right part of the tree " higher part"
}
else
{ //neither left nor right this this node to delete from tree.
    if((t->Left == NULL) || ( t->Right == NULL)){ // if there's a child from left or right or none at all.
    AVL_T tetree = NULL; //construct a tree to work on.
    if(t->Left) //check if we are on the left of the right side of tree t
            tetree = t->Left; // if we are on the left side let tree tetree be t->left
    else tetree = t->Right; //else we are on the right side of the tree


    if(tetree == NULL){ //else its none , there's no children
        tetree = t; // let the tree copy the data from the node
        t = NULL; // let it be null  .
    }
    else //there's one child
    t = tetree; //copy the data of the child
    tetree = NULL;
   // free(tetree); //free the tree.
    }

    else{
            //the tree contain two children
            //get the smallest node of tree from the right
        AVL_T tea =  smallestNode(t->Right);
        //copy all the data from the tree tea into the tree
        strcpy(t->CourseCode,tea->CourseCode);
        strcpy(t->Course,tea->Course);
        strcpy(t->CreditHours,tea->CreditHours);
        strcpy(t->topics,tea->topics);
        strcpy(t->Department,tea->Department);
        //delete this tree " tea"
        t->Right=ElemenateNode(t->Right,tea->CourseCode);

    }

}
//check if there's a node in the tree
if(t==NULL){
printf("Deleted \n");
    return t; //return
}
//update the height of the tree node after deletion
t->Height = 1 + MAX(getHeight(t->Left),getHeight(t->Right));
//get the balance from the get balance function from before
 int bal = getBal(t);
 //in case the tree is unbalanced
if(bal > 1 && getBal(t->Left)>=0 ){ //if the balance from the left more or equal than 0 , and balance of the node is >1
    return singleRotateRight(t); //rotate to right
}
if (bal >1 && getBal(t->Left) < 0 ){ //if the balance from the left less than 0 , and balance of the node is >1
    return doubleRotateLeft(t); //double rotate  to left " left right"
}
if(bal < -1 && getBal(t->Right) <=0 ){ //if the balance from the right more or equal than 0 , and balance of the node is <-1
    return singleRotateLeft(t); //rotate once to the left
}
if (bal < -1 && getBal(t->Right) > 0 ){ //if the balance from the right more than 0 , and balance of the node is <-1
    return doubleRotateRight(t);//double rotate  to right " right left"
}

return t; //return the tree
}
///////////////////////////////////////////////////////////////////
int is =0; //initial integer to work with
char codes[MAXSIZE][250]; //array of strings to store codes we get
void searchFromDepart(AVL_T t , char key[]){ //function to find and store matched department .
if(t!=NULL){ //if the node it not empty
    if(strcmp(t->Department,key)==0){ //check if the department matches the key
        strcpy(codes[is],t->CourseCode);//if yes copy the course code of this node
        is++; //store it in global array to use it later .
        }
searchFromDepart(t->Left,key); //check from the left of the tree.
searchFromDepart(t->Right,key); //check from the right of the tree
}

}
///////////////////////////////////////////////////////
int chacha=0; //initial integer to work with
char needed[MAXSIZE][250]; //array of strings to store codes we get
void searchLetter(AVL_T t , char key){
if(t!=NULL){
    char *temp = t->CourseCode; // pointer to store the string in
    char begining = temp[0]; //get the first letter on string
    if(begining == key){ //check if the first letter matches the key
      //  printf("%c\n",begining); // to test if it works.
        strcpy(needed[chacha],t->CourseCode);//if yes copy the course code of this node
        chacha++; //store it in global array to use it later .
        }

searchLetter(t->Left,key); //check from the left of the tree.
searchLetter(t->Right,key); //check from the right of the tree
}

}
//////////////////////////////////////////////////

AVL_T Elemenations(AVL_T t,char key[]){
is =0; //return is into 0 so we can reset what's in the string
searchFromDepart(t,key);//call the function to store the array we need
if(is == 0){
     printf("Department Does not exist . \n");
     }
else{ printf("The Courses will be deleted : \n");
for(int i =0; i<=is; i++){ //do a loop to check
    printf("%s\n",codes[i]); //get the codes we want to delete
   t = ElemenateNode(t,codes[i]); //send those codes to the function to delete them
    }
}
is = -1;
 return t;//return the tree after deletion
}
//////////////////////////////////////////////////
AVL_T ElemenateLetter(AVL_T t,char key){ //this function  to delete by character
chacha =0; //reset
searchLetter(t,key); //call the function
if(chacha == 0){
     printf("No Courses have this letter. \n");
}
else{ printf("The Courses will be deleted : \n");
for(int i =0; i<=chacha ; i++){
    printf("%s\n",needed[i]);
   t = ElemenateNode(t,needed[i]); //delete the nodes .
    }
}
chacha = -1;
 return t; //return the tree after deleting
}

int d = 0; // integer to work with
char dcodes[MAXSIZE][250]; // array of strings

void searchForcode(AVL_T t){ //function to search for course codes and store them on the array
if(t!=NULL){
        strcpy(dcodes[d],t->CourseCode);//if yes copy the course code of this node
        d++; //store it in global array to use it later .
        searchForcode(t->Left); //check from the left of the tree.
        searchForcode(t->Right); //check from the right of the tree*/
    }
}
////////////////////////////////////////////////////////////
void searchTreeWithData(AVL_T t,char key[]){ // to print tree needed with its Data for number 4.
    //List courses in lexicographic order with their associated information (credit hours, IDs, and topics)
if(t !=NULL){ //while the node is not null
    if(strcmp(t->CourseCode,key)==0){//check if the code matches course code
      printf("Course ID: %s \t || Name : %s \n",t->CourseCode,t->Course); //print this data
      printf("Department : %s \n",t->Department);
      printf("\nNumber of hours presented:\n");
      printf("\t%s \t \n",t->CreditHours); //with its topics

    }
      searchTreeWithData(t->Left,key); //check from the left side of the tree
      searchTreeWithData(t->Right,key); //check from the right side of the tree

}
}
//////////////////////////////////////////////////
void printSorted(AVL_T t){ //the function we will call to be sorted  in lexicographic order.
d=0; //reset
searchForcode(t); //call the function  we need
if(d == 0){
     printf("No courses exist . \n");
     }
else{
char temp[250]; //create a temporarily string  to store in.

   for (int i = 0; i <= d; ++i) { //start a loop with first  array of strings codes[i]
      for (int j = i + 1; j <= d; ++j) { //start a loop with second array of strings codes [j]

         if (strcmp(dcodes[i], dcodes[j]) > 0) { //if the ASCII code for code[i] higher
            strcpy(temp, dcodes[i]); //store it in the temp string
            strcpy(dcodes[i], dcodes[j]); //copy the content from the smaller string
            strcpy(dcodes[j], temp); // switch the content now codes[j] is higher
         }
      }
   }

for (int i = 0; i <= d ; ++i) {
    searchTreeWithData(t,dcodes[i]); //search the strings after we sorted them and print them.
   }

}
d = -1;
}
//////////////////////////////////////////////////
void printCoursesD(AVL_T t,char key[]){ // List all courses in lexicographic order that belong to the same department.
is =0; //reset
searchFromDepart(t,key); //get the array we want to sort by using search function.
if(is == 0){
     printf("Department Does not exist . \n");
     }
     else{
char temp[250];

   for (int i = 0; i <= is; ++i) { //start a loop with first  array of strings codes[i]
      for (int j = i + 1; j <= is; ++j) { //start a loop with second array of strings codes [j]

         if (strcmp(codes[i], codes[j]) > 0) { //if the ASCII code for code[i] higher
            strcpy(temp, codes[i]); //store it in the temp string
            strcpy(codes[i], codes[j]); //copy the content from the smaller string
            strcpy(codes[j], temp); // switch the content now codes[j] is higher
         }
      }
   }
for (int i = 0; i <= is ; ++i) {
    searchTree(t,codes[i]); //search the strings after we sorted them and print them.
   }
}
is= -1;
}
//////////////////////////////////////////////////
int main()
{
printList(); //print the list we want to choose from
printf("Select from the menu.\n");
AVL_T root = NULL; //construct the tree we work with
int x =0; //integer to choose from the list
do{
    scanf("\n%d",&x); //read the number

switch (x) { //switch cases depend on x
case 1 :
    root = readFile(root); //fist case read the file
    break;

case 2:
printf("Option  2 Insertion \n"); //choose 2 to insert
    char Course[250];
    char CreditHours[5];
    char CourseCode[250];
    char Department[250];
    char topics[MAXSIZE];

            printf("Enter Course name:");
            scanf("\n %[^\n]s",Course); //read the course name [^\n] is to read until end of line.
            printf("Enter Course hours:");
            scanf("\n %[^\n]s",CreditHours); //credit hours [^\n] is to read until end of line.
            printf("Enter Course Code:");
            scanf("\n %[^\n]s",CourseCode); //course code [^\n] is to read until end of line.
            printf("Enter Course Department:");
            scanf("\n %[^\n]s",Department); //department [^\n] is to read until end of line.
            printf("Enter Course topics:");
            scanf("\n %[^\n]s",topics); //topics of the course [^\n] is to read until end of line.

    root = insert(root,Course,CreditHours,CourseCode,Department,topics); //insert them into the tree root
printf("Success \n");
break;

case 3 :
printf("Option 3\n");  // Find a course and support updating of its information

    printf("Enter Course Code:");
    scanf("\n %[^\n]s",CourseCode); //read the course code we want to update
    root = updatingData(root,CourseCode); //updating the data

 break;
case 4 :
printf("Option 4\n"); //List courses in lexicographic order
    printSorted(root); //call the function that sorted the tree

break;
case 5 :
    printf("Option 5\n"); //List all topics associated with a given course
    printf("Enter Course Code:");
    scanf("\n %[^\n]s",CourseCode); //get the course code to share
    searchTree(root,CourseCode); //print the course with its data
    printf("Done Searching.No info No course code like this Exist  \n");

break;

case 6 :
    printf("Option 6\n"); //List all courses in lexicographic order   department
    printf("Enter Course Department:");
    scanf("\n %[^\n]s",Department); //read the department name
printCoursesD(root,Department); //sent it to the function we will work with.

break;

case 7 :
    printf("Option 7\n"); //Delete a course.
    printf("Enter Course Code:");
    scanf("\n %[^\n]s",CourseCode); //get course code
    root = ElemenateNode(root,CourseCode); // remove the node  and return new tree

break;
case 8 :
    printf("Option 8 \n"); //Delete all courses that start with a specific letter.
    printf("Enter letter:");
    char p; //create a temp character to work with
    scanf("\n%c",&p); //read the character
   root= ElemenateLetter(root,p); //send it to delete

    break;
case 9 :
    printf("Option 9\n");  //Delete all courses that start with a specific letter.
    printf("Enter Course Department:");
    scanf("\n %[^\n]s",Department); //get by reading the line and [^\n] is to read until end of line.
   root = Elemenations(root,Department); //send the department

break;
case 10:
    printf("Option 10\n"); // Save all words in file offered_courses.txt
    lastTree = fopen ("offered_courses.txt","w"); //open the file to store at it
    printPreOrder(root); //print them in call the function of print.
    fclose(lastTree); //then close it
    printf("Saved to the file \n");

}
if(x == 11)
    break;
printList(); //print the list after each option
printf("Select from the menu.\n");  //with choosing the x.
}while(x != 11);
printf("\n"); //choosing 11 will exit from the loop and close the program.


    return 0;
}

////////////////////////////////////////////////////////////
void printList(){
printf("************************************************\n");
printf("*1-           Store From the File              *\n");
printf("*2-         Insert A New Course info           *\n");
printf("*3-       Update A Selected Course info        *\n");
printf("*4-      Print Courses lexicographically       *\n");
printf("*5-    Print All topics By Selected course     *\n");
printf("*6-    Print Courses By Selected Department    *\n");
printf("*7-           Delete A Course info             *\n");
printf("*8-         Delete Courses By Letter           *\n");
printf("*9-       Delete Courses By Department         *\n");
printf("*10-             Save In the file              *\n");
printf("*11-                   Exit                    *\n");
printf("************************************************\n");
}
///////////////////////////////////////////////////////////
