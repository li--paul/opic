#ifndef OP_LOG_H
#define OP_LOG_H 1
#include "op_macros.h"
#include <log4c.h>

OP_BEGIN_DECLS
extern void opic_log4c_init();
OP_END_DECLS

#define OP_LOGGER_FACTORY(logger, catName) \
static const log4c_category_t* logger; \
__attribute__((constructor)) \
static void init_##logger() \
{ \
  opic_log4c_init(); \
  logger = log4c_category_get(catName); \
}

#define OP_LOG_ARGS(LOGGER, CATEGORY, MESSAGE, ...) \
  log4c_category_log(LOGGER, CATEGORY, "%s():%d " \
      MESSAGE, __func__, __LINE__, __VA_ARGS__)

#define OP_LOG_NO_ARGS(LOGGER, CATEGORY, MESSAGE) \
  log4c_category_log(LOGGER, CATEGORY, "%s():%d " \
      MESSAGE, __func__, __LINE__)

#define OP_LOG_FATAL(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_FATAL, __VA_ARGS__)

#define OP_LOG_ALERT(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_ALERT, __VA_ARGS__)

#define OP_LOG_CRIT(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_CRIT, __VA_ARGS__)

#define OP_LOG_ERROR(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_ERROR, __VA_ARGS__)

#define OP_LOG_WARN(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_WARN, __VA_ARGS__)

#define OP_LOG_NOTICE(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_NOTICE, __VA_ARGS__)

#define OP_LOG_INFO(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_INFO, __VA_ARGS__)

#ifndef NDEBUG
  
#define OP_LOG_DEBUG(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_DEBUG, __VA_ARGS__)

#define OP_LOG_TRACE(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_TRACE, __VA_ARGS__)

#else

#define OP_LOG_DEBUG(LOGGER, ...) ((void) 0)
#define OP_LOG_TRACE(LOGGER, ...) ((void) 0)

#endif

#ifndef UNIT_TESTING

#define OP_LOG_NOTEST(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_NOTEST, __VA_ARGS__)

#else

#define OP_LOG_NOTEST(LOGGER, ...) ((void) 0)

#endif

#define OP_LOG_UNKNOWN(LOGGER, ...) \
  _OP_GET_MACRO_BY_ARGS(__VA_ARGS__, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, \
   OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_ARGS, OP_LOG_NO_ARGS)(LOGGER, LOG4C_PRIORITY_UNKNOWN, __VA_ARGS__)

#endif
