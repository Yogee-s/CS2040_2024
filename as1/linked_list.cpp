#include "linked_list.h"
#include <stdexcept>

// Returns the value at head
int List::head() {
	// TODO: Implement this method
	if (m_head == nullptr) {
		throw std::out_of_range("List is empty");
	}
	return m_head->element;
}

// Checks whether the container is empty
bool List::empty() const {
	// TODO: Implement this method
	return (m_size == 0);
}

// Returns the number of elements
size_t List::size() const {
	// TODO: Implement this method
	return m_size;
}

// Inserts an element to the head
void List::push_head(int element) {
	// TODO: Implement this method
	Node* new_node = new Node(element, m_head);
	m_head = new_node;
	m_size += 1;
}

// Removes the head element
int List::pop_head() {
	// TODO: Implement this method
	if (m_head == nullptr) {
		throw std::out_of_range("List is empty");
	}
	Node* temp = m_head->next;
	int head_value = m_head->element;
	Node* remove_head = m_head;
	m_head = temp;
	m_size -= 1;
	free(remove_head);
	return head_value;
}

// Checks whether the container contains the specified element
bool List::contains(int element) const {
	// TODO: Implement this method
	Node* pNode = m_head;
	while (pNode != nullptr) {
		if (pNode->element == element) {
			return true;
		}
		pNode = pNode->next;
	}
	return false;
}

// Returns a std::string equivalent of the container
std::string List::to_string() const {
	// TODO: Implement this method
	std::string result;
	if (m_head == nullptr) {
		return "{}";
	}
	else {
		Node* pNode = m_head;
		result += "{";
		while (pNode->next != nullptr) {
			result += std::to_string(pNode->element);
			result += ", ";
			pNode = pNode->next;
		}
		result += std::to_string(pNode->element);
		result += '}';

		return result;
	}
}
