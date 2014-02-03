/// \file errHandler.hpp
#ifndef _ERRHANDLER_HPP_
#define _ERRHANDLER_HPP_

#define PRINT_TAG __FILE__<<"\t"<<__LINE__<<"\t"<<__DATE__<<"\t"<<__TIME__<<"\t"
#define OUTPUT_MSG(TAG, MSG) cout<<PRINT_TAG<< #TAG" : " << MSG << endl;
#endif
