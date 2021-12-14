#pragma once
#include <iostream>
#include <cstdarg>


namespace WhoLeb
{
	template<class T>
	class Linked_List
	{
	public:
		Linked_List(const size_t size, ...);
		Linked_List(T val) : value(val) {}
		Linked_List();

		void create_node(size_t place, T value);
		T remove_node(const size_t place);
		size_t find_first_of(T value);
		Linked_List<T>& operator[](size_t place);
		Linked_List<T>* get_node(size_t place);

		size_t get_length();
		

		T value;
	protected:
		Linked_List<T>* find_at(size_t place);

		Linked_List* head;
		Linked_List* next_node;
	};

	template<class T> Linked_List<T>::Linked_List(const size_t size, ...)
	{
		Linked_List<T>* current = new Linked_List<T>;
		if (!head) 
		{
			head = current;
			head->head = head;
		}
		Linked_List<T>* list = 0;

		std::va_list args;
		va_start(args, size);

		for (unsigned int i = 0; i < size; i++)
		{
			if (i == 0) list = current;

			current->value = va_arg(args, T);

			if (i < size - 1)
			{
				current->next_node = new Linked_List<T>();
				current->next_node->head = this->head;
				current = current->next_node;
			}
			else current->next_node = nullptr;
		}

	}

	template<class T> Linked_List<T>::Linked_List()
	{
		head = nullptr;
		next_node = nullptr;
		//value = (T)NULL;
	}

	template<class T> void Linked_List<T>::create_node(size_t place, T val)
	{
		Linked_List<T>* tmp = head;
		Linked_List<T>* new_el = new Linked_List<T>(val);
		Linked_List<T>* templ1 = nullptr;
		if (head) {
			templ1 = find_at(place)->next_node;
			new_el->head = head;
		}
		if (place == 0)
		{
			new_el->next_node = head;
			head = new_el;
			while (tmp)
			{
				tmp->head = head;
				tmp = tmp->next_node;
			}
		}
		else
		{
			find_at(place - 1)->next_node = new_el;
			new_el->next_node = templ1;
			/*while (tmp)
			{
				tmp->head = head;
				tmp = tmp->next_node;
			}*/
		}
	}

	template<class T> T Linked_List<T>::remove_node(const size_t place)
	{
		T tmp;
		if (place == 0)
		{
			if (head == nullptr) return T(NULL);
			Linked_List* templ = head->next_node;
			tmp = head->value;
			delete head;
			head = templ;
			while (templ)
			{
				templ->head = head;
				templ = templ->next_node;
			}
		}
		else
		{
			Linked_List* templ_1 = find_at(place);

			Linked_List* templ_2 = templ_1->next_node;
			tmp = templ_1->value;
			delete templ_1;

			find_at(place - 1)->next_node = templ_2;
		}
		return tmp;
	}

	template<class T> size_t Linked_List<T>::get_length()
	{
		int k = 1;
		auto tmp = head;
		if (tmp == nullptr) return 0;
		while (tmp->next_node)
		{
			k++;
			tmp = tmp->next_node;
		}
		return k;
	}

	template<class T> Linked_List<T>& Linked_List<T>::operator [](size_t place)
	{
		Linked_List<T>& tmp = &head;
		for (size_t i = 0; i < place && tmp->next_node; i++)
		{
			tmp = tmp->next_node;
		}
		return tmp.next_node;
	}

	template<class T>
	inline Linked_List<T>* Linked_List<T>::get_node(size_t place)
	{
		Linked_List<T>* tmp = head;
		for (size_t i = 0; i < place && tmp->next_node; i++)
		{
			tmp = tmp->next_node;
		}
		return tmp;
		// TODO: insert return statement here
	}

	template<class T> Linked_List<T>* Linked_List<T>::find_at(size_t place)
	{
		Linked_List<T>* tmp = head;
		if (!tmp) return nullptr;
		for (size_t i = 0; i < place && tmp->next_node; i++)
		{
			tmp = tmp->next_node;
		}
		return tmp;
	}

	template<class T> size_t Linked_List<T>::find_first_of(T val)
	{
		auto tmp = head;
		size_t k = 0;
		while (tmp)
		{
			if (tmp->value == val)
				return k;
			tmp = tmp->next_node;
			k++;
		}
		return -1;
	}
}

