#include "pch.h"
#include <iostream>
#include <string>
#include <limits>
#include <stdarg.h>
#include <type_traits>
#include <xtr1common>

using namespace std;

struct Node {
public:
	template<typename... Ts>
	using StringType = typename enable_if<conjunction<is_convertible<Ts, string>...>::value>::type;
private:
	Node* m_first;
	static void CreateNextNode(Node* node) {

	}

	static Node* CreateNextNode(Node* node, string first) {
		Node* newNode = new Node(first);
		node->m_next = newNode;
		return newNode;
	}

	template<typename... Ts, typename = StringType<Ts...>>
	static void CreateNextNode(Node* node, string first, Ts... arguments) {
		node = CreateNextNode(node, first);
		CreateNextNode(node, arguments...);
	}

	string imprNext() {
		string text = "," + m_data;
		if (m_next) {
			text += m_next->imprNext();
		}
		return text;
	}
public:
	string m_data;
	Node* m_next;
	Node* getFirst() {
		return m_first;
	}

	Node* setFirst(Node* node = nullptr) {
		if (!node) {
			m_first = this;
		}
		else {
			m_first = node;
		}
		if (m_next) {
			m_next->setFirst(m_first);
		}
		return m_first;
	}

	Node(string data, Node* next = nullptr) {
		m_data = data;
		m_next = next;
	}

	template<typename... Ts, typename = StringType<Ts...>>
	static Node* CreateNodes(string first, Ts... arguments) {
		Node* node = new Node(first);
		CreateNextNode(node, arguments...);
		return node->setFirst();
	}

	string impr() {
		string text = "{" + m_data;
		if (m_next) {
			text += m_next->imprNext();
		}
		return text + "}";
	}

	Node* reverse(Node* start = nullptr) {
		Node* current = m_first;
		Node* next = nullptr;
		Node* previous = nullptr;
		Node* befor = nullptr;
		while (current != nullptr) {
			if (current == start && previous) {
				befor = previous;
			}
			next = current->m_next;
			if (befor || !start || start == m_first) {
				current->m_next = previous;
			}
			previous = current;
			current = next;
		}
		if (befor) {
			if (befor->m_next) {
				befor->m_next->m_next = nullptr;
			}
			befor->m_next = previous;
		}
		if (!start || start == m_first) {
			return previous->setFirst();
		}
		else {
			return m_first;
		}
	}

	Node* reverse(string data = "") {
		Node* current = m_first;
		Node* next = nullptr;
		Node* previous = nullptr;
		Node* befor = nullptr;
		while (current != nullptr) {
			if (current->m_data == data && previous) {
				befor = previous;
			}
			next = current->m_next;
			if (befor || data == "" || data == m_first->m_data) {
				current->m_next = previous;
			}
			previous = current;
			current = next;
		}
		if (befor) {
			if (befor->m_next) {
				befor->m_next->m_next = nullptr;
			}
			befor->m_next = previous;
		}
		if (data == "" || (m_first && data == m_first->m_data)) {
			return previous->setFirst();
		}
		else {
			return m_first;
		}
	}

	~Node() {
		delete m_next;
	}
};

int main()
{
	Node* mainNode = Node::CreateNodes("Hola", "Pepe", "Juan", "Pedro")->reverse("Pepe");
	cout << mainNode->impr() << "\n";
	Node* secondNode = Node::CreateNodes("1", "2", "3", "4", "5", "6", "7")->reverse("3");
	cout << secondNode->impr() << "\n";
	delete mainNode;
}