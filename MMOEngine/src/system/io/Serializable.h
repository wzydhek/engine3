/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "system/lang/String.h"
#include "system/lang/Object.h"
#include "system/util/VectorMap.h"
#include "ObjectInputStream.h"

namespace sys {
	namespace io {

		class ObjectOutputStream;
		class ObjectInputStream;

		class VariableName;

		class Serializable : public virtual Object {
		protected:
			SerializableString _className;
			VectorMap<VariableName, uint64> _variables;

		public:
			const static bool is_virtual_object = true;

			Serializable();
			Serializable(const Serializable& s);
			Serializable(Serializable&& s);

			Serializable& operator=(const Serializable& s);
			Serializable& operator=(Serializable&& s);

			virtual ~Serializable() = default;

			//virtual void writeObject(String& str);
			virtual void writeObject(ObjectOutputStream* stream);

			//virtual void readObject(const String& str);
			virtual void readObject(ObjectInputStream* stream);

			void addSerializableVariable(const char* name, uint8* variable, int version = 0);
			void addSerializableVariable(const char* name, int8* variable, int version = 0);

			void addSerializableVariable(const char* name, uint16* variable, int version = 0);
			void addSerializableVariable(const char* name, int16* variable, int version = 0);

			void addSerializableVariable(const char* name, uint32* variable, int version = 0);
			void addSerializableVariable(const char* name, int32* variable, int version = 0);

			void addSerializableVariable(const char* name, uint64* variable, int version = 0);
			void addSerializableVariable(const char* name, int64* variable, int version = 0);

			void addSerializableVariable(const char* name, float* variable, int version = 0);
			void addSerializableVariable(const char* name, double* variable, int version = 0);

			void addSerializableVariable(const char* name, bool* variable, int version = 0);

			void addSerializableVariable(const char* name, Variable* variable, int version = 0);
			Variable* getSerializableVariable(const char* name);

			/*bool toString(String& str) {
				writeObject(str);

				return true;
			}

			bool parseFromString(const String& str, int version = 0) {
				readObject(str);

				return true;
			}*/

			bool toBinaryStream(ObjectOutputStream* stream);

			bool parseFromBinaryStream(ObjectInputStream* stream);

			void _setClassName(const String& name);

			String& _getClassName();

			const String& _getClassName() const;

			static int getObjectData(const String& str, String& obj);

			static int serializeAtomicType(void* address, int type, String& value);
			static int serializeAtomicType(void* address, int type, ObjectOutputStream* stream);

			static int deSerializeAtomicType(void* address, int type, const String& value);
			static int deSerializeAtomicType(void* address, int type, ObjectInputStream* stream);

			static int getVariableDataMap(const String& serializedData, VectorMap<String, String>& map);
			static int getVariableDataOffset(const String& variableName, ObjectInputStream* stream);
			static int getVariableDataOffset(const uint32& variableHashCode, ObjectInputStream* stream);

			static int getVariableNames(Vector<String>& variableNames, ObjectInputStream* stream);

			/**
			 * Returns a new ObjectOutputStream with the modified variable data
			 * Returns nullptr on error
			 */
			static ObjectOutputStream* convertToHashCodeNameMembers(ObjectInputStream* object);
			static ObjectOutputStream* changeVariableData(const String& variableName, ObjectInputStream* object, Stream* newVariableData);
			static ObjectOutputStream* changeVariableData(const uint32& variableHashCode, ObjectInputStream* object, Stream* newVariableData);
			static ObjectOutputStream* deleteVariable(const String& variableName, ObjectInputStream* object);
			static ObjectOutputStream* changeVariableName(const String& variableName, const String& newVariableName, ObjectInputStream* object);
			static ObjectOutputStream* addVariable(const String& variableName, ObjectInputStream* object, Stream* newVariableData);

			template<typename ClassType> static bool getVariable(const String& variableName, ClassType* address, ObjectInputStream* serializedObject) {
				int offset = getVariableDataOffset(variableName, serializedObject);

				if (offset == -1)
					return false;

				serializedObject->setOffset(offset);

				TypeInfo<ClassType>::parseFromBinaryStream(address, serializedObject);

				serializedObject->reset();

				return true;
			}

			template<typename ClassType> static bool getVariable(const uint32& variableHashCode, ClassType* address, ObjectInputStream* serializedObject) {
				int offset = getVariableDataOffset(variableHashCode, serializedObject);

				if (offset == -1)
					return false;

				serializedObject->setOffset(offset);

				TypeInfo<ClassType>::parseFromBinaryStream(address, serializedObject);

				serializedObject->reset();

				return true;
			}

			template<typename ClassType> static bool getVariable(const String& variableName, ClassType* address, const String& serializedObject) {
				VectorMap<String, String> variableDataMap;

				int variableSize = getVariableDataMap(serializedObject, variableDataMap);

				if (!variableDataMap.contains(variableName))
					return false;

				String variableData = variableDataMap.get(variableName);

				TypeInfo<ClassType>::parseFromString(address, variableData);

				return true;
			}

		private:
			void deSerializeVariable(const String& nameAndVersion, const String& varData);

		};

		class VariableName {
			const char* name;
			uint8 version;

			uint8 type;

		public:
			VariableName();

			VariableName(const char* name, int version);

			VariableName(const VariableName& v);

			VariableName& operator=(const VariableName& v);

			~VariableName() {

			}

			int compareTo(const VariableName& str) const;

			const char* getName() const;

			void setName(const char* str);

			void setVersion(int ver);

			void setType(int typ);

			int getVersion() const;

			int getType() const;

			/*bool toString(String& str) {
				return false;
			}

			bool parseFromString(const String& str, int version = 0) {
				return false;
			}*/

			bool toBinaryStream(ObjectOutputStream* stream);

			bool parseFromBinaryStream(ObjectInputStream* stream);

		};
	}
}

using namespace sys::io;
