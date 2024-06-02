/*  Yen-Jung Lu

    COEN79 LAB3 - sequence1.h

    04/22/2022

*/ 

#ifndef COEN79_SEQUENCE1_H
#define COEN79_SEQUENCE1_H

#include <iostream>

namespace coen79_lab3 {
    
class sequence {
    
    
        
    public:
        sequence();
        // TYPEDEF and MEMBER CONSTANTS
        typedef double value_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 50;
    
        void start();
        void end();
        void last();
        value_type current() const;
        void advance();
        void retreat();

        
        void insert(const value_type& entry);
        void attach(const value_type& entry);
        void remove_current();
        void insert_front(const value_type& entry);
        void attach_back(const value_type& entry);
        void remove_front();
        
        void operator +=(const sequence& rhs);
        
        
        size_type size() const;
        bool is_item( ) const;

        

        value_type operator[](int index) const;
        
        
        value_type mean() const;
		value_type standardDeviation() const;
        
        
        private:
            value_type data[CAPACITY];
            size_type used;
            size_type current_index;
        
        
        
    };
       sequence::value_type summation(sequence &seq);
       sequence operator +(const sequence& lhs, const sequence& rhs);

}

#endif
