#include "vertex.hpp"

unsigned int vertex::s_label = 0 ;

std::ostream & operator <<( std::ostream & os , const vertex & _ )
{
    return os << _.get_symbol() ;
}
