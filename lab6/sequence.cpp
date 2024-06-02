/*  Yen-Jung Lu

    COEN79 - LAB6 sequence.cpp

    05/13/2022

*/

#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; 

namespace coen79_lab6
{
  // Default private member variable initialization function.
  void sequence::init()
  {
    //Initializing pointers to NULL
    head_ptr = NULL;
    tail_ptr = NULL;
    cursor = NULL;
    precursor = NULL;
    //Initializiing many_nodes (or our counter) to 0
    many_nodes = 0;
  }

  //CONSTRUCTOR IMPLEMENTATION for default constructor

  //The sequence has been initialized as an empty sequence.
  sequence :: sequence ()
  {
    init();
  }

  //Copy Constructor
  sequence::sequence(const sequence& source)
  {
    init();
    *this = source;
  }
    
  sequence::~sequence(){
    list_clear(head_ptr);
    many_nodes = 0;
  }
    
  //MODIFICATION MEMBER FUNCTIONS

  //The precursor and cursor are adjusted such that the first
  //item in the sequence becomes the current item 
  void sequence::start(){
    precursor = head_ptr;
    cursor = head_ptr;
    return;
  }
  
  //The precursor and cursor are adjusted such that the last
  // item in the sequence becomes the current item
  void sequence::end(){
    cursor = tail_ptr;
    if(head_ptr == tail_ptr){
      precursor = NULL;
    }
    else{
      precursor = head_ptr;
      while(precursor->link() != cursor){
	      precursor = precursor->link();
      }
    }
    return;
  }


//If the current item was already the last item in the sequence, then 
// there is no longer any current item. Otherwise, the new current item 
// is the item immediately after the original current item.
  void sequence::advance(){
    assert(is_item());
        
    if(cursor == tail_ptr){
      cursor = NULL;
      return;
    }
        
    precursor = cursor;
    cursor = cursor->link();
    return;
  }
  

//A new copy of entry has been inserted in the sequence before the current item. 
// If there was no current item, then the new entry has been inserted at the front
// of the sequence. 
  void sequence::insert(const value_type& entry){
    if(head_ptr == NULL){//list is empty
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = head_ptr;
    }
    else if(is_item() && cursor == head_ptr){//cursor @ head
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
    }
    else if(is_item() && cursor != head_ptr){//somewhere in middle or end
      list_insert(precursor, entry);
      cursor = precursor -> link();
    }
    else if(!is_item()){//cursor is NULL
      list_head_insert(head_ptr, entry);
      tail_ptr = precursor->link();
      cursor = head_ptr;
      precursor = NULL;
    }
    many_nodes++;
    return;
  }
    


//A new copy of entry has been inserted in the sequence after the current item. 
// If there was no current item, then the new entry has been attached to the end 
// of the sequence. 
  void sequence::attach(const value_type& entry){
    if(head_ptr == NULL){//empty list
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = head_ptr;
    }
    else if(is_item() && many_nodes == 1){//head = tail
      list_insert(head_ptr, entry);
      precursor = head_ptr;
      tail_ptr = precursor->link();
      cursor = tail_ptr;
    }
    else if(is_item() && many_nodes > 1 && cursor == head_ptr){//cursor @ head, but list > 1
      list_insert(head_ptr, entry);
      precursor = head_ptr;
      cursor = precursor->link();
    }
    else if(is_item() && cursor != head_ptr){//somewhere in the middle or tail
      if(cursor != tail_ptr){//middle
	      list_insert(cursor, entry);
	      advance();
      }
      else{//tail
	      list_insert(tail_ptr, entry);
	      tail_ptr = cursor->link();
	      precursor = cursor;
	      cursor = tail_ptr;
      }
    }
    else if(!is_item() && many_nodes > 0){//cursor is null but list isn't empty, add at tail
      list_insert(tail_ptr, entry);
      precursor = tail_ptr;
      cursor = precursor->link();
      tail_ptr = cursor;
    }
    many_nodes++;
    return;
  }
    
  // MODIFICATION MEMBER FUNCTIONS
  void sequence::operator =(const sequence& source){
    if(this == &source){
      return;
    }
    list_clear(head_ptr);
    many_nodes = 0;
    node* tmp_tail;
    list_copy(source.head_ptr, head_ptr,tmp_tail);
    cursor = head_ptr;
    tail_ptr = tmp_tail;
      
    node* tmp = source.head_ptr;
    precursor = head_ptr;
    if(source.cursor == NULL){
      cursor = NULL;
      precursor = tail_ptr;
    }
    else{
      while(tmp != source.precursor){
	      tmp = tmp->link();
	      precursor = precursor->link();
      }
      if(precursor != NULL){
	      cursor = precursor->link();
      }
    }
    many_nodes = source.many_nodes;        
  }
    
  void sequence::remove_current( ){
    assert(is_item());
    if(head_ptr->link() == NULL){//one item in list
      delete cursor;
      head_ptr = NULL;
      tail_ptr = NULL;
      precursor = NULL;
      cursor = NULL;
    }
    else if(cursor == head_ptr && head_ptr ->link() !=NULL){//list isn't empty and cursor @ head
      cursor = head_ptr->link();
      list_head_remove(head_ptr);
      precursor = NULL;
    }
    else if (cursor == tail_ptr && many_nodes > 1){//list isn't empty and cursor @ tail
      tail_ptr = precursor;
      delete cursor;
      cursor = NULL;
      tail_ptr->set_link(NULL);
    }
    else if(cursor != head_ptr && cursor != tail_ptr){//removing from middle
      precursor->set_link(cursor->link());
      delete cursor;
      cursor = precursor->link();
    }
    many_nodes--;
  }
    
  // CONSTANT MEMBER FUNCTIONS
  sequence::size_type sequence::size( ) const{
    return many_nodes;
  }
    
  bool sequence::is_item( ) const{
    if(cursor == NULL){
      return false;
    }
    else{
      return true;
    }
  }
    
  sequence::value_type sequence::current( ) const{
    assert(is_item());
        
    return cursor->data();
        
  }
}