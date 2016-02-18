//std lib
#include <stdlib.h>
#include <iostream>
#include <initializer_list> 

//own lib
#include "directed_graph.hpp"
#include "arc.hpp"

int main( int argc , char * argv [] )
{
   
   if ( argc > 1 )
   {
   		int example = atoi(argv[1]);
   		
   		switch (example)
   		{
   			case 1 :
   			{
					vertex v1("0");
					vertex v2("1");
					vertex v3("2");
					vertex v4("3");
					vertex v5("4");
					vertex v6("5");
			
					arc<int> a1 (v1,v2,2);    
					arc<int> a2 (v1,v4,4);
					arc<int> a3 (v2,v3,1);
					arc<int> a4 (v3,v5,3);
					arc<int> a5 (v5,v4,3);
					arc<int> a6 (v5,v6,2);
					arc<int> a7(v4,v6,2);
					arc<int> a8(v2,v4,4);
				 	arc<int> a9(v2,v5,2);
				
		
					directed_graph<int> d({v1,v2,v3,v4,v5,v6},{a1,a2,a3,a4,a5,a6,a7,a8,a9});
		
					try
					{
						d.display();
					 
						directed_graph<int>::topological_sorting(d);
					
				 		d.shortest_path(v1);
				 		d.shortest_path(v2);
				 		d.shortest_path(v3);
				 		d.shortest_path(v4);
				 		d.shortest_path(v5);
				 		d.shortest_path(v6);
				 		
						return EXIT_SUCCESS;
					}//end try
					catch (const graph_exception & e )
					{
						std::cerr << e.what() << std::endl ;
					
						exit(EXIT_FAILURE);
					}//end catch
				
					break;
			}//end case
			case 2 :
			{
				directed_graph<int> d ;
				d.load("examples/villes.txt");
				d.display();
				break ;
			}//end case
		}//end switch
	}//end if
	else
	{
		std::cerr << " Using : ./topological_sorting [EXAMPLE NUMBER] " << std::endl;
		exit(EXIT_FAILURE);
	}// end else
}



	
