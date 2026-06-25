#include "FileInputStream.h"

FileInputStream::FileInputStream(File* file) {
    file->setBinary();

    file->setReadOnly();

    FileInputStream::file = file;
}

void FileInputStream::close() {
    validateReadable();

    file->close();
}

int FileInputStream::read(byte* buf, int len) {
    validateReadable();

    return fread(buf, 1, len, file->getDescriptor());
}

int FileInputStream::read(byte* buf, uint32 off, int len) {
    validateReadable();

    file->seek(off);

    return fread(buf, 1, len, file->getDescriptor());
}

int FileInputStream::skip(int n) {
    validateReadable();

    return file->seek(n, SEEK_CUR);
}

void FileInputStream::validateReadable() {
    if (!file->exists())
        throw FileNotFoundException(file);
}
