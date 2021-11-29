#pragma once
#include <iostream>
#include <cstdarg>


namespace WhoLeb
{

	template <typename T>
	class dynamic_array
	{
	public:
		dynamic_array(const size_t size, ...);
		dynamic_array();

		inline T get(size_t place);
		void add_element(const size_t, T value);
		T remove_element(const size_t place);
		T operator[](size_t place);
		int find_first_of(T value);
		size_t size();
		virtual bool empty();
		virtual void push(T value);
		virtual T pop();
		void sort();

	protected:
		void double_size();
		void reduce_size();
		size_t element_size();

		size_t current_count;
		size_t current_size;
		T* arr;

		class pair
		{
		public:
			int length;
			T* _array;
		};


	private:
		void m_sort();
		int get_minrun();
		void insertion_sort(T* arr, int n);
		void insertion_sort_by_length(pair* arr, int n);
		T* merge(pair* first, pair* second);
		int minrun;
	};

	template<class T> dynamic_array<T>::dynamic_array()
	{
		current_size = 1;
		current_count = 0;
		arr = new T[1];
		minrun = get_minrun();
	}

	template<class T> T dynamic_array<T>::get(size_t place)
	{
		if (place == -1) std::cout << "bad input";
		return arr[place];
	}

	template<class T> dynamic_array<T>::dynamic_array(const size_t size, ...)
	{
		int k = 0;
		unsigned int csize = size;
		while (csize)
		{
			csize /= 2;
			k++;
		}
		current_size = 1 << k;

		arr = new T[current_size];
		std::va_list args;
		va_start(args, size);

		for (size_t i = 0; i < size; i++)
			arr[i] = va_arg(args, T);

		va_end(args);

		current_count = size;
		minrun = get_minrun();
	}

	template<class T> void dynamic_array<T>::add_element(const size_t place, T value)
	{
		if (current_count + 1 > current_size) double_size();
		for (size_t i = current_count; i > place; i--)
			arr[i] = arr[i - 1];
		arr[place] = value;
		current_count++;
	}

	template<class T> T dynamic_array<T>::remove_element(const size_t place)
	{
		T v = arr[place];
		if (place < 0);
		else
		{
			for (size_t i = place; i < current_count - 1; i++)
				arr[i] = arr[i + 1];
			current_count--;
			while (current_count < current_size / 2)
				reduce_size();
			return v;
		}
	}

	template<class T> T dynamic_array<T>::operator[](size_t place)
	{
		if (place > current_count)
		{
			std::cout << "Bad input ";
		}
		return arr[place];
	}

	template<class T> size_t dynamic_array<T>::size()
	{
		return current_count;
	}

	template<class T> int dynamic_array<T>::find_first_of(T val)
	{
		for (int i = 0; i < size(); i++)
			if (arr[i] == val) return i;
		return -1;
	}

	template<class T> bool dynamic_array<T>::empty()
	{
		const bool val = static_cast<bool>(size());
		return !val;
	}

	template<class T>
	inline void dynamic_array<T>::push(T value)
	{
		add_element(size(), value);
	}

	template<class T>
	inline T dynamic_array<T>::pop()
	{
		return T(remove_element(size() - 1));
	}

	template<typename T>
	inline void dynamic_array<T>::sort()
	{
		m_sort();
	}

	template<class T> void dynamic_array<T>::double_size()
	{
		current_size <<= 1;
		T* tmp = new T[current_size];
		for (int i = 0; i < current_count; i++)
			tmp[i] = arr[i];

		delete[] arr;
		arr = tmp;
	}

	template<class T> void dynamic_array<T>::reduce_size()
	{
		T* tmp = new T[current_size];
		if (current_size != 1) current_size >>= 1;
		else return;
		for (int i = 0; i < current_count; i++)
			tmp[i] = arr[i];

		delete[] arr;
		arr = tmp;
	}

	template<class T> size_t dynamic_array<T>::element_size()
	{
		return size_t(sizeof(T));
	}

	template<class T>
	inline void dynamic_array<T>::m_sort()
	{
		T* arra = nullptr;
		minrun = get_minrun();
		pair* runs = new pair[current_count / minrun + 1];
		int n = 0, counter = 0;
		while (n < current_count)
		{

			int i = 1;
			while (get(i + n + 1) > get(n + i) && i < current_count)
			{
				i++;
			}

			if (i < minrun)
				i = minrun;

			arra = new T[i];
			for (int j = 0; j < i; j++)
				arra[j] = get(n + j);

			n += i;
			insertion_sort(arra, i);

			runs[counter] = { i, arra };

			counter++;
		}

		pair* additional = new pair[counter];
		for (int r = 0; r < counter; r++)
		{
			additional[r] = runs[r];
		}
		insertion_sort_by_length(additional, counter);
		for (int r = 0; r < counter; r++)
			runs[r] = additional[r];

		delete[] additional;

		pair* result_array = new pair{ 0, nullptr };
		for (int f = 0; f < counter; f++)
		{
			result_array->_array = merge(result_array, &runs[f]);
		}

		delete[] arr;
		arr = result_array->_array;

		delete[] runs;
		//if(arra)
		//	delete[] arra;
	}

	template<class T>
	inline int dynamic_array<T>::get_minrun()
	{
		int r = 0;		/* ������ 1 ���� ����� ��������� ����� ����� ���� �� 1 ��������� */
		size_t n = current_count;
		while (n >= 64) {
			r |= n & 1;
			n >>= 1;
		}
		return n + r;
	}

	template<class T>
	inline void dynamic_array<T>::insertion_sort(T* arr, int n)
	{
		int i, j;
		for (i = 1; i < n; i++)
		{
			T value = arr[i];
			for (j = i - 1; j >= 0 && arr[j] > value; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = value;
		}
	}

	template<class T>
	inline void dynamic_array<T>::insertion_sort_by_length(pair* arr, int n)
	{
		int i, j;
		for (i = 1; i < n; i++)
		{
			pair value = arr[i];
			for (j = i - 1; j >= 0 && arr[j].length > value.length; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = value;
		}
	}

	template<class T>
	inline T* dynamic_array<T>::merge(pair* first, pair* second)
	{
		int f_size = first->length, s_size = second->length;
		T* tmparr = new T[f_size + s_size];

		T* left = first->_array;
		T* right = second->_array;

		if (!left)
		{
			for (int i = 0; i < s_size; i++)
				tmparr[i] = right[i];
			first->length += s_size;
			return tmparr;
		}
		int place = first->length;
		int i = 0, j = 0;
		while (i < f_size && j < s_size)
		{
			if (left[i] <= right[j])
			{
				tmparr[i + j] = left[i];
				i++;
			}
			else
			{
				tmparr[i + j] = right[j];
				j++;
			}
		}
		while (i < f_size)
		{
			tmparr[i + j] = left[i];
			i++;
		}
		while (j < s_size)
		{
			tmparr[i + j] = right[j];
			j++;
		}
		first->length += j;
		return tmparr;
	}
}

