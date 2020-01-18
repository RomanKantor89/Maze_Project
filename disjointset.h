/*************************************/
/*                                   */
/* V 1.0.1: removed const on returns */
/*                                   */
/*************************************/



class DisjointSet {
	class Set {
		friend class DisjointSet;
		struct Member {
			int data_;
			Member* next_;
			Member* prev_;
			Member(const int& data = int{}, Member* next = nullptr, Member* prev = nullptr) {
				data_ = data;
				next_ = next;
				prev_ = prev;
			}
		};
		Member* front_;
		Member* back_;
		int size_;
	public:
		Set();
		void push_front(const int& data);
		~Set();
	};
	
	Set** disjointSet_ = nullptr;
	int size_ = 0;

public:

	//constructor
	DisjointSet(int max);

	//object is the only member of the set, generate index with hashfunction
	bool makeSet(int object);

	//finds the set that has the member provided in the parameter
	int findSet(int object) const;

	//combines 2 sets into one and picks the first node of rep1 as representative
	bool unionSets(int rep1, int rep2);

	//destructor
	~DisjointSet();

	//copy constructor
	DisjointSet(const DisjointSet& other);

	//assignment operator
	DisjointSet& operator=(const DisjointSet& other);

	//move constructor
	DisjointSet(DisjointSet&& other);

	//move assignment operator
	DisjointSet& operator=(DisjointSet&& other);

	//find and return size of set at first index
	int firstSetSize() const {
		return disjointSet_[0]->size_;
	}
};

