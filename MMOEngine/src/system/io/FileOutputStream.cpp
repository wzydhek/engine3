#include "FileOutputStream.h"

FileOutputStream::FileOutputStream(File* file) {
    file->setBinary();

    file->setWriteable();

    FileOutputStream::file = file;
}

void FileOutputStream::close() {
    validateWriteable();

    file->flush();

    file->close();
}

void FileOutputStream::flush() {
    validateWriteable();

    file->flush();
}

int FileOutputStream::write(byte* buf, int len) {
    validateWriteable();

    return fwrite(buf, 1, len, file->getDescriptor());
}

int FileOutputStream::write(byte* buf, uint32 off, int len) {
    validateWriteable();

    file->seek(off);

    return fwrite(buf, 1, len, file->getDescriptor());
}

int FileOutputStream::write(char ch) {
	return fwrite(&ch, 1, 1, file->getDescriptor());
}

int FileOutputStream::write(int val) {
	return fwrite(&val, 1, 4, file->getDescriptor());
}

int FileOutputStream::write(uint32 val) {
	return fwrite(&val, 1, 4, file->getDescriptor());
}

int FileOutputStream::write(long val) {
	return fwrite(&val, 1, sizeof(long), file->getDescriptor());
}

int FileOutputStream::write(int64 val) {
	return fwrite(&val, 1, 8, file->getDescriptor());
}

int FileOutputStream::write(uint64 val) {
	return fwrite(&val, 1, 8, file->getDescriptor());
}

int FileOutputStream::write(float val) {
	return fwrite(&val, 1, sizeof(float), file->getDescriptor());
}

int FileOutputStream::write(const char* str) {
	return fwrite(str, 1, strlen(str), file->getDescriptor());
}

int FileOutputStream::write(const String& str) {
	return write((byte*)str.toCharArray(), str.length());
}

FileOutputStream& FileOutputStream::operator<< (char ch) {
	write(ch);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (int val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (uint32 val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (long val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (int64 val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (uint64 val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (float val) {
	write(val);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (const char* str) {
	write(str);

	return *this;
}

FileOutputStream& FileOutputStream::operator<< (const String& str) {
	write(str);

	return *this;
}

void FileOutputStream::validateWriteable() {
	if (!file->exists())
		throw FileNotFoundException(file);
}
