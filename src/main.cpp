#include <stdlib.h>
//std lib
#include <iostream>
#include <initializer_list> 


//own lib
#include "arc.hpp"
#include "directed_graph.hpp"

int main( int argc , char * argv [] )
{
    
    //@see `Wiki` tab in GitHub for the source of this example
    
    vertex v1("début",0);
    vertex v2("A",1);
    vertex v3("B",2);
    vertex v4("C",3);
    vertex v5("D",4);
    vertex v6("E",5);
    vertex v7("F",6);
    vertex v8("G",7);
    vertex v9("H",8);
    vertex v10("I",9);
    vertex v11("J",10);
    vertex v12("fin",11);

    arc<int> a1 (v1,v2,0);    
    arc<int> a2 (v1,v3,0);
    arc<int> a3 (v1,v4,0);
    arc<int> a4 (v1,v5,0);
    arc<int> a5 (v1,v8,0);
    arc<int> a6 (v1,v9,0);
    arc<int> a7(v2,v6,7);
    arc<int> a8(v3,v6,5);
    arc<int> a9(v6,v7,4);
    arc<int> a10(v4,v7,3);
    arc<int> a11(v5,v7,1);
    arc<int> a12(v7,v10,2);
    arc<int> a13(v8,v10,1);
    arc<int> a14(v9,v11,10);
    arc<int> a15(v10,v11,1);
    arc<int> a16(v11,v12,35);
        

    directed_graph<int> d({v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12},{a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16});

    try
    {
        d.display();
     
        directed_graph<int>::topological_sorting(d);
       
        d.display();
 
        return EXIT_SUCCESS;
    }
    catch (const graph_exception & e )
    {
        std::cout << e.what() << std::endl ;
        
        exit(EXIT_FAILURE);
    }
}



	
