/*  Yen-Jung Lu

    COEN79 -LAB7 company.cpp

    05/20/2022

*/

#include <cassert>
#include "company.h"
#include "node.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }

    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }

    //uses the equal Operator (=) to make a copy of the compoany varaible src
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        *this = src;

    }

    //reassign head_ptr and tail_ptr to point to a list of elements that is a copy of src
    //return the varaible pointer that called this function after assignment
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        if(this ==  &src)
        {
          return *this;
        }

        list_clear(head_ptr);
        tail_ptr = NULL;
        head_ptr = NULL;

        this->company_name = src.get_name();
        list_copy(src.head_ptr, head_ptr, tail_ptr);


        return *this;
    }
       

    company::~company() {
        list_clear(head_ptr);
    }

    // Return the name of the company
    std::string company::get_name() const {
        return company_name;
    }

    //Return the Constant version of the head of linked list 
    const node *company::get_head() const {
        return head_ptr;
    }

    //Return the Constant version of the tail of linked list
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    //Return the non-constant version of the head of linked list
    node* company::get_head() {
        return head_ptr;
    }

    //Return the non-constant version of the tail of linked list
    node* company::get_tail() {
        return tail_ptr;
    }

    // Prints the products of the company
    void company::print_items() {
        list_print(head_ptr);
    }

 
    // If already have a list, insert the product_name and price at the end, if there is no
    // items created yet, then initialize a new list. If the list is existed, then return 
    // true if an item is successfully inserted
    bool company::insert(const std::string& product_name, const float& price) {

        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }

        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(tail_ptr, product_name, price);
        }

        return true;
    }

    //Erases the product that its name matches product_name. Returns true if the
    // product has been found and deleted, returns false otherwise
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        if(head_ptr == NULL)
        {
          return false;
        }

        node *cursor = head_ptr;
        node *cursor2 = cursor->getLink();
        node* deleted = NULL;
        while(cursor->getLink() != NULL)
        {
          if(head_ptr->getName() == product_name)
          {
            list_head_remove(head_ptr);

            return true;
          }
          else
          {
              if(cursor2->getName() == product_name)
              {
                deleted = cursor2;
                cursor->setLink(deleted->getLink());

                delete deleted;

              }

              return true;
          }

          cursor = cursor->getLink();
          cursor2 = cursor->getLink();
        }

        return false;
    }


}