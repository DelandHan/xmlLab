#pragma once
#include <string>

namespace xml
{
	enum NodeType
	{
		GENERAL_NODE,
		ELEMENT_NODE,
		ATTRIBUTE_NODE,
		TEXT_NODE,
		CDATA_SECTION_NODE,
		ENTITY_REFERENCE_NODE,
		ENTITY_NODE,
		PROCESSING_INSTRUCTION_NODE,
		COMMENT_NODE,
		DOCUMENT_NODE,
		DOCUMENT_TYPE_NODE,
		DOCUMENT_FRAGMENT_NODE,
		NOTATION_NODE,
	};

	enum Result
	{
		SUCCESS,
		FAILURE,
		CONTINUE,
		DONE
	};

	class XMLNode
	{
	public:
		class AttNode
		{
		public:
			inline const std::string& getKey() const { return theKey; }
			inline const std::string& getValue() const { return theValue; }
		private:
			friend class XMLNode;
			AttNode();
			~AttNode();

			void clear();
			AttNode* insert(const std::string &key, const std::string &value);

			std::string theKey;
			std::string theValue;
			AttNode *theNext, *thePrev;
		};

		XMLNode();
		~XMLNode();

		//tree
		//get parent node
		XMLNode* getParent() const { return theParent; }
		//get previous node
		XMLNode* getPrevious() const { return thePrevious; }
		//get next node
		XMLNode* getNext() const { return theNext; }
		//get 1st child;
		XMLNode* getFirstChild() const { return theFirstChild; }
		//get last child;
		XMLNode* getLastChild() const { return theLastChild; }
		//clone node. To do: need further checking
		XMLNode * clone();
		//get next by list
		XMLNode* getNextByChain(bool checkChild = true) const;
		XMLNode* getPreviousByChain(bool checkChild = true);

		//add neighbour
		void insert(XMLNode* neighbour, bool isNext);

		//add child in the end
		void append(XMLNode* child);

		//remove this node from the tree
		void removeMe();

		/////////////////

		//clone
		XMLNode& operator=(const XMLNode& other);

		//The node's type
		NodeType getType() const { return theType; }
		//Change node to another type
		void convertType(NodeType type);

		//Get the Name or the Value of the Node
		const std::string & getString() const { return theString; }
		//Set the Name or the Value of the Node
		void setString(const char* source, size_t count, size_t off = null);
		inline void setString(const std::string &str) { setString(str.c_str(), str.size()); }

		//Get the Attribute
		std::string getAttribute(const std::string &key) const;
		const AttNode* getAttribute(const AttNode * node) const;
		//Set the Attribute
		void setAttribute(const std::string & key, const std::string & value);
		//Remove an Attribute
		void removeAttribute(const std::string & key);

		//define -1 for usage
		static const size_t null = -1;

		//verify string
		Result verifyString(const char* source, size_t count);
		//generally verify string
		static Result verifyString(const char* source, size_t count, NodeType type);

	private:
		std::string theString;
		NodeType theType;
		AttNode* theAtt;

		//tree
		XMLNode *thePrevious, *theNext, *theParent, *theFirstChild, *theLastChild;

	};



}