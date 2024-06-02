/*  Yen-Jung Lu

    COEN79 - LAB6 - node.cpp

    05/13/2022

*/

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{ 

  //The value returned is the number of nodes in the linked list.
  size_t list_length(const node* head_ptr)
  {
    const node *cursor;
    size_t answer;
        
    answer = 0;
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
      ++answer;
        
    return answer;
  }


  //A new node containing the given entry has been added at the head of the linked list
  void list_head_insert(node*& head_ptr, const node::value_type& entry)
  {
    head_ptr = new node(entry, head_ptr);
  }

  //A new node containing the given entry has been added after the node that previous_ptr points to
  void list_insert(node* previous_ptr, const node::value_type& entry)
  {
    node *insert_ptr;
        
    insert_ptr = new node(entry, previous_ptr->link( ));
    previous_ptr->set_link(insert_ptr);
  }


  // The pointer returned points to the first node containing the specified target in its data member
  node* list_search(node* head_ptr, const node::value_type& target)
  {
    node *cursor;
        
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
      if (target == cursor->data( ))
	    return cursor;
        
      return NULL;
  }
    
  const node* list_search(const node* head_ptr, const node::value_type& target)
  {
    const node *cursor;
        
    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
      if (target == cursor->data( ))
	    return cursor;
        
      return NULL;
  }
  
  
  //The pointer returned points to the node at the specified position in the list  
  node* list_locate(node* head_ptr, size_t position)
  {
    node *cursor;
    size_t i;
        
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
      cursor = cursor->link( );
        
      return cursor;
  }
    
  const node* list_locate(const node* head_ptr, size_t position)
  {
    const node *cursor;
    size_t i;
        
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
      cursor = cursor->link( );
        
    return cursor;
  }

  //The head node has been removed and returned to the heap;
  // head_ptr is now the head pointer of the new, shorter linked list 
  void list_head_remove(node*& head_ptr)
  {
    node *remove_ptr;
        
    remove_ptr = head_ptr;
    head_ptr = head_ptr->link( );
    delete remove_ptr;
  }

  //The node after previous_ptr has been removed from the linked list
  void list_remove(node* previous_ptr)
  {
    node *remove_ptr;
        
    remove_ptr = previous_ptr->link( );
    previous_ptr->set_link( remove_ptr->link( ) );
    delete remove_ptr;
  }
  
  // All nodes of the list have been returned to the heap and the heap_ptr is now NULL
  void list_clear(node*& head_ptr)
  {
    while (head_ptr != NULL)
      list_head_remove(head_ptr);
  }

  void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
  {
    head_ptr = NULL;
    tail_ptr = NULL;
        
    if (source_ptr == NULL)
      return;
        
    // Make the head node for the newly created list, and put data in it.
    list_head_insert(head_ptr, source_ptr->data( ));
    tail_ptr = head_ptr;
        
    // Copy the rest of the nodes one at a time, adding at the tail of new list.
    source_ptr = source_ptr->link( );
    while (source_ptr != NULL)
      {
	      list_insert(tail_ptr, source_ptr->data( ));
	      tail_ptr = tail_ptr->link( );
	      source_ptr = source_ptr->link( );
      }
  }

  //head_ptr and tail_ptr are the head and tail pointers for a new list that contains 
  // the items from start_ptr up to but not including end_ptr.
  void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr){
    head_ptr = NULL;
    tail_ptr = NULL;
        
    if(start_ptr == end_ptr || start_ptr == NULL){
      return;
    }
        
    list_head_insert(head_ptr, start_ptr -> data());
    tail_ptr = head_ptr;
            
    while(start_ptr -> link() != end_ptr){
      start_ptr = start_ptr -> link();
      list_insert(tail_ptr, start_ptr->data());
      tail_ptr = tail_ptr -> link();
    }
  }
  
  //The return value is the count of the number of times target appears as the data portion of a node on the linked list
  size_t list_occurrences(node* head_ptr, const node::value_type& target){
    node* temp = head_ptr;
    size_t count = 0;
        
    if(head_ptr == NULL)
      return count;
        
    while(temp !=  NULL){
      if(temp->data() == target)
	      count++;
        temp = temp->link();
    }
        
    return count;
        
  }

  //A new node has been added to the linked list with entry as the data. 
  // The new node occurs at the specified position in the list
  void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position){
    assert(position > 0 && position <= list_length(head_ptr) + 1);
        
    if (position == 1)
      list_head_insert(head_ptr, entry);
    else if (position == list_length(head_ptr) + 1)
      list_insert(list_locate(head_ptr, list_length(head_ptr)), entry);
    else
      list_insert(list_locate(head_ptr, position - 1), entry);
  }


  //The node at the specified position has been removed from the linked list 
  // and the function has returned a copy of the data from the removed node. 
  node::value_type list_remove_at(node*& head_ptr, size_t position){
    assert(position > 0 && position <= list_length(head_ptr));
        
    node::value_type temp = list_locate(head_ptr, position) -> data();

    if(position == 1){
      node::value_type temp = head_ptr -> data();
      list_head_remove(head_ptr);
      return temp;
    }
    else{
      list_remove(list_locate(head_ptr, position - 1));
      return temp;
    }
  }
 
  node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
    assert((1 <= start) && (start <= finish) && (finish <= list_length(head_ptr)));
    if(head_ptr == NULL){
      return NULL;
    }
    node* newHead = NULL;
    node* newTail = NULL;
    node* startNode = list_locate(head_ptr, start);
    node* endNode = list_locate(head_ptr, finish + 1);//idk why there's a "+1" but it works lol
    list_piece(startNode, endNode, newHead, newTail);
    return newHead;
  }
    
  void list_print(const node* head_ptr){
    if(head_ptr == NULL){
      cout << endl;
      return;
    }
    while(head_ptr->link() != NULL){
      cout << head_ptr->data() << ", ";
      head_ptr = head_ptr->link();
    }
    cout << head_ptr->data() << endl;
    return;
  }

  //All the duplicates are removed from the linked list  
  void list_remove_dups(node* head_ptr){
    if(head_ptr == NULL){
      return;
    }
    node* ptr1;
    node* ptr2;
    node* dup;
    ptr1 = head_ptr;
    while(ptr1 != NULL && ptr1->link() != NULL){
      ptr2 = ptr1;
      while(ptr2->link() != NULL){
	      if(ptr1->data() == ptr2->link()->data()){
	        dup = ptr2->link();
	        ptr2->set_link(ptr2->link()->link());
	        delete(dup);
	      }
	      else{
	        ptr2 = ptr2->link();
	      }
	    ptr1 = ptr1->link();
      }
    }
    return;
  }
  // If there is a loop in the linked list, the returned value is a pointer to the start of the loop
  node* list_detect_loop (node* head_ptr){
    if(head_ptr == NULL){
      return NULL;
    }
    node* fast_run = head_ptr;
    node* slow_run = head_ptr;
    while((fast_run != NULL) && (fast_run->link() != NULL)){
      slow_run = slow_run->link();
      fast_run = fast_run->link()->link();
      if(slow_run == fast_run){
	      break;
      }
    }
    if((fast_run == NULL) || (fast_run->link() == NULL)){
      return NULL;
    }
    slow_run = head_ptr;
    while(slow_run != fast_run){
      slow_run = slow_run->link();
      fast_run = fast_run->link();
    }
    cout << "the pointers met!" << endl;
    return slow_run;
  }
    
}