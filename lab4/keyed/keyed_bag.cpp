/* Yen-Jung Lu
   COEN79 LAB4- keyed_bag.cpp
   04/29/2021
*/

#include "keyed_bag.h"
#include <assert.h>


using namespace coen79_lab4;

namespace coen79_lab4{
    
    //The keyed_bag has been initialized as an empty keyed_bag.
    keyed_bag::keyed_bag(){
        used=0;
        for (int i=0; i<keyed_bag::CAPACITY; i++) {
            keys[i]= ' ';
            data[i]= 0;
        }
    }

    //This keyed_bag is emptied of all items and keys.
    void keyed_bag::erase(){
        for(int i=0;i<used;i++){
            keys[i] = ' ';
            data[i] = 0;
        }
        used=0;
    }
    
    // If key was in the keyed_bag, then the key and its value have been removed;
    // otherwise the keyed_bag is unchanged. A true return value indicates that an
    // item was removed; false indicates that nothing was removed
    bool keyed_bag::erase(const key_type& key){
        if(has_key(key)){
            for(int i=0; i<used; i++){
                if(keys[i] == key){
                    for (int j=i; j<used-1; j++) {
                        keys[j] = keys[j+1];
                        data[j] = data[j+1];
                    }
                    used--;
                    return true;
                }
            }
        }
        return false;
    }

    //A new copy of entry has been added to the keyed_bag with the corresponding key.
    void keyed_bag::insert(const value_type& entry, const key_type& key){
        assert(size() < CAPACITY);
        if (has_key(key)==false) {
            data[used] = entry;
            keys[used] = key;
            used++;
        }
       
    }

    //Each item and its key in addend has been added to this keyed_bag.
    void keyed_bag::operator +=(const keyed_bag& addend){
        assert(used + addend.used < CAPACITY);
        std::copy(addend.data, addend.data + addend.used, data + used);
        std::copy(addend.keys, addend.keys + addend.used, keys + used);
        used += addend.used;

    }

    //The return value is whether or not the given key is in the keyed_bag's list of keys.
    bool keyed_bag::has_key(const key_type& key) const{
     
        for (int i = 0; i<used; i++) {
                if (keys[i]==key) {
                    return true;
              }
        }
        
        return false;
    }

    //the data value corresponding to the given key is returned.
    keyed_bag::value_type keyed_bag::get(const key_type& key) const{
        assert(has_key(key)==true);
        for(int i = 0; i<used; i++) {
            if (keys[i]==key) {
                return data[i];
            }
            
        }
        return 0;
    }
    
    //The return value is the total number of items in the keyed_bag.
    keyed_bag::size_type keyed_bag::size() const{
        return used;
    }
    
    //The return value is number of times target is in the keyed_bag.
    keyed_bag::size_type keyed_bag::count(const value_type& target) const{
        int count = 0;
        for (int i = 0; i<used; i++) {
            if (data[i]==target) {
                count++;
            }
        }
        return count;
    
    };
    
    //The return value is true if there is at least one key used by both this
    // bag and the "otherBag". In other words, this function checks if there is 
    // any shared key by the two bags.
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const{
        bool dup = false;
        for (int i = 0; i<used; i++) {
            for (int j = 0; j<used; j++) {
                if (keys[i] ==otherBag.keys[j]) {
                    dup = true;
                }
            }
        }
        return dup;

    }
    

    // NONMEMBER FUNCTIONS for the keyed_bag class
    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2){
        
        keyed_bag tot;
        assert(b1.size() + b2.size() < keyed_bag::CAPACITY);
        tot += b1;
        tot += b2;
        return tot;
    
    }
}
