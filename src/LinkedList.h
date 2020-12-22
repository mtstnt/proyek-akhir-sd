#pragma once
#include <iostream>

template <typename T>
class LinkedList
{
private:
	class Node
	{
	public:
		T data;
		Node* prev;
		Node* next;
	};

	Node* head = nullptr;
	Node* tail = nullptr;
public:
	LinkedList() {}
	~LinkedList() 
	{
		MassDelete(0, GetSize());
	}

	void Append(T data)
	{
		Node* node = new Node;
		(*node).data = data;
		(*node).prev = nullptr;
		(*node).next = nullptr;

		if (head == nullptr && tail == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			(*tail).next = node;
			(*node).prev = tail;
			tail = node;
		}
	}
	void Prepend(T data)
	{
		Node* node = new Node;
		(*node).data = data;
		(*node).prev = nullptr;
		(*node).next = nullptr;

		if (head == nullptr && tail == nullptr)
		{
			head = node;
			tail = node;
		}
		else
		{
			(*node).next = head;
			(*head).prev = node;
			head = node;
		}
	}
	T Front()
	{
		Node* node = head;
		return (*node).data;
	}
	T Get(int index)
	{
		Node* node = head;
		if (node != nullptr)
		{
			int itr = 0;
			while (itr < index)
			{
				if ((*node).next == nullptr)
				{
					break;
				}
				node = (*node).next;
				itr++;
			}
		}
		return (*node).data;
	}
	void Delete(int index)
	{
		bool deleted = false;
		Node* node = head;
		if (node == nullptr)
		{
			std::cout << "Warning! insufficient size" << std::endl;
			return;
		}
		int itr = 0;
		while (1)
		{
			//Delete
			if (itr == index)
			{
				if (node == head)
				{
					if ((*node).next != nullptr)
					{
						Node* next_node = (*node).next;
						head = next_node;
						(*next_node).prev = nullptr;

						(*node).next = nullptr;
						(*node).prev = nullptr;
						deleted = true;
						delete node;
						break;
					}
					else
					{
						head = nullptr;
						(*node).next = nullptr;
						(*node).prev = nullptr;
						deleted = true;
						delete node;
						break;
					}
				}
				else if (node == tail)
				{
					if ((*node).prev != nullptr)
					{
						Node* prev_node = (*node).prev;
						tail = prev_node;
						(*prev_node).next = nullptr;

						(*node).next = nullptr;
						(*node).prev = nullptr;
						deleted = true;
						delete node;
						break;
					}
					else
					{
						tail = nullptr;
						(*node).next = nullptr;
						(*node).prev = nullptr;
						deleted = true;
						delete node;
						break;

					}
					
				}
				else
				{
					Node* prev_node = (*node).prev;
					Node* next_node = (*node).next;

					(*prev_node).next = next_node;
					(*next_node).prev = prev_node;

					(*node).prev = nullptr;
					(*node).next = nullptr;
					deleted = true;
					delete node;
					break;
				}
			}
			if ((*node).next == nullptr)
			{
				break;
			}
			node = (*node).next;
			itr++;
		}
		if (!deleted)	//Could be Optimized so we don't have to waste O(n) try to delete an invalid Index by using var size
		{
			std::cout << "Warning! Delete Failed, Invalid Index" << std::endl;
		}
	}
	void Display()
	{
		Node* node = head;
		if (node != nullptr)
		{
			while (1)
			{
				std::cout << (*node).data << " ";
				if ((*node).next == nullptr)
				{
					break;
				}
				node = (*node).next;
			}
			std::cout << std::endl;
		}
		
	}
	int GetSize()
	{
		Node* node = head;
		if (node == nullptr)
		{
			return 0;
		}
		int itr = 1;
		while (1)
		{
			if ((*node).next == nullptr)
			{
				break;
			}
			node = (*node).next;
			itr++;
		}
		return itr;
	}

	T GetMax()
	{
		if (head == nullptr)
		{
			return -1;
		}
		T max = (*head).data;
		Node* node = head;
		while (1)
		{
			T tmp = (*node).data;
			if (tmp > max)
			{
				max = tmp;
			}
			if ((*node).next == nullptr)
			{
				break;
			}
			node = (*node).next;
		}
		return max;
	}
	T GetMin()
	{
		if (head == nullptr)
		{
			return -1;
		}
		T min = (*head).data;
		Node* node = head;
		while (1)
		{
			T tmp = (*node).data;
			if (tmp < min)
			{
				min = tmp;
			}
			if ((*node).next == nullptr)
			{
				break;
			}
			node = (*node).next;
		}
		return min;
	}

	void DeleteMax()
	{
		T data = GetMax();
		Node* node = head;
		int itr = 0;
		while (1)
		{
			if ((*node).data == data)
			{
				if ((*node).next == nullptr)
				{
					Delete(itr);
					break;
				}
				node = (*node).next;
				Delete(itr);
			}
			else
			{
				if ((*node).next == nullptr)
				{
					break;
				}
				node = (*node).next;
				itr++;
			}
		}
	}
	void DeleteMin()
	{
		T data = GetMin();
		Node* node = head;
		if (node != nullptr)
		{
			int itr = 0;
			while (1)
			{
				if ((*node).data == data)
				{
					if ((*node).next == nullptr)
					{
						Delete(itr);
						break;
					}
					node = (*node).next;
					Delete(itr);
				}
				else
				{
					if ((*node).next == nullptr)
					{
						break;
					}
					node = (*node).next;
					itr++;
				}
			}
		}
		
	}

	void MassDelete(int index, int size)
	{
		if (size < 0)
		{
			std::cout << "Invalid Size" << std::endl;
			return;
		}
		if (index + size - 1 <= GetSize() - 1)
		{
			for (int i = 0; i < size; i++)
			{
				Delete(index);
			}
		}
		else
		{
			std::cout << "Invalid Index or Size" << std::endl;
		}
	}
};

