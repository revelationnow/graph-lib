/// \file errHandler.hpp
#ifndef _ERRHANDLER_HPP_
#define _ERRHANDLER_HPP_

typedef enum {
  ERR_LEVEL_INFO,
  ERR_LEVEL_WARN,
  ERR_LEVEL_ERR,
  ERR_LEVEL_FATAL,
  ERR_LEVEL_MAX
} errHandlerTagEnumType;

#define PRINT_TAG __FILE__<<"\t"<<__LINE__<<"\t"<<__DATE__<<"\t"<<__TIME__<<"\t"
#define OUTPUT_MSG(TAG, MSG) OUTPUT_MSG_##TAG(MSG)



#define OUTPUT_MSG_ERR_LEVEL_INFO(MSG)  
#define OUTPUT_MSG_ERR_LEVEL_WARN(MSG)  
#define OUTPUT_MSG_ERR_LEVEL_ERR(MSG)   OUTPUT_MSG_COMMON(ERR,MSG)
#define OUTPUT_MSG_ERR_LEVEL_FATAL(MSG) OUTPUT_MSG_COMMON(FATAL,MSG)

#define OUTPUT_MSG_COMMON(TAG, MSG) cout<<PRINT_TAG<< #TAG" : "<<MSG<<endl;

#endif
