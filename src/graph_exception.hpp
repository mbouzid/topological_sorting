#pragma once


#include <exception>
#include <string>
#include <iostream>

/**
*	Handle graph exceptions 
*	@class graph_exception
**/
class graph_exception : public std::exception
{

	private :
	
			std::string m_error_message;
	

	public :
		
		graph_exception( const std::string & error_message ):m_error_message(error_message)
		/**
		* Constructor.
		* @constructor @access public
		* @param {const std::string &} error_message
		**/
		{;}
		
		virtual const char * what() const throw()
		/**
		* Describe the exception.
		* @method @access public @abstract
		* @throws none
		**/
		{
			return m_error_message.c_str();
		}
		
		
		virtual ~graph_exception() throw()
		/**
		* Destructor
		* @destructor @access public @abstract
		* @throws none
		**/
		{;}



};
