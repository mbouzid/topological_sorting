#include "arc.hpp"

template <typename W> unsigned int arc<W>::s_label = 0 ;

template <typename W>
std::ostream & operator <<( std::ostream & os , const arc<W> & _ ) 
{
    return os << "(" << _.get_in() << "," << _.get_out() << "," << _.get_weight() << ")" ;
};

template typename std::ostream & operator << <int>( std::ostream & os , const arc<int> & _ ) ;
template class arc<int> ;
