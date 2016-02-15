#include <stdlib.h>
#include <iostream>
#include "directed_graph.hpp"
#include <initializer_list> 


int main( int argc , char * argv [] )
{
    vertex v1('A',1);
    vertex v2('B',2);
    vertex v3('C',3);
    vertex v4('D',4);
    vertex v5('E',5);
    vertex v6('F',6);

    std::pair <vertex,vertex> a1(v1,v2);
    std::pair <vertex,vertex> a2(v1,v4);
    std::pair <vertex,vertex> a3(v2,v3);
    std::pair <vertex,vertex> a4(v3,v4);
    std::pair <vertex,vertex> a5(v4,v5);
    std::pair <vertex,vertex> a6(v3,v5);
    
    directed_graph d({v1,v2,v3,v4,v5,v6},{a1,a2,a3,a4,a5,a6});

    try
    {
        d.display();
     
        directed_graph::topological_sorting(d);
        
        return EXIT_SUCCESS;
    }
    catch (const graph_exception & e )
    {
        std::cout << e.what() << std::endl ;
        
        exit(EXIT_FAILURE);
    }
}



	
