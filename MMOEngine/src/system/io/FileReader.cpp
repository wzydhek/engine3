#include "FileReader.h"

FileReader::FileReader(File* file) {
    file->setReadOnly();

    FileReader::file = file;
}

void FileReader::close() {
    validateReadable();

    file->close();
}

int FileReader::read(char* buf, int len) {
    validateReadable();

    return fread(buf, 1, len, file->getDescriptor());
}

int FileReader::read(char* buf, uint32 off, int len) {
    validateReadable();

    file->seek(off);

    return fread(buf, 1, len, file->getDescriptor());
}

bool FileReader::readLine(String& line) {
    validateReadable();

    char buf[4096];

    if (fgets(buf, 4096, file->getDescriptor()) != nullptr) {
        line = buf;

        return true;
    }
    else
        return false;
}

int FileReader::skip(int n) {
    validateReadable();

    return file->seek(n, SEEK_CUR);
}

void FileReader::validateReadable() {
    if (!file->exists())
        throw FileNotFoundException(file);
}
