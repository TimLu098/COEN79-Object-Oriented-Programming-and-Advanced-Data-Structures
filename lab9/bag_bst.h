/*  Yen-Jung Lu
    COEN79 LAB9 - bag_bst.h
    06/03/2022
*/

#ifndef COEN79_BST_BAG
#define COEN79_BST_BAG

#include <cstdlib>     // Provides NULL and size_t
#include "bintree.h"   // Provides binary_tree_node and related functions

namespace coen79_lab9
{
    template <class Item>
    class bag
    {
    public:
        // TYPEDEFS
        typedef std::size_t size_type;
        typedef Item value_type;

        // CONSTRUCTORS and DESTRUCTOR
        bag( ) { root_ptr = NULL; }
        bag(const bag& source);
        ~bag( );

        // MODIFICATION functions
        size_type erase(const Item& target);
        bool erase_one(const Item& target);
        void insert(const Item& entry);
        void operator +=(const bag& addend);
        void operator =(const bag& source);

        // CONSTANT functions
        size_type size( ) const;
        size_type count(const Item& target) const;
        void debug( ) const { print(root_ptr, 0); }

    private:
        binary_tree_node<Item> *root_ptr; // Root pointer of binary search tree
        void insert_all(binary_tree_node<Item>* addroot_ptr);
    };

    // NONMEMBER functions for the bag<Item> template class
    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2);
}



// -----------------------------
// *** IMPLEMENTATION ***
// -----------------------------

namespace coen79_lab9
{

#pragma mark - Toolkit Function Implementation


    // ---------------------------------
    // Toolkit functions for implementing bag class using BST
    // Note: These are not functions of the bag class
    // ---------------------------------

    template <class Item>
    void bst_remove_max(binary_tree_node<Item>*& root_ptr, Item& removed)
    // Precondition: root_ptr is a root pointer of a non-empty binary
    // search tree.
    // Postcondition: The largest item in the binary search tree has been
    // removed, and root_ptr now points to the root of the new (smaller)
    // binary search tree. The reference parameter, removed, has been set
    // to a copy of the removed item.
    {
        binary_tree_node<Item> *oldroot_ptr;

        assert(root_ptr != NULL);

        if (root_ptr->right( ) != NULL)
            bst_remove_max(root_ptr->right( ), removed);
        else
        {
            // STUDENT WORK
            removed = root_ptr->data();
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->left();
            delete oldroot_ptr;
        }
    }


    template <class Item>
    bool bst_remove(binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: If target was in the tree, then one copy of target
    // has been removed, and root_ptr now points to the root of the new
    // (smaller) binary search tree. In this case the function returns true.
    // If target was not in the tree, then the tree is unchanged (and the
    // function returns false).
    {
        binary_tree_node<Item> *oldroot_ptr;

        if (root_ptr == NULL)
        {   // Empty tree
            return false;
        }

        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree

            // STUDENT WORK
            return bst_remove(root_ptr->left(), target);

        }

        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree

            // STUDENT WORK
            return bst_remove(root_ptr->right(), target);
        }

        // Target found
        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.

            // STUDENT WORK
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;

            return true;
        }

        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item of left subtree.

        // STUDENT WORK
        bst_remove_max(root_ptr->left(),root_ptr->data());
        return true;
    }


    template <class Item>
    typename bag<Item>::size_type bst_remove_all (binary_tree_node<Item>*& root_ptr, const Item& target)
    // Precondition: root_ptr is a root pointer of a binary search tree
    // or may be NULL for an empty tree).
    // Postcondition: All copies of target have been removed from the tree
    // and root_ptr now points to the root of the new
    // (smaller) binary search tree. The return value tells how many copies
    // of the target were removed.
    {
        binary_tree_node<Item> *oldroot_ptr;

        if (root_ptr == NULL)
        {   // Empty tree
            return 0;
        }

        if (target < root_ptr->data( ))
        {   // Continue looking in the left subtree

            // STUDENT WORK
            return bst_remove_all(root_ptr->left(), target);
        }

        if (target > root_ptr->data( ))
        {   // Continue looking in the right subtree

            // STUDENT WORK
            return bst_remove_all(root_ptr->right(), target);
        }

        if (root_ptr->left( ) == NULL)
        {   // Target was found and there is no left subtree, so we can
            // remove this node, making the right child be the new root.

            // STUDENT WORK
            oldroot_ptr = root_ptr;
            root_ptr = root_ptr->right();
            delete oldroot_ptr;
            return 1;
        }

        // If code reaches this point, then we must remove the target from
        // the current node. We'll actually replace this target with the
        // maximum item in our left subtree. We then continue
        // searching for more copies of the target to remove.
        // This continued search must start at the current root (since
        // the maximum element that we moved up from our left subtree
        // might also be a copy of the target).

        // STUDENT WORK
        bst_remove_max(root_ptr->left( ), root_ptr->data());

        return 1 + bst_remove_all(root_ptr, target);
    }


#pragma mark - Member Function Implementation


    // ---------------------------------
    // Member functions of the bag class
    // ---------------------------------


    // NOTE: The copy constructor needs to make a new copy of the source’s
    // tree, and point root_ptr to the root of this copy
    // Use the tree_copy function to do the copying
    template <class Item>
    bag<Item>::bag(const bag<Item>& source)
    // Library facilities used: bintree.h
    {
        // STUDENT WORK
        root_ptr = tree_copy(source.root_ptr);
    }



    template <class Item>
    bag<Item>::~bag( )
    // Header file used: bintree.h
    {
        tree_clear(root_ptr);
    }


    template <class Item>
    typename bag<Item>::size_type bag<Item>::size( ) const
    // Header file used: bintree.h
    {
        return tree_size(root_ptr);
    }


    // Insert
    // Case 1: First handle this special case: When the first entry is inserted,
    //         simply call root_ptr = new binary_tree_node<Item>(entry)
    // Case 2: There are already some other entries in the tree:
    //    • We pretend to search for the exact entry that we are trying to insert
    //    • We stop the search just before the cursor falls off the bottom of the tree,
    //      and we insert the new entry at the spot where the cursor was about to fall off
    template <class Item>
    void bag<Item>::insert(const Item& entry)
    // Header file used: bintree.h
    {
        binary_tree_node<Item> *cursor = root_ptr;
        bool done = false;

        if (root_ptr == NULL)
        {
            root_ptr = new binary_tree_node<Item>(entry);
            return;
        }

        do
        {
            if (cursor->data() >= entry)
            {   // Go left

                // STUDENT WORK

                if(cursor->left() == NULL)
                {
                  cursor->set_left(new binary_tree_node<Item>(entry));
                  done = true;
                }
                cursor = cursor->left();
            }
            else
            {   // Go right

                // STUDENT WORK
                if(cursor->right() == NULL)
                {
                  cursor->set_right(new binary_tree_node<Item>(entry));
                  done = true;
                }
                cursor = cursor->right();

            }
        }   while (!done);
    }


    template <class Item>
    typename bag<Item>::size_type bag<Item>::count(const Item& target) const
    {
        size_type answer = 0;
        binary_tree_node<Item> *cursor = root_ptr;

        while (cursor != NULL)
        {
            if (cursor->data() < target)
                // Go right.
                cursor = cursor->right();
            else
            {
                // STUDENT WORK
                if(cursor->data() == target)
                {
                  answer ++;

                }
                cursor = cursor->left();
            }
        }
        return answer;
    }


    template <class Item>
    typename bag<Item>::size_type bag<Item>::erase(const Item& target)
    {
        return bst_remove_all(root_ptr, target);
    }


    template <class Item>
    bool bag<Item>::erase_one(const Item& target)
    {
        return bst_remove(root_ptr, target);
    }


    // The assignment operator:
    // 1. First check if it is a self-assignment by comparing (this == &source): If yes, then return
    // 2. If there is no self-assignment, then before we copy the source tree we must release all
    //    memory used by the nodes of the current tree
    //    Use tree_clear to release memory
    template <class Item>
    void bag<Item>::operator =(const bag<Item>& source)
    // Header file used: bintree.h
    {
        // STUDENT WORK
        root_ptr = tree_copy(source.root_ptr);

    }


    template <class Item>
    void bag<Item>::operator +=(const bag<Item>& addend)
    {
        if (root_ptr == addend.root_ptr)
        {
            // STUDENT WORK
            bag<Item> copy = addend;
            insert_all(copy.root_ptr);
        }
        else
            insert_all(addend.root_ptr);
    }


    template <class Item>
    bag<Item> operator +(const bag<Item>& b1, const bag<Item>& b2)
    {
        // STUDENT WORK
        bag<Item> combined;
        combined += b1;
        combined += b2;

        return combined;
    }


    template <class Item>
    void bag<Item>::insert_all(binary_tree_node<Item>* addroot_ptr)
    // Precondition: addroot_ptr is the root pointer of a binary search tree that
    // is separate for the binary search tree of the bag that activated this
    // method.
    // Postcondition: All the items from the addroot_ptr's binary search tree
    // have been added to the binary search tree of the bag that activated this
    // method.
    {
        if (addroot_ptr != NULL)
        {
            // STUDENT WORK
            insert(addroot_ptr->data());
            insert_all(addroot_ptr->left());
            insert_all(addroot_ptr->right());
        }
    }

}

#endif