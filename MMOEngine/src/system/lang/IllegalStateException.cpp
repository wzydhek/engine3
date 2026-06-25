#include "IllegalStateException.h"

IllegalStateException::IllegalStateException() : Exception("IllegalStateException") {
}

IllegalStateException::IllegalStateException(String s) : Exception("IllegalStateException") {
	message = message + " - " + s;
}
