#pragma once 

#include <iostream>
#include <sstream>
class vertex
{
    
    private :
        
        char m_symbol;
        unsigned int m_label ;
        
    public :
        
        vertex( char symbol , unsigned int label ):m_symbol(symbol),m_label(label)
        /**
        *   Constructor.
        *   @constructor @access public
        *   @param {int} label - the label of the vertex
        **/{}
    
        vertex( const vertex & _ ):m_symbol(_.m_symbol),m_label(_.m_label)
        /**
        *   Copy constructor.
        *   @constructor @access public
        *   @param {const vertex &} _ - a vertex to copy
        **/
        {}


        ~vertex()
        /**
        *   Destructor.
        *   @destructor @access public
        **/{}

        bool operator < ( const vertex & _ ) const
        /**
        *   Overloaded comparision method.
        *   @method @access public @readonly
        *   @param {const vertex &} _ - a vertex
        *   @return {bool} - 
        **/
        {
            return (m_label<_.m_label);
        }

        bool operator ==( const vertex & _ ) const
        /**
        *   Overloaded equality operator.
        *   @method @access public @readonly
        *   @param {const vertex &} _ - a vertex
        *   @return {bool}
        **/
        {
            return (m_label==_.m_label);
        }

        char get_symbol() const
        /**
        *   Symbol getter.
        *   @method @access public @readonly
        *   @return {char}
        **/
        {
            return m_symbol;
        }            
        
};

std::ostream & operator << ( std::ostream & os , const vertex & _ );
