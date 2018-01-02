
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <stdexcept>

   class StructExceptions {};

    namespace Sexceptions {

        class OutOfMemory : public std::exception {};
        class NotExist : public std::exception {};
        class AlreadyExist : public std::exception {};
        class InvalidInput : public std::exception {};
}		class Error : public std::exception {};

#endif /* EXCEPTIONS_H_ */
