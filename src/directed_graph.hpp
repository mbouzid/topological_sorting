#pragma once


//std lib
#include <set>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <unistd.h>
#include <list>
#include <fstream>
#include <ostream>

//own lib
#include "arc.hpp"
#include "vertex.hpp"
#include "graph_exception.hpp"
#include "strfun.hpp"

unsigned int min_index( std::set<vertex> queue , int dist[] , unsigned int n );

template <class W>
class directed_graph
{

    private :

                    
        /**
        *   A directed graph is an ordered pair G = <V,A> where V is a set of vertices and A a set of arcs. 
        *   @member {std::set<vertex>} m_vertices - the vertices are represented as a set of ordered vertices
        *   @member {std::set<std::pair<vertex,vertex>} - the arcs are represented as a set of pair of vertices
        **/        

        std::set <vertex> m_vertices ;  
        std::set < arc<W> > m_arcs ;

        
    public :


		vertex get_vertex ( unsigned int label ) const throw (graph_exception &)
		/**
		*	Return the vertex according to its label.
		*	@method @access public @readonly
		*	@param {unsigned int} label
		*	@return {vertex}
		*	@throws {graph_exception &} - an exception is thrown if the label does not correspond to any vertex
		**/
		{
			for ( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
			{
				if ( (*i).get_label() == label )
				{
					return (*i);
				}
			}
			
			throw (new graph_exception("This label does not correponds to a vertex"));
			
		}

        vertex get_vertex ( const std::string & symbol ) const throw ( graph_exception & )
        /**
        *   Return the vertex according to its symbol
        *   @method @access public @readonly
        *   @param {const std::string &} symbol
        *   @return {vertex}
        *   @throws {graph_exception &} - an exception is thrown if the symbol does not correspond to any vertex
        **/
        {
            for ( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {
                if ( (*i).get_symbol() == symbol )
                {
                    return (*i);
                }
            }
            throw (new graph_exception("This symbol does not corresponds to a vertex"));
        }

        unsigned int order() const
        /**
        *   Return the order of the graph, i.e. the number of its vertices
        *   @method @access public @readonly
        *   @return  {unsigned int}
        **/
        {
            return (m_vertices.size());
        }
                    
        void shortest_path( const vertex & source ) const throw (graph_exception &)
        /**
        *   Return the shortest path from a vertex source according to the weights of the arcs.
        *	WARNING : graph MUST BE CONNECTED
        *   @method @access public @readonly
        *   @param {const vertex & } source - a vertex source
        *   @throws {graph_exception &} - an exception is thrown if the source vertex does not belong to the graph
        **/
        {  
        	if ( belongs(source) )
            {
		    	unsigned int n = order() ;
		    	W dist[n] ;						//dist[] is an array indexed to the label of the vertices
		    	std::set<vertex> queue;			
		    	
		    	// set all the distances to 'infinity'
		    	for ( unsigned int i = 0 ; i<n ; ++i )
		    	{
		    		dist[i]=100000;
		    	}
		        
		    	dist[source.get_label()] =0; //distance to the source vertex is zero 

		        // set the queue with all the vertices
		    	for ( auto i= m_vertices.begin() ; i!= m_vertices.end() ; ++i )
		    	{
		    		queue.insert(*i);        		
		    	}

	
		    	while ( ! queue.empty() )
		    	{
		    	
		    		unsigned int u = min_index(queue,dist,n) ; // select  the  element  of  queue  with  the  minimal distance
		    		
		    		for ( auto j = queue.begin() ; j!= queue.end() ; j++ )
		    		{
		    			if ( (*j).get_label() == u )
		    			{
		    				queue.erase(*j);	// erase the vertex visited
		    			}
		    		}
		 
		    		
		    		for( auto a = m_arcs.begin() ; a!=m_arcs.end() ; ++a )
		    		{
		    				
		    			// for all successors of u 
		    			if ( (*a).get_in().get_label() == u  ) 
		    			{
		    				unsigned int v = (*a).get_out().get_label(); // get the successor
		    	
		    				if ( dist[v]  > dist[u] + (*a).get_weight() ) // if  new  shortest  path found
		    				{
		    					dist[v]=dist[u]+(*a).get_weight(); //set  new  value  of  shortest path
		    				
		    				}
		    			}
		    			else
		    			// for all predecessors of u 
		    			if ( (*a).get_out().get_label() == u  ) 
		    			{
		    				unsigned int v = (*a).get_in().get_label(); // get the predecessor
		    	
		    				if ( dist[v]  > dist[u] + (*a).get_weight() ) // if  new  shortest  path found
		    				{
		    					dist[v]=dist[u]+(*a).get_weight(); //set  new  value  of  shortest path
		    				
		    				}
		    			}

		    		}
		    		
		    	}
		    	
		    	std::cout << "Dijkstra algorithm result : " << std::endl ;
		    	
		    	//Original algorithm outputs value of shortest path  not the path itself 
		    	for ( unsigned int i = 0 ; i<n ; ++i )
		    	{
		    		if ( source.get_label() != i )
		    		{
		    			std::cout << " -> shortest distance "<< "(" << source << "," 
		    			<< get_vertex(i) << ")=" << dist[i] << " " << std::endl ;
		    		}
		    	}
            }
            else
                throw (new graph_exception("No such vertex in the graph"));

        }


   
    
        directed_graph ( const std::initializer_list<vertex> & vertices , const std::initializer_list<arc<W>> & arcs )
        /**
        *   Constructor.
        *   @constructor @access public
        *   @param {const std::initializer_list<vertex> &} vertices 
        *   @param {const std::initializer_list< arc<W> > &} arcs
        **/
        {
            for( auto i = vertices.begin() ; i!= vertices.end() ; ++i )
            {
                m_vertices.insert(*i);
            }
            
            for( auto i = arcs.begin() ; i!= arcs.end() ; ++i )
            {
                m_arcs.insert(*i);
            }
        }
                
        unsigned int number_of_predecessors ( const vertex & _ ) const throw (graph_exception &)
        /**
        *   Return the in-degree of a vertex.
        *   @param {const vertex & } _ - a vertex
        *   @return {unsigned int}
        *   @throws {graph_exception &} - an exception is thrown if the vertex is not in the graph 
        **/
        {
            if (belongs(_)) 
                return (predecessors_of(_).size());
            else 
                throw (new graph_exception("No such vertex in the graph"));
        }

        unsigned int number_of_successors ( const vertex & _ ) const throw (graph_exception &)
        /**
        *   Return the out-degree of a vertex.
        *   @param {const vertex & } _ - a vertex
        *   @return {unsigned int}
        *   @throws {graph_exception &} - an exception is thrown if the vertex is not in the graph.
        **/
        {
            if (belongs(_))
                return (successors_of(_).size());
            else
                throw (new graph_exception("No such vertex in the graph"));
        }

        std::set<vertex>::iterator source() const throw (graph_exception &)
        /**
        *   Return the last source vertex
        *   @method @access public @readonly
        *   @return {std::set<vertex>::iterator}
        *   @throws {graph_exception &} - an exception is thrown if the graph is acyclic 
        *    i.e. none of the vertices is a source vertex
        **/
        {    
            std::set<vertex>::iterator src ;
            for ( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {             
                if (number_of_predecessors(*i) == 0)    // identify a vertex with an in-degree equals to zero (no incoming edge) 
                {
                    src=i;     
                }
            } 

            if (src!=m_vertices.end())
                return src;
            else
                throw (new graph_exception("Acyclic graph"));
               
        
        }

        static void topological_sorting (const directed_graph & _ ) throw (graph_exception&)
        /**
        *   Topological sorting algorithm.
        *   @method @access public @static
        *   @throws {graph_exception&} - an exception is thrown if the graph is not an directed acyclic graph (aka DAG) 
        **/ 
        {
            std::list<vertex> output; //this is where the vertices will be placed
            directed_graph c(_);

            while ( !c.is_empty() )   // repeat until the graph is empty 
            {
                output.push_back(*(c.source())); // insertion of the first identified source vertex in the output
                c.get_rid_of(*(c.source()));    // deletion of this vertex and all his outgoing edges 
            }
            
            // display the output 
            std::cout << "topological ordering of vertices : " ;
            for( auto i = output.begin() ; i!= output.end() ; ++i )
            {
                std::cout << *i << " " ;
            }

            std::cout << std::endl;
            
        }

        directed_graph()
        /**
        *   Constructor.
        *   Create an empty directed graph.
        *   @constructor @access public
        **/   
        {

        }

        void add_vertex( const vertex & _ )
        /**
        *   Add a vertex in the graph.
        *   @method @access public
        *   @param {const vertex &} _ - a vertex
        **/
        {
            m_vertices.insert(_);
        }

        void add_arc( const arc<W> & _ )
        /**
        *   Add an arc in the graph.
        *   @method @access public
        *   @param {const arc<W> &} _ - an arc
        **/
        {
            m_arcs.insert(_);
        }

        void load( const char * filename )
        /**
        *   Load a graph from a file
        *   @method @access public
        *   @param {const char *} filename - a file name (or a path)
        **/
        {
              std::ifstream f(filename,std::ios::in);
              
              if (f)
              {
              	std::string vertices , line ;	
              	getline(f,vertices);	// the first line must specified the vertices
              	
              	std::string ** tokens_v = split(' ',vertices);	
              	size_t i = 0 ;
              	size_t words = number_words(' ',vertices);
              	
              	while ( i<words)
              	{
              		std::string symbol = *(tokens_v[i]) ;
              		m_vertices.insert(vertex(symbol));
              		++i;
              		
              	}
             	
             	free(tokens_v,words);
             	
             	std::string ** tokens_a ;
           		// the others lines represent the arcs
              	while ( getline(f,line,'\n') )
              	{
              		tokens_a = split(' ',line);
              		m_arcs.insert(arc<W>(*tokens_a[0],*tokens_a[1],*tokens_a[2]) );	
              		free(tokens_a,3);
 
              	}
              
              	f.close();
              }
              else
              		std::cerr << "Cannot open the file " << filename << std::endl;

        }
        
        void save( const char * filename ) const
        /**
        *	Save a graph in a file.
        *	@method @access public @readonly
        *	@param {const char *} filename 
        **/
        {
        	std::ofstream f(filename,std::ios::out);
            
            if (f)
            {
            	for ( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            	{
            		f << (*i) << " " ;
            	}
            	f << std::endl ;
            	
            	for ( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
            	{
            		f << (*i).get_in() << " " << (*i).get_out() << " " << (*i).get_weight() << std::endl;
            		
            	}
   
            	f.close();
            }
            else
            {
            	std::cerr << "Cannot open the file" << filename << std::endl ;	
            }
        }
        
        
        directed_graph( const directed_graph & _ )
        {
            for ( auto i = _.m_vertices.begin() ; i!= _.m_vertices.end() ; ++i )
            {   
                m_vertices.insert(*i);
            }
            
            for ( auto i = _.m_arcs.begin() ; i!= _.m_arcs.end() ; ++i )
            {
                m_arcs.insert(*i);
            }
        }

        ~directed_graph()
        /**
        *   Destructor.
        **/
        {


        }

        bool belongs( const vertex & _ ) const
        /**
        *   Predicate testing if a vertex is in the graph.
        *   @method @access public @readonly 
        *   @param {const vertex &} _ - a vertex
        *   @return {bool}
        **/
        {
            auto found = m_vertices.find(_);
            return ( (found!=m_vertices.end())?(true):(false));
        }

        bool is_empty() const
        /**
        *   Predicate testing emptiness.
        *   @method @access public @readonly
        *   @return {bool}
        **/
        {
            return (m_vertices.empty()&&m_arcs.empty());
        }

        void get_rid_of( const vertex & _ ) throw (graph_exception &)
        /**
        *   Get rid of a vertex and the arcs associated with it.
        *   @method @access public
        *   @param {const vertex &} _ - a vertex
        **/
        {
        	if (! belongs(_) ) throw new graph_exception("No such vertex in the graph");
        	else
            {
		            
                std::set<vertex>::iterator i = m_vertices.begin();
                while ( i != m_vertices.end() )
                {
                    if ( *i == _ )
                    {
                        m_vertices.erase(i++);
                    }
                    else
                    {
                        ++i;
                    }
                }
                
                typename std::set<arc<W>>::iterator j = m_arcs.begin();
                while ( j != m_arcs.end() )
                {
                    if ( ( (*j).get_in() == _ ) || ( (*j).get_out() == _ ) )
                    {
                        m_arcs.erase(j++);
                    }
                    else
                    {
                        ++j;
                    }
                } 
		      
                
		    }
        }

         
        void display() const
        /**
        *   Display the directed graph.
        *   @method @access public @readonly
        **/
        {
        	std::cout << "vertices : "  ;
            for( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {
               std::cout << (*i) << " " ;
            }
            
            std::cout << std::endl;
			std::cout << "arcs : " << std::endl ;
            for ( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
            {
                std::cout << *i << std::endl ;
            }
            std::cout<< std::endl;
        } 
        
        const std::set<vertex> & get_vertices() const
        /**
        *   Vertices getter.
        *   @method @access public @readonly 
        *   @return {const std::set<vertex>&} 
        **/
        {
            return m_vertices;
        }

        const std::set<arc<W>> &  get_arcs() const
        /**
        *   Arcs getter.
        *   @method @access public @readonly 
        *   @return {const std::set<arc<W>> &}
        **/
        {
            return m_arcs;
        }

        std::set<vertex> successors_of( const vertex & _ ) const
        /**
        *   Return the list of the successors of a vertex.
        *   @method @access public @readonly
        *   @param {const vertex&} _ - a vertex
        *   @return {std::set<vertex>}
        **/
        {
            std::set<vertex> successors;
            if (belongs(_))
            {
                for( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
                {
                    if ( (*i).get_in() == _ )
                        successors.insert((*i).get_in());
                }
            }
            return successors; 
        }

        std::set<vertex> predecessors_of( const  vertex & _ ) const
        /**
        *   Return the list of the predecessors of a vertex.
        *   @method @access public @readonly
        *   @param {const vertex &} _ - a vertex 
        *   @return std::set<vertex>
        **/
        {
            std::set<vertex> predecessors;
            if (belongs(_))
            {
                for ( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
                {
                    if ( (*i).get_out() == _ )
                        predecessors.insert((*i).get_out());
                }
            }
            return predecessors;
        }
};

