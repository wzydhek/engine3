#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(File* file) : IOException("FileNotFoundException") {
	message = message + " - file \'" + file->getName() + " not found";
}