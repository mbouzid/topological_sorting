#pragma once 

#include <iostream>
#include <string>

class vertex
{
    
    private :
        
        std::string m_symbol;
        unsigned int m_label ;
        static unsigned int s_label ;
        
    public :
        
        vertex( const std::string & symbol ):m_symbol(symbol),m_label(s_label++)
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

        std::string get_symbol() const
        /**
        *   Symbol getter.
        *   @method @access public @readonly
        *   @return {std::string}
        **/
        {
            return m_symbol;
        }            

        unsigned int get_label() const
        /**
        *   Label getter.
        *   @method @access public @readonly 
        *   @return {unsigned int}
        **/
        {
            return m_label ;    
        }         
};

std::ostream & operator << ( std::ostream & os , const vertex & _ );
