#pragma once

//std lib
#include <set>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <unistd.h>
#include <list>

//own lib
#include "vertex.hpp"
#include "graph_exception.hpp"
#include "arc.hpp"

template <class W>
class directed_graph
{

    private :
        
        /**
        *   A directed graph is an ordered pair G = <V,A> where V is a set of vertices and A a set of arcs. 
        *   @member {std::set<vertex>} m_vertices - the vertices are represented as a set of ordered vertices
        *   @member {std::set<arc<W>>} - the arcs are represented as a set of ordered arcs
        **/        

        std::set <vertex> m_vertices ;  
        std::set < arc<W> > m_arcs ;

        
    public :
        
        //BONUS 
        W shortest_path() const
        /**
        *   Return the shortest path according to the weights of the arcs.
        *   @method @access public @readonly
        *   @return {W}
        **/
        {    
                   /** TODO
                   		Dijkstra algorithm !
                   	**/
            return 0;
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
        *   @access public @static
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
            std::cout << "Ordering of vertices : " ;
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
        
        directed_graph( const directed_graph & _ )
        /**
         * Copy constructor
         * @constructor @access public
         * @param {const directed_graph &} _ - a graph to copy
         **/
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
        	if (! belongs(_) ) 
        		throw new graph_exception("No such vertex in the graph");
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
            for( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {
               std::cout << (*i) << " " ;
            }
            
            std::cout << std::endl;

            for ( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
            {
                std::cout << *i << " ";
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
        *   Return a list of the successors of a vertex.
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
        *   Return a list of the predecessors of a vertex.
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

