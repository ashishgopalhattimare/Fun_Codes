#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

int hashTable[26];

/**
 * Structure for the Heap tree
 * */
struct Node
{
	char c;
	int freq;
	Node *left, *right;
};

struct CharLoc
{
	string location;
}locArray[26];

/**
 * Structure for the linked list representation
 * */
struct Link
{
	Node *node;
	Link *next;

}*front = NULL,*rear = NULL;

/**
 * Enqueue in the sorted vector into linked list
 * */
void enQueue(Node *x)
{
	Link *temp = new Link;
	temp->node = x;

	if(front == NULL) {
		temp->next = NULL;
		front = temp;
	}
	else {
		rear->next = temp;
	}// end if

	rear = temp;
}

/**
 * reset HashTable for the new string input
 * */
void reset()
{
	for(int i = 0; i < 26; i++) {
		hashTable[i] = 0;
		locArray[i].location = "";
	}
	return;
}

/**
 * HashTable for the Frequency
 * */
void makeHash(const string str)
{
	reset();
	int len = str.length();
	for(int i = 0; i < len; i++) {
		hashTable[str[i]-'a']++ ;
	}
	return;
}

/**
 * Comparactor function for the sort function
 * */
bool compare(const Node& a, const Node& b)
{
	if(a.freq == b.freq) {
		return a.c < b.c;
	}
	return a.freq < b.freq;
}

/**
 * Print Linked List of the Frequency
 * */
void printLink()
{
	Link *p = front;
	while(p) {
		printf("%d ", p->node->freq);
		p = p->next;
	}
	printf("\n");
}

void HeapUtility()
{
	int freq;
	while(front->next != NULL)
	{
		Node *n1 = front->node;
		Node *n2 = front->next->node;
		
		freq = n1->freq + n2->freq;

		Node *newNode = new Node;
		newNode->freq = freq;
		newNode->c = '#';

		// nowNew Node has left and right nodes
		if(n1->freq > n2->freq) {
			newNode->right = n1;
			newNode->left = n2;
		}
		else {
			newNode->right = n2;
			newNode->left = n1;
		}// end if

		// remove the first two link from front
		
		Link *f1 = front;
		Link *f2 = front->next;

		front = f2->next;

		// delete the two links from front link

		if(front == NULL)
		{
			enQueue(newNode);
		}

		else {
			// add the newly formed Link to the linked list

			// Last Append
			if(newNode->freq >= rear->node->freq) {
				Link *newLink = new Link;
				newLink->node = newNode;
				newLink->next = NULL;

				rear->next = newLink;
				rear = newLink;
			}
			
			else if(newNode->freq <= front->node->freq){
				Link *newLink = new Link;
				newLink->node = newNode;
				newLink->next = front;
				
				front = newLink;
			}
			
			// in between
			else {
				Link *ptr = front, *prev = NULL;
				while(ptr) {

					if(newNode->freq <= ptr->node->freq) {
						Link *newLink = new Link;
						newLink->node = newNode;
						
						newLink->next = ptr;
						prev->next = newLink;

						break;
					}// end if
					
					prev = ptr;
					ptr = ptr->next;
				}// end while
			}// end if
		}// end if

		//printLink();
	}// end while
}

/**
 * Print the inorder of the heap tree formed
 * */
void inorder(Node *head)
{
	if(head == NULL) return;

	inorder(head->left);
	printf("(%c,%d) ", head->c, head->freq);
	inorder(head->right);
	
	return;
}

/**
 * Get the Location of all the characters from the heap traverse
 * */
void getLocation(Node *head, string loc)
{
	if(head == NULL) return;

	if(head->left == NULL && head->right == NULL) {
		locArray[head->c - 'a'].location = loc;
		return;
	}

	getLocation(head->left, loc + "0");
	getLocation(head->right, loc + "1");

	return;
}

void decryptHuffman(Node *head, const string decrypt)
{
	if(head == NULL) {
		return;
	}
	
	Node *ptr = head;
	
	int len = decrypt.length();
	for(int i = 0; i < len; i++) {
		if(ptr->left == NULL && ptr->right == NULL) {
			printf("%c", ptr->c);
			
			ptr = head;
		}
		
		if(decrypt[i] == '0') {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}
	
	printf("%c\n", ptr->c);
	
	return;
}

int main()
{
	int arLen;
	string word;

	while(true)
	{
		printf("\nORIGINALY WORD : ");
		cin >> word;

		makeHash(word);

		vector <struct Node> A;
		arLen = 0;

		for(int i = 0; i < 26; i++) {
			if(hashTable[i] > 0) {
				Node *node = new Node;
				node->c = i + 'a';
				node->freq = hashTable[i];
				node->left = node->right = NULL;

				A.push_back(*node);
				arLen++;
			}
		}

		sort(A.begin(), A.end(), compare);

		front = rear = NULL;
		for(int i = 0; i < arLen; i++) {
			enQueue(&A[i]);
		}

		//printLink();
		
		HeapUtility();

		//printf("\n"); inorder(front->node);
		
		getLocation(front->node, "");
		
		/*
		//Print the location of all the characters in the word according
		//to their position in the Heap Tree i.e. 0-left , 1-right
		printf("\n");
		for(int i = 0; i < 26; i++) {
			printf("%c : %s\n", i+'a', locArray[i].location.c_str());
		}
		*/

		string encryptString = "";
		for(int i = 0; i < word.length(); i++) {
			encryptString = encryptString + locArray[word[i]-'a'].location;
		}
		
		printf("ENCRYPTED WORD : ");
		cout << encryptString << endl;
		
		printf("DECRYPTED WORD : ");
		decryptHuffman(front->node, encryptString);
		
		break;
	}

	return 0;
}






