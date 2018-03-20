#pragma once

template <typename T>
class singleton
{
public:
	static T* Get()
	{
		static T value;
		return &value;
	}
};