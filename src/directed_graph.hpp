#pragma once

#include <set>
#include <iostream>
#include "vertex.hpp"
#include "graph_exception.hpp"
#include <initializer_list>
#include <algorithm>
#include <unistd.h>

class directed_graph
{

    private :
        
        std::set <vertex> m_vertices ;
        std::set <std::pair<vertex,vertex>> m_arcs ;

    public :


        unsigned int number_of_predecessors ( const vertex & _ ) const
        {
            return (predecessors_of(_).size());
        }

        unsigned int number_of_successors ( const vertex & _ ) const
        {
            return (successors_of(_).size());
        }

        std::set<vertex>::iterator source() const
        /**
        *   Return the first source vertex
        *   @method @access public @readonly
        *   @return {std::set<vertex>::iterator}
        **/
        {
            std::set<vertex>::iterator pred = m_vertices.begin();
                
            for ( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {             
                if (number_of_predecessors(*i) == 0)
                {
                    pred=i;
                }
    
            } 

            return pred;
        }

        void topological_sorting() 
        /**
        *   Topological sorting algorithm.
        *   @method @access public 
        **/ 
        {
                
            while ( !is_empty() )
            {
                std::cout << *source() << " ";
                get_rid_of(*(source()));
                
            }

            std::cout << std::endl;
            
            
        }   
        
        directed_graph( const std::set<vertex> & vertices , const std::set<std::pair<vertex,vertex>> & arcs )
        /** 
        *   Constructor.
        *   Creates a directed graph according to a set of vertices and a set of pairs of vertices.
        *   @param {const std::set<vertex> &} vertices
        *   @param {const std::set<std::pair<vertex,vertex>> &} arcs 
        **/
        {
            for( auto i = vertices.begin() ; i!= vertices.end() ; ++i)
            {
                m_vertices.insert(*i);
            }
    
            for( auto i = arcs.begin() ; i != arcs.end() ; ++i )
            {
                if ( belongs((*i).first) && belongs((*i).second) )
                    m_arcs.insert(*i);      
            }

        }

        directed_graph( const std::initializer_list<vertex> & vertices , const std::initializer_list<std::pair<vertex,vertex>> & arcs )
        /**
        *   Constructor.
        *   Creates a directed graph with two initializer_list
        *   @constructor @access public
        *   @param {std::initializer_list<vertex>} vertices
        *   @param {std::initializer_list<std::pair<vertex,vertex>>} arcs
        **/ 
        {
            for (auto i = vertices.begin() ; i!= vertices.end() ; ++i )
            {
                m_vertices.insert(*i);
            }
            for (auto i = arcs.begin() ; i!= arcs.end() ; ++i )
            {
                if (belongs((*i).first) && belongs((*i).second))
                {
                    m_arcs.insert(*i);
                }
            }

        }

        directed_graph()
        /**
        *   Constructor.
        *   Create an empty directed graph.
        *   @constructor @access public
        **/   
        {

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

        void get_rid_of( const vertex & _ )
        /**
        *   Get rid of a vertex and the arcs associated with it.
        *   @method @access public
        *   @param {const vertex &} _ - a vertex
        **/
        {
            for( auto i = m_vertices.begin() ; i!= m_vertices.end() ; ++i )
            {
                if ((*i)==_) 
                {
                    m_vertices.erase(*i);
                }
            }
            
            for ( auto i = m_arcs.begin() ; i!= m_arcs.end() ; ++i )
            {
                if (((*i).first==_)||((*i).second==_))
                {
                    m_arcs.erase(*i);
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
                std::cout << "(" << (*i).first << "," << (*i).second << ")" << " ";
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
                    if ( (*i).first == _ )
                        successors.insert((*i).second);
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
                    if ( (*i).second == _ )
                        predecessors.insert((*i).first);
                }
            }
            return predecessors;
        }
};

