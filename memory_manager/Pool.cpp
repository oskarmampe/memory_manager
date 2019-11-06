//#include "Pool.h"
//
//template <class T>
//Pool<T>::Pool(U32 no_of_elements)
//{
//	base_pointer = new T[no_of_elements];
//	size = no_of_elements;
//	initialise_linked_list();
//}
//
//
//
//template <class T>
//T* Pool<T>::alloc()
//{
//	//return the next free pointer
//	unsigned char* result = head->data;
//	head = head->next;
//
//	return result;
//
//}
//
//template <class T>
//void Pool<T>::free(T* pointer)
//{
//	// Create a node and add it to the linked list.
//	delete pointer;
//	Node* temp = new Node{ pointer, head };
//	head = temp;
//}
//
//template <class T>
//void Pool<T>::clear()
//{
//	delete[] base_pointer;
//	initialise_linked_list();
//}
//
//template <class T>
//void Pool<T>::initialise_linked_list()
//{
//
//	Node* curr = new Node;
//	for (U32 i = 0; i < size; ++i)
//	{
//
//		Node* temp = new Node;
//		temp->data = base_pointer + i;
//		temp->next = NULL;
//		if (head == NULL)
//		{
//			head = temp;
//			curr = temp;
//		}
//		else
//		{
//			curr->next = temp;
//			curr = temp;
//		}
//	}
//}