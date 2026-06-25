#include "FileWriter.h"

FileWriterMkDirException::FileWriterMkDirException(const String& msg) : IOException(msg) {
}

FileWriterOpenException::FileWriterOpenException(const String& msg) : IOException(msg) {
}

FileWriter::FileWriter(File* file, bool append, bool delayOpen) {
	FileWriter::file = file;
	FileWriter::append = append;

	if (!delayOpen) {
		validateWriteable();
	}
}

void FileWriter::close() {
	if (!isOpen.get()) {
		return;
	}

	validateWriteable();

	//file->flush(); close already does flush internally

	file->close();
}

void FileWriter::flush() {
	if (!isOpen.get()) {
		return;
	}

	validateWriteable();

	file->flush();
}

int FileWriter::write(const char* str, int len) {
	validateWriteable();

	return fwrite(str, 1, len, file->getDescriptor());
}

int FileWriter::write(const char* str, uint32 off, int len) {
	validateWriteable();

	file->seek(off);

	return fwrite((byte*)str, 1, len, file->getDescriptor());
}

int FileWriter::write(char ch) {
	return write(&ch, 1);
}

int FileWriter::write(int val) {
	char buf[bufferLength];

	int written = snprintf(buf, sizeof(buf), "%i", val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(uint32 val) {
	char buf[bufferLength];

	int written = snprintf(buf, sizeof(buf), "%u", val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(long val) {
	char buf[bufferLength];

	int written = snprintf(buf, sizeof(buf), "%ld", val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(int64 val) {
	char buf[bufferLength];

	int written = sprintf(buf, "%lld", (long long)val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(uint64 val) {
	char buf[bufferLength];

	int written = snprintf(buf, sizeof(buf), "%llu", (unsigned long long) val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(float val) {
	char buf[bufferLength];

	int written = snprintf(buf, sizeof(buf), "%f", val);

	E3_ASSERT(written >= 0 && written < static_cast<int>(sizeof(buf)));

	return write(buf, written);
}

int FileWriter::write(const char* str) {
	return write(str, strlen(str));
}

int FileWriter::write(const String& str) {
	return write(str.toCharArray(), str.length());
}

int FileWriter::writeLine(const String& str) {
	int written = write(str.toCharArray(), str.length());
	written += write("\n", 1);

	return written;
}

FileWriter& FileWriter::operator<< (char ch) {
	write(ch);

	return *this;
}

FileWriter& FileWriter::operator<< (int val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (uint32 val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (long val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (int64 val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (uint64 val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (float val) {
	write(val);

	return *this;
}

FileWriter& FileWriter::operator<< (const char* str) {
	write(str);

	return *this;
}

FileWriter& FileWriter::operator<< (const String& str) {
	write(str);

	return *this;
}

FileWriter& FileWriter::operator<< (const StringBuffer& str) {
	write(str.getBuffer(), str.length());

	return *this;
}

File* FileWriter::getFile() {
	return file;
}

const File* FileWriter::getFile() const {
	return file;
}

void FileWriter::validateWriteable() {
	validateMutex.lock();

	try {
		if (!isOpen.get()) {
			if (!file->mkdirs()) {
				throw FileWriterMkDirException(file->getFileName());
			}

			bool success = append ? file->setAppendable() : file->setWriteable();

			if (!success) {
				throw FileWriterOpenException(file->getFileName());
			}

			isOpen.set(true);
		}

		if (!file->exists()) {
			throw FileNotFoundException(file);
		}
	}
	catch (...) {
		validateMutex.unlock();
		throw;
	}

	validateMutex.unlock();
}
