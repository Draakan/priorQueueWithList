#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
	char *message;
	int priority;

	Node *Next, *Prev;
};

struct QueuePriority
{
	int QueueLength, MaxQueueLength;

	Node *Head, *Tail;
}*qp;

int GetLength() { return qp->QueueLength; }

bool IsEmpty() { return qp->QueueLength == 0; }

bool IsFull() { return qp->QueueLength == qp->MaxQueueLength; }

void SetMaxLength(int digit)
{
		qp->Head = qp->Tail = NULL;

		qp->QueueLength = 0;
		qp->MaxQueueLength = digit;
}

void Add(char *message, int priority)
{
	if (!IsFull())
	{
		Node *temp = (Node*)malloc(sizeof(Node)), *tempOne = qp->Head;

		temp->Prev = NULL;
		temp->Next = NULL;

		temp->priority = priority;
		temp->message = (char*)malloc(strlen(message) + 1);

		if (!temp->message)
		{
			puts("Allocation error");
			exit(1);
		}

		strcpy(temp->message, message);

		if (qp->QueueLength == 0)
		{
			qp->Head = qp->Tail = temp;
			qp->QueueLength++;
		}
		else
		{
			for (int i = 0; i < qp->QueueLength; i++)
			{
				if ((temp->priority < tempOne->priority && tempOne->Next != NULL && temp->priority > tempOne->Next->priority)
					|| (temp->priority == tempOne->priority))
				{
					Node *Ins = tempOne->Next, *PrevIns = Ins->Prev;

					if (PrevIns != NULL && qp->QueueLength != 1)
						PrevIns->Next = temp;

					temp->Next = Ins;
					temp->Prev = PrevIns;
					Ins->Prev = temp;

					qp->QueueLength++;

					return;
				}

				if (temp->priority < tempOne->priority && tempOne->Next == NULL)
				{
					temp->Next = NULL;
					temp->Prev = qp->Tail;

					qp->Tail->Next = temp;
					qp->Tail = temp;

					qp->QueueLength++;

					return;
				}

				if (temp->priority > tempOne->priority && tempOne->Prev == NULL)
				{
					temp->Next = qp->Head;

					qp->Head->Prev = temp;
					qp->Head = temp;

					qp->QueueLength++;

					return;
				}

				tempOne = tempOne->Next;
			}
		}
	}
	else
	{
		Node *temp = qp->Tail;

		if (priority > temp->priority)
		{
			qp->Tail = qp->Tail->Prev;
			qp->Tail->Next = NULL;

			free(temp->message);
			free(temp);

			qp->QueueLength--;

			Add(message, priority);
		}
	}
}

void Extract()
{
	while (!IsEmpty())
	{
		Node *temp = qp->Head;

		printf("%i => %s\n", temp->priority, temp->message);

		qp->Head = qp->Head->Next;

		free(temp->message);
		free(temp);

		qp->QueueLength--;
	}
}

int main()
{
	qp = (QueuePriority*)malloc(sizeof(QueuePriority));

	SetMaxLength(12);

	Add("nick", 4);
	Add("maksim", 9);
	Add("pavlo", 5);
	Add("oleg", 2);
	Add("marina", 7);
	Add("sofia", 8);
	Add("victor", 10);
	Add("irina", 1);
	Add("roma", 23);
	Add("sergiy", 13);
	Add("new digit", -2);
	Add("hello, world", 5);
	Add("inserted digit", 27);

	Extract();

	return 0;
}