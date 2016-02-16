#include "directed_graph.hpp"

unsigned int min_index( std::set<vertex> queue , int dist[] , unsigned int n )
{
	int imin = (*queue.begin()).get_label() ;
	
	for ( auto i = queue.begin() ; i!= queue.end() ; ++i )
	{
		if ( dist[(*i).get_label()] < dist[imin] )
		{
			imin= (*i).get_label();
		}
	}
	return imin;
} 

template class directed_graph<int> ;
