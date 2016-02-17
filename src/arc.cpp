#include "arc.hpp"

template <typename W> unsigned int arc<W>::s_label = 0 ;

template <typename W>
bool operator < ( const arc<W> & a , const arc<W> & b ) 
{
    return a.get_weight() < b.get_weight();
}

template <typename W>
std::ostream & operator <<( std::ostream & os , const arc<W> & _ ) 
{
    return os << "(" << _.get_in() << "," << _.get_out() << ")" << " weight=" << _.get_weight()  ;
};


bool operator < ( const arc<int> & a , const arc<int> & b );
template typename std::ostream & operator << <int>( std::ostream & os , const arc<int> & _ ) ;
template class arc<int> ;
