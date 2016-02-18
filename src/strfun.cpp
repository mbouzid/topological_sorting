#include "strfun.hpp"

unsigned int number_words( char separator , const std::string & str ) 
{

	if ( str.empty() ) 
		return 0;
	else 
	{
		size_t separator_index = str.find_first_of(separator);
		size_t sz = str.length();

		if (separator_index != std::string::npos ) 
		{
			std::string sub = str.substr(separator_index+1,sz);
			return 1+number_words(separator,sub);
		} 
		else 
			return 1;
	}
	
}


void free ( std::string ** p_str , size_t sz )
{
	for ( size_t i = 0 ; i< sz ; ++i )
    {
        delete p_str[i] ;
    }
    delete [] p_str ;
}

std::string ** split ( char separator, const std::string & str)
{

		if ( str.empty() ) 
			return NULL ;
		else 
		{
			
			unsigned int n = number_words(separator,str);
			std::string ** tokens = new std::string * [n];
			std::string sub = str;
			
			for(unsigned int i=0;i<n;i++) 
			{
				
				
				size_t separator_index = sub.find_first_of(separator);
				size_t sz = sub.length();

				if ( separator_index != std::string::npos ) 
				{	
						
					std::string sub1 = sub.substr(0,separator_index);						
					
					tokens[i]=new std::string (sub1);
				
					sub=sub.substr(separator_index+1,sz);
						
				} 
				else 
				{ 
						
					tokens[i]=new std::string(sub);

				}

			}
		
			return tokens;				
			
		}


	}
