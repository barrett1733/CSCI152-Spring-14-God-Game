/*

This code is based off of the Java source code found here:

	http://www.keithschwarz.com/interesting/code/?dir=fibonacci-heap

I utilized this source as a learning tool and a reference in emplementing the
Fibonacci Heap, which will be used in the Dijkstra's Shortest Path Algorithm 
as a means of achieving optimal speed and efficiency.

The code in this file was not cut and pasted, but mimics the source code it's 
based on. I did this to ensure my understanding of the algorithm and methods 
used to create it, while also decreasing the frequency of bugs and mistakes
due to the fact that I am learning this for the first time.

-Anthony Smith (Feb. 2014)

*/


/*

TODO: Generalize class and functions.
TODO: May need to implement a check priority exception
TODO: Include proper exceptions. dequeMin, checkPriority, etc.

*/
#include <stdlib.h>
#include <iostream>

using namespace std;


class fHeap{

private:
	class Node{
		
	public:
		int priority; //the lowest value has highest priority
		int item; //the thing being queued


		bool isMarked = false; //did node lose child?
		int rank; //number of children 

		Node* parent;
		Node* child;

		//siblings
		Node* next;
		Node* prev;

		Node(int newItem, int newPriority){

			item = newItem;
			priority = newPriority;
			prev = next = this;

		}
        
		//I may need to adjust the scope of these classes and members.
		void setitem(int k) { item = k; }
		int getitem() { return item; }
		int getPriority() { return priority; }

		void printItem(){ std::cout << item << "\n"; }

	};

	Node* min = NULL; //min key in heap

	int size = 0; //size of heap

	//merges the doubly linked lists. Used in mergeTree function.
	Node* mergeLists(Node* one, Node* two){
		
		if (one == NULL && two == NULL)
			return NULL;

		else if (one != NULL && two == NULL)
			return one;

		else if (one == NULL && two != NULL)
			return two;

		else {
		
			Node* temp = one->next;
			one->next = two->next;
			one->next->prev = one;
			two->next = temp;
			two->next->prev = two;

		}

		//return the highest priority pointer (the min) to maintain min heap property
		return one->priority < two->priority ? one : two;

	}
	
	/*
	removes node from it's subtree and makes it its own tree in the root list
	also calls merge and recursively takes care of all marked parents and grandparents
	*/
	void cutNode(Node* target){
	
		target->isMarked = false;

		if (target->parent == NULL)
			return;

		if (target->next != target){

			//adjusts the list that target was removed from, maintaing the CLL. 
			//Target's next and prev will be fixed in the merge function.
			target->next->prev = target->prev;
			target->prev->next = target->next;

		}

		if (target->parent->child == target){
			
			if (target->next != target)					//if target has siblings
				target->parent->child = target->next;   //point its parent at one(any) of them
			else
				target->parent->child = NULL;
		
		}

		--target->parent->rank;

		//make target its own tree and merge it with the root list
		target->next = target;
		target->prev = target;
		min = mergeLists(min, target);

		if (target->parent->isMarked)
			cutNode(target->parent);
		else
			target->parent->isMarked = true;

		target->parent = NULL;
	
	}
	
	//changes a nodes priority when the node's key changes
	void decreaseKey(Node* target, int newPriority){
	
		target->priority = newPriority;

		if (target->parent != NULL && target->priority <= target->parent->priority)
			cutNode(target);

		if (target->priority <= min->priority)
			min = target;
	}


public:

	fHeap(){}

	Node* getMin() { return min; }

	bool isEmpty(){ return min == NULL; } 

	int getSize() { return size; }

	//enqueue returns a reference to the newly insterted node
	Node* enqueue(int newItem, int priority){
		//may need to check priority here

		Node* result = new Node(newItem, priority);

		min = mergeLists(min, result);

		++size;

		return result;

	}

	//combines two fHeaps, but we may not use this
	fHeap* merge(fHeap* one, fHeap* two){
	
		fHeap* result = new fHeap();

		result->min = mergeLists(one->min, two->min);
		
		result->size = one->size + two->size;

		one->size = two->size = 0;
		one->min = NULL;
		two->min = NULL;
	
	}

	Node* dequeueMin(){

		//Temporary, until I figure out exceptions
		if (isEmpty){
			cout << "error! Queue is empty.";
			return NULL;
		}

		--size;

		Node* minElement = min;

		if (min->next == min)
			min = NULL;
		else{

			min->prev->next = min->next;
			min->next->prev = min->prev;
			min = min->next;

		}

		if (minElement->child != NULL){
		
			Node* current = minElement->child;

			do{
				
				current->parent = NULL;

				current = current->next;

			} while (current != minElement->child);

		}
	
		min = mergeLists(min, minElement->child);

		if (min == NULL)
			return minElement;
	
		
	
	}


	



};