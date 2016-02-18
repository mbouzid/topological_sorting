#pragma once

#include <string>

unsigned int number_words( char separator , const std::string & str ) ;
void free ( std::string ** p_str , size_t sz );
std::string ** split ( char separator , const std::string & str );
