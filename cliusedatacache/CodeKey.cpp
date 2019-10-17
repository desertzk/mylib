#include "CodeKey.h"

namespace std {

	size_t hash<CodeKey>::operator()(const CodeKey& ck) const
	{
		return hash<string>()(ck.code) ^ hash<int>()(ck.type) ^ hash<int>()(ck.time);
	}
}

//CodeKey::CodeKey()
//{
//}
//
//
//CodeKey::~CodeKey()
//{
//}

bool operator==(const CodeKey& lci, const CodeKey& otherci)
{
	return (strcmp(lci.code, otherci.code) == 0) && lci.type == otherci.type&&lci.time == otherci.time;
}