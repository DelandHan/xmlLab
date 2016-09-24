#pragma once

namespace tree
{
	template<class T>
	class Node
	{
	private:
		T m_Value;

		Node<T> *m_Previous, *m_Next;
		Node<T> *m_Parent, *m_FirstChild, *m_LastChild;

	public:
		//init
		Node() :
			m_Previous(nullptr), m_Next(nullptr),
			m_Parent(nullptr), m_FirstChild(nullptr), m_LastChild(nullptr)
		{}
		~Node() {
			Node<T>* node = m_FirstChild, *temp;

			while (node)
			{
				temp = node; node = node->getNext();
				delete temp;
			}

			removeMe();
		}

		//cloneNode
		Node<T>* clone() {
			Node<T> *node = new Node<T>, *temp = this->m_FirstChild;
			node->m_Value = this->m_Value;
			while (temp) {
				node->append(temp->clone());
				temp = temp->m_Next;
			}
			return node;
		}

		//getData
		T& getValue() { return m_Value; }
		const T& getValue() const { return m_Value; }

		//get parent node
		Node<T>* getParent() const { return m_Parent; }
		//get previous node
		Node<T>* getPrevious() const { return m_Previous; }
		//get next node
		Node<T>* getNext() const { return m_Next; }
		//get 1st child;
		Node<T>* getFirstChild() const { return m_FirstChild; }
		//get last child;
		Node<T>* getLastChild() const { return m_LastChild; }
		//get next by list
		Node<T>* getNextByChain(bool checkChild = true) const {
			Node<T> * pNode = nullptr;
			if(checkChild) pNode = this->getFirstChild();
			if (pNode == nullptr) {
				pNode = const_cast<Node<T> *>(this); //for const usage
				while (pNode->getNext() == nullptr) {
					if (pNode->getParent() == nullptr) return nullptr;
					else pNode = pNode->getParent();
				}
				pNode = pNode->getNext();
			}
			return pNode;
		}

		Node<T>* getPreviousByChain(bool checkChild = true) {
			Node<T> * pNode = this->getPrevious();
			if (pNode == nullptr) return this->getParent();
			if (pNode->getLastChild() && checkChild) return pNode->getLastChild();
			return pNode;
		}

		//add neighbour
		void insert(Node<T>* neighbour, bool isNext)
		{
			//if it is not individual, return
			if (neighbour->m_Next || neighbour->m_Previous || neighbour->m_Parent) return;
			if (isNext)
			{//insert the node to next.
			 //configure neighbour first.
				neighbour->m_Previous = this;
				neighbour->m_Next = m_Next;

				if (m_Next != nullptr)
				{
					m_Next->m_Previous = neighbour;
				}
				else
				{
					if (m_Parent)
					{
						if (m_Parent->m_LastChild == this)
						{
							m_Parent->m_LastChild = neighbour;
						}
					}
				}
				m_Next = neighbour;
			}
			else
			{//insert the node to previous
			 //configure neighbour first
				neighbour->m_Next = this;
				neighbour->m_Previous = m_Previous;
				if (m_Previous != nullptr)
				{
					m_Previous->m_Next = neighbour;
				}
				else
				{
					if (m_Parent)
					{
						if (m_Parent->m_FirstChild == this)
						{
							m_Parent->m_FirstChild = neighbour;
						}
					}
				}
				m_Previous = neighbour;
			}
			neighbour->m_Parent = this->m_Parent;
		}

		//add child in the end
		void append(Node<T>* child)
		{
			if (child->m_Parent || child->m_Previous || child->m_Next) return;
			if (m_FirstChild == nullptr && m_LastChild == nullptr)
			{
				m_FirstChild = child; m_LastChild = child;
				child->m_Parent = this;
				return;
			}
			else
			{
				m_LastChild->insert(child, true);
			}
		}
		void removeMe()
		{
			if (m_Parent)
			{
				if (m_Parent->m_FirstChild == this) 	m_Parent->m_FirstChild = this->m_Next;
				if (m_Parent->m_LastChild == this) m_Parent->m_LastChild = this->m_Previous;
			}

			if (m_Previous != nullptr) m_Previous->m_Next = m_Next;
			if (m_Next != nullptr) m_Next->m_Previous = m_Previous;

			m_Previous = nullptr;
			m_Next = nullptr;
			m_Parent = nullptr;
		}

	};
}
