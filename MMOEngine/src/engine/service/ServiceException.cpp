#include "ServiceException.h"

ServiceException::ServiceException() : Exception() {
}

ServiceException::ServiceException(const String& msg) : Exception(msg) {
}