#pragma once

#include "allocator.h"

namespace FRS {

	template <class T, class Allocator = default_allocator<T>>
	class basic_string {
	protected:
		T* m_array;
		uint32 m_length;
		uint32 m_capacity;

	public:

		typedef T* Iterator;
		typedef T* Reserve_Iterator;

		/*
		@ Operator    : =
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Nah.
		*/
		void operator = (basic_string &m_para);

		/*
		@ Method      : begin
		@ Description : Get the begin iterator of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		Iterator begin() {
			return m_array;
		}

		/*
		@ Method      : end
		@ Description : Get the end iterator of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		Iterator end() {
			return m_array + m_length;
		}

		Reserve_Iterator rbegin() {
			return m_array + m_length;
		}

		Reserve_Iterator rend() {
			return m_array;
		}

		/*
		@ Method      : front
		@ Description : Get the front element of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T front() {
			return m_array[0];
		}

		/*
		@ Method      : back
		@ Description : Get the back element of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T back() {
			return m_array[m_length - 1];
		}

		basic_string(basic_string& p_ant) {
			m_length = p_ant.m_length;
			m_capacity = p_ant.m_capacity;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			mem_copy(m_array, p_ant.m_array, m_length * sizeof(T));
			m_array[m_length] = '\0';
		}

		basic_string(const T* p_data) {
			size_t length = 0;

			while (p_data[length])
				length++;

			m_capacity = length + 5;
			m_length = length;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			mem_copy(m_array, p_data, length);
			m_array[m_length] = '\0';
		}

		basic_string(uint32 length, uint32 capacity, const T* p_data) {
			m_capacity = capacity;
			m_length = length;

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			mem_copy(m_array, p_data, length);
			m_array[m_length] = '\0';
		}

		basic_string() {
			m_array = nullptr;
			m_length = 0;
			m_capacity = 0;
		}

		~basic_string() {
			Allocator::free(m_array);
		}

		/*
		@ Operator    : []
		@ Description : Get the element at n_num of array
		@ Date        : 05/27/2017 | 7:57 AM
		@ Method      : Not baby.
		*/
		T operator [](uint32 p_num) {
			return m_array[p_num];
		};

		/*
		@ Method      : data
		@ Description : Get the data of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		T* data() {
			return m_array;
		}

		/*
		@ Method      : count
		@ Description : Get the size of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		uint32 length() {
			return m_length;
		}

		/*
		@ Method      : capacity
		@ Description : Get the capacity of array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : Not baby.
		*/
		uint32 capacity() {
			return m_capacity;
		}

		/*
		@ Method      : push_back
		@ Description : add a variable to the back of the array
		@ Date        : 05/27/2017 | 7:58 AM
		@ Method      : ----------------------------------
		Implement push_back is not hard, the core is
		set the current size-1 variable in the array
		by the parameter, if the size of arrays is
		equal or bigger than the capacity, we reserve
		it by the size plus 5.
		*/
		void push_back(T m_para) {
			if ((m_length >= m_capacity)) {
				reserve(m_capacity + 5);
			}

			m_array[m_length++] = m_para;
		};

		/*
		@ Method      : pop_back
		@ Description : delete the variable at the back of the array
		@ Date        : 05/27/2017 | 8:05 AM
		@ Method      : -------------------------------------
		Pop_back is easier. Just subtract the size by one.
		*/
		void pop_back(T m_para) {
			m_length--;
		};

		/*
		@ Method      : reserve
		@ Description : change the capacity of the
		array by reserving bits
		@ Date        : 05/27/2017 | 8:24 AM
		@ Method      : -------------------------------
		To change capacity, we create a new array,
		copy the old array to new array and replace
		it. Pretty much like swapping.
		*/
		void reserve(uint32 m_new_capacity) {
			if (m_array == nullptr) {
				m_length = 0;
				m_capacity = 0;
			}

			T*     newArray = Allocator::alloc(m_new_capacity * sizeof(T));
			uint32 newSize = m_new_capacity < m_length ? m_new_capacity : m_length;
			
			if (m_length != 0)
				mem_copy(newArray, m_array, m_length * sizeof(T));

			m_capacity = m_new_capacity;
			Allocator::free(m_array);

			m_array = Allocator::alloc(m_capacity * sizeof(T));

			m_array = newArray;
			m_array[m_length] = '\0';
		};

		/*
		@ Method      : resize
		@ Description : change the size of array
		@ Date        : 05/27/2017 | 8:26 AM
		@ Method      : -------------------
		Change the capacity of the
		array by n_num, than set the size
		by n_num
		*/
		void resize(int32 n_num) {
			reserve(n_num);
			m_length = n_num;
		};

		/*
		@ Method      : shrink_to_fit
		@ Description : change the size of array
		@ Date        : 05/27/2017 | 6:16 PM
		@ Method      : -------------------
		Change the capacity of the
		array by m_length, than set the capacity
		by m_length
		*/
		void shrink_to_fit() {
			reserve(m_length);
			m_capacity = m_length;
		}

		/*
		@ Method      : clear
		@ Description : clear the array
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Nope tbh
		*/
		void clear() {
			m_length = 0;
			m_capacity = 0;

			m_array = nullptr;
		};

		/*
		@ Method      : erase
		@ Description : erase elements from m_begin to m_end
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : move the memory from the past - end
		of the delete to the begin of the
		delete pointer. To easy understand:

		0 1 2 3 5 6

		if we want to erase the element 3 to 5,
		which means 2, 3, 5, get the number of element
		remains not delete by get end() - m_end, than move:

		0 1 |2 3 5| 6

		Remaining end() - m_end = 1

		Command:
		mem_move_c(3, 5+1, 1);

		Append resuly:

		0 1 6 3 5 6

		Delete the size by m_end - m_begin + 1

		Result:

		0 1 6
		*/
		void erase(Iterator m_begin, Iterator m_end) {
			uint32 a = end() - m_end - 1;
			mem_move_c(m_begin, m_end + 1, (end() - m_end) * sizeof(T));
			m_length -= m_end - m_begin + 1;

		}

		/*

		@ Method      : erase
		@ Description : erase elements from m_begin to m_end
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(Iterator m_begin) {
			erase(m_begin, m_begin + 1);
		}
		/*

		@ Method      : erase
		@ Description : erase elements at p_pos
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(uint32 p_pos) {
			erase(begin() + p_pos);
		}

		/*

		@ Method      : erase
		@ Description : erase elements from m_begin to m_end
		@ Date        : 05/27/2017 | 9:04 AM
		@ Method      : erase with m_end = m_begin + 1
		*/

		void erase(uint32 p_begin, uint32 p_end) {
			erase(begin() + p_begin, begin() + p_end);
		}

		/*

		@ Method      : insert
		@ Description : insert data from p_begin to p_end
		@ Date        : 06/06/2017 | 1:29 PM
		@ Method      :
		caculate if the capacity is enough, or else
		reserve it.
		Then we move the part (from p_begin to the end
		of the array) to the p_end
		Then, there will be space for the data. Parse the
		data there.
		*/

		void insert(T data, Iterator p_begin, Iterator p_end) {

			int32 t_new_size = p_end - p_begin;

			if (m_length + t_new_size >= m_capacity) {
				reserve(m_length + t_new_size + 5);
			}

			mem_move_c(p_end, p_begin, (end() - p_begin) * sizeof(T));

			Iterator t_begin = p_begin;

			for (uint32 i = 0; i < p_end - p_begin; i++) {
				*t_begin++ = data;
			}

			m_length += t_new_size;
			m_capacity = m_length + t_new_size + 5;
		}

		/*

		@ Method      : insert
		@ Description : insert data at p_pos
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, Iterator p_pos) {
			insert(data, p_pos, p_pos + 1);
		}

		/*

		@ Method      : insert
		@ Description : insert data from p_begin to p_end
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, uint32 p_begin, uint32 p_end) {
			insert(data, begin() + p_begin, begin() + p_end);
		}

		/*

		@ Method      : insert
		@ Description : insert data at p_pos
		@ Date        : 06/06/2017 | 1:31 PM
		@ Method      :
		Wrapper
		*/
		void insert(T data, uint32 p_pos) {
			insert(data, p_pos);
		}

		/*
		@ Method      : is_empty
		@ Description : check if the array is empty
		@ Date        : 05/27/2017 | 7:52 AM
		@ Method      : Not really. Only checks if size is 0
		*/
		bool is_empty() {
			return (m_length == 0);
		}

		friend basic_string<T> operator + (basic_string<T>& m_para1, basic_string<T>& m_para2) {
			
			auto t_length = m_para1.length() + m_para2.length();
			auto t_capacity = m_para1.capacity() + m_para2.capacity() + 7;
			T* t_array = Allocator::alloc(t_capacity * sizeof(T));

			mem_copy(t_array, m_para1.data(), m_para1.length() * sizeof(T));
			mem_move_c(t_array + m_para1.length(), m_para2.data(), m_para2.length() * sizeof(T));

			t_array[t_length] = '\0';

			return basic_string<T>(t_length, t_capacity, t_array);
		}

		void operator += (basic_string& m_para) {
			
			uint32 t_new_size = m_para.length() + m_length;

			if (t_new_size >= m_capacity)
				reserve(t_new_size + 7);

			mem_move_c(m_array + m_length, m_para.m_array, m_para.m_length * sizeof(T));

			m_length = t_new_size;
			m_capacity = t_new_size + 7;
		}

		void operator += (const T* m_para) {
			*this += string(m_para);
		};

		uint32 find(basic_string& p_find) {
			basic_string t_merge = p_find + basic_string("|") + *this;

			for (uint32_t i = 0; i < m_length; i++) {
				uint32 t_patternLength = 0;

				uint32_t t_up = 0;

				for (uint32_t j = i; j < m_length; j++, t_up++) {

					if (t_merge.m_array[t_up] == t_merge.m_array[j]) {
						++t_patternLength;
					}
					else 
						break;
				}

				if (t_patternLength == p_find.m_length) {
					return i - p_find.m_length - 1;
				}

			}

			return -1;
		}

	};

	template <typename T, typename Allocator = default_allocator<T>>
	void basic_string<T, Allocator>::operator = (basic_string &m_para) {
		Allocator::free(m_array);

		m_length = m_para.m_length;
		m_capacity = m_para.m_capacity;

		m_array = Allocator::alloc(m_capacity * sizeof(T));

		mem_copy(m_array, m_para.m_array, m_length * sizeof(T));

	}

	typedef basic_string<char> string;

}