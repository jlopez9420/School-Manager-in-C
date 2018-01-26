#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	---- STRUCTURES ----
*/

typedef struct Student{
	int student_id;
	char student_name[30];
	struct Student* next;
}Student;

typedef struct Teacher{
	int teacher_id;
	char teacher_name[30];
	struct Teacher *next;
}Teacher;

/*
	---- FUNCTIONS DECLARATIONS ----
*/

//	Student functions declarations
int Student_autoNumber (Student** sFirst);
void Student_insert (Student** sFirst);
void Students_show (Student* sFirst);
Student* Student_search (Student* sFirst, int id);
bool Student_delete (Student** sFirst, int id);
/*
	---- MAIN FUNCTION ----
*/

int main () {

	Student *sFirstNode = NULL;

	Student_insert (&sFirstNode);
	Student_insert (&sFirstNode);
	Student_insert (&sFirstNode);
	Student_insert (&sFirstNode);

	Students_show (sFirstNode);
	Student_delete (&sFirstNode, 1);
	Students_show (sFirstNode);
	Student_delete (&sFirstNode, 3);
	Students_show (sFirstNode);
	Student_delete (&sFirstNode, 4);
	Students_show (sFirstNode);

	Student_insert (&sFirstNode);
	Student_insert (&sFirstNode);
	Students_show (sFirstNode);

	return 0;
}

/*
	---- FUNCTIONS ----	
*/

//This functions finds the first student id available in the
//linked list using a counter that is being incremented by 1.
int Student_autoNumber (Student** sFirst) {
	Student* sNode = *sFirst;
	int number = 1;

	while (sNode != NULL && number == sNode->student_id) {
		sNode = sNode->next;
		number++;
	}

	return number;
}

//This function inserts (in a sorted way) a student in a
//linked list.
void Student_insert (Student** sFirst) {
	Student* sNewNode =  (Student *) malloc(sizeof(Student));

	//In this block we add the attributes for the new student
	sNewNode->student_id = Student_autoNumber(sFirst);
	printf("Please enter the student's name: ");
	scanf("%s", sNewNode->student_name);
	printf("%d\n", sNewNode->student_id);

	//We check if the node will be the very first on the linked list.
	if (sNewNode->student_id == 1) {
		//We check two possible scenarios, if the linked list is empty
		//or if first node (the one with id=1 only) was deleted and needed
		if (!(*sFirst)) {
			*sFirst = sNewNode;
			sNewNode->next = NULL;
		} else {
			sNewNode->next = *sFirst;
			*sFirst = sNewNode;
		}
	} else {
		Student* sNode = *sFirst;
		//We go to the position on the right of the link list from the new node
		while (sNode->next != NULL && sNode->student_id != ((sNode->student_id) - 1)) {
			sNode = sNode->next;
		}
		//Two possible scenarios, if its the very last node or if it needs to be
		//inserted between nodes.
		if (sNode->next == NULL) {
			sNode->next = sNewNode;
			sNewNode->next = NULL;
		} else {
			sNewNode->next = sNode->next;
			sNode->next = sNewNode;
		}
	}
}

//This function shows all students, goes through the linked list 
//and prints the nodes.
void Students_show (Student* sFirst) {
	Student* sNode = sFirst;

	printf("ID\t\tNAME\n");
	while (sNode != NULL) {
		printf("%d\t\t%s\n", sNode->student_id, sNode->student_name);
		sNode = sNode->next;
	}
}

//This functions return the student to be searched, goes through
//the linked list and evaluates the id in parameter with the linked list nodes.
Student* Student_search (Student* sFirst, int id) {
	Student* sNode = sFirst;

	while (sNode != NULL) {
		if (sNode->student_id == id) {
			return sNode;
		}
		sNode = sNode->next;
	}
	return NULL;
}

bool Student_delete (Student** sFirst, int id) {
	Student* sNode = Student_search(*sFirst, id);
	if (sNode) {
		if (sNode == *sFirst) {
			*sFirst = sNode->next;
			return true;
		} else {
			sNode = *sFirst;
			Student* sNodeLast = NULL;
			while (sNode->student_id != id) {
				sNodeLast = sNode;
				sNode = sNode->next;
			}
			sNodeLast->next = sNode->next;
		}
	}
	return false;
}