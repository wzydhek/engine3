#include "Character.h"

Character::Character() : BaseTypeVariable<char>(0) {
}

Character::Character(char val) : BaseTypeVariable<char>(val) {
}

Character::Character(const Character& val) : BaseTypeVariable<char>(val) {
}

Character& Character::operator = (const Character& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<char>::operator=(val);

	return *this;
}

bool Character::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool Character::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Character::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeSignedByte(get());

	return true;
}

bool Character::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readSignedByte();

	return true;
}

char Character::valueOf(const String& str) {
	return str.charAt(0);
}

bool Character::isDigit(char ch) {
	return isdigit(ch);
}

bool Character::isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool Character::isLetterOrDigit(char ch) {
	return isalpha(ch);
}

bool Character::isLowerCase(char ch) {
	return islower(ch);
}

bool Character::isUpperCase(char ch) {
	return isupper(ch);
}

char Character::toLowerCase(char ch) {
	if (isUpperCase(ch))
		return 'a' + (ch - 'A');
	else
		return ch;
}

char Character::toUpperCase(char ch) {
	if (isLowerCase(ch))
		return 'A' + (ch - 'a');
	else
		return ch;
}

uint32 Character::hashCode(char value) {
	return (uint32)value;
}

UnsignedCharacter::UnsignedCharacter() : BaseTypeVariable<unsigned char>(0) {
}

UnsignedCharacter::UnsignedCharacter(unsigned char val) : BaseTypeVariable<unsigned char>(val) {
}

UnsignedCharacter::UnsignedCharacter(const UnsignedCharacter& val) : BaseTypeVariable<unsigned char>(val) {
}

UnsignedCharacter& UnsignedCharacter::operator=(const UnsignedCharacter& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<unsigned char>::operator=(val);

	return *this;
}

bool UnsignedCharacter::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool UnsignedCharacter::parseFromString(const String& str, int version) {
	*this = Character::valueOf(str);

	return true;
}

bool UnsignedCharacter::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeByte(get());

	return true;
}

bool UnsignedCharacter::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readByte();

	return true;
}

uint32 UnsignedCharacter::hashCode(unsigned char value) {
	return (uint32)value;
}
