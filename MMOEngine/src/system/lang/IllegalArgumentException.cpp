#include "IllegalArgumentException.h"

IllegalArgumentException::IllegalArgumentException() : Exception("IllegalArgumentException") {
}

IllegalArgumentException::IllegalArgumentException(String s) : Exception("IllegalArgumentException") {
	message = message + " - " + s;
}
