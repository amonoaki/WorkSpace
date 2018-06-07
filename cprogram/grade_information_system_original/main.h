#define N 50       //set the number of students
#define SUB_ONE sub1
#define SUB_TWO sub2
#define SUB_THREE sub3
#define SUB 3     //make sure the number of subject

typedef struct Student {
	char id[20];      //the student's id
	char name[20];    //the student's name
	float SUB_ONE;    //subject one
	float SUB_TWO;    //subject two
	float SUB_THREE;  //subject three
	float total;      //total grade
	float aver;       //average grade
}STU;
