#include <stdlib.h>
#include <iostream>
#include "directed_graph.h"
#include <initializer_list> 


int main( int argc , char * argv [] )
{
    vertex v1('1',1);
    vertex v2('2',2);
    vertex v3('3',3);
    vertex v4('4',4);
    vertex v5('5',5);
    vertex v6('6',6);
    vertex v7('7',7);
    vertex v8('8',8);
    vertex v9('9',9);
    
    std::pair<vertex,vertex> a1(v1,v2);
    std::pair<vertex,vertex> a2(v1,v8);
    std::pair<vertex,vertex> a3(v2,v8); 
    std::pair<vertex,vertex> a4(v2,v3);
    std::pair<vertex,vertex> a5(v3,v6);
    std::pair<vertex,vertex> a6(v4,v3);
    std::pair<vertex,vertex> a7(v4,v5);
    std::pair<vertex,vertex> a8(v5,v6);
    std::pair<vertex,vertex> a9(v9,v8);

    auto vertices {v1,v2,v3,v4,v5,v6,v7,v8,v9};
    auto arcs {a1,a2,a3,a4,a5,a6,a7,a8,a9};
    
    directed_graph d(vertices,arcs);

    d.display();
     
    d.topological_sorting();
    return EXIT_SUCCESS;
}



	
