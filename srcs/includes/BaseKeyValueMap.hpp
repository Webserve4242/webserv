#ifndef BASEKEYVALUEMAP_HPP
#define BASEKEYVALUEMAP_HPP

#include <map>
#include <string>

class	BaseKeyValueMap
{
	private:

	public:
		BaseKeyValueMap(void);
		BaseKeyValueMap(const BaseKeyValueMap &other);
		virtual ~BaseKeyValueMap();
};

#endif