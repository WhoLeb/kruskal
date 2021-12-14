#pragma once
#include "Linked_List.h"

namespace WhoLeb
{
	template<class T>
	class queue : protected Linked_List<T>
	{
	public:
		queue();

		T front();
		void push(T value);
		T pop();
		bool is_empty();
	private:
		Linked_List<T>* list;
	};

	template<class T>
	inline queue<T>::queue()
	{
		list = new Linked_List<T>;
	}

	template<class T>
	inline T queue<T>::front()
	{
		return T(list->get_node(0)->value);
	}

	template<class T>
	inline void queue<T>::push(T value)
	{
		list->create_node(list->get_length(), value);
	}

	template<class T>
	inline T queue<T>::pop()
	{
		T res = list->remove_node(0);
		return T(res);
	}

	template<class T>
	inline bool queue<T>::is_empty()
	{
		return !(bool)list->get_length();
	}

}