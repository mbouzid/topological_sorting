#include "vertex.h"

std::ostream & operator <<( std::ostream & os , const vertex & _ )
{
    return os << _.get_symbol() ;
}
