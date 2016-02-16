#pragma once

#include "vertex.hpp"

template <class W>
class arc
{
    private :

        /**
        *   An arc is established between two vertices. 
        *   @member {std::pair<vertex,vertex>} m_pair - the vertices linked
        *   @member {W} m_weight - the weight between the vertices
        *   @member {unsigned int} m_label - an extra information in order to distinguish arcs.
        *   @static {unsigned int} s_label 
        **/
        
        std::pair<vertex,vertex> m_pair ;
        W m_weight ;
        static unsigned int s_label ;
        unsigned int m_label ;

    public :
        
        arc( const vertex & in , const vertex & out , const W & weight ):m_pair(std::make_pair(in,out)),m_weight(weight),m_label(++s_label)
        /**
        *   Constructor
        *   @constructor @access public
        *   @param {const vertex &} in - the in vertex
        *   @param {const vertex &} out - the out vertex
        *   @param {const W &} weight - the weight between the vertices
        **/
        {}
        arc( const arc & _ ):m_pair(_.m_pair),m_weight(_.m_weight),m_label(_.m_label)
        /**
        *   Copy constructor
        *   @constructor @access public
        *   @param {const arc &} _ - the arc to copy
        **/
        {}

        ~arc()
        /**
        *   Destructor
        *   @destructor @access public
        **/
        {}

        vertex get_in() const
        /**
        *   In vertex getter.
        *   @method @access public @readonly
        *   @return {vertex}
        **/
        {
            return m_pair.first;
        }
        
        vertex get_out() const
        /**
        *   Out vertex getter.
        *   @method @access public @readonly
        *   @return {vertex}
        **/
        {
            return m_pair.second;
        }
        
        const W & get_weight() const
        /**
        *   Weight getter.
        *   @method @access public @readonly 
        *   @return {const W &}
        **/
        {
            return m_weight;
        }            
 
        bool operator <( const arc & _ ) const
        /**
        *   Overloaded comparision operator.
        *   @method @access public @readonly 
        *   @param {const arc &} _ - an arc
        *   @return {bool}
        **/
        {
            return m_label<_.m_label ;  
        }  
};      

template <typename W>
std::ostream & operator <<( std::ostream & os , const arc<W> & _ ) ;