#include "disjointset.h"

DisjointSet::DisjointSet(int max){

	size_ = max;
	disjointSet_ = new Set*[max]();

	for (int i = 0; i < max; i++) {
		disjointSet_[i] = new Set;
	}
}

//Pushes one member into the set
bool DisjointSet::makeSet(int object) {

	if (disjointSet_[object]->front_) {
		if (disjointSet_[object]->front_->data_ == object) {
			return false;
		}
	}

	disjointSet_[object]->push_front(object);
	disjointSet_[object]->size_++;

	return true;
}

//Returns the representative of the set that this index's node is part of
int DisjointSet::findSet(int object) const{
	return disjointSet_[object]->front_->data_;
}

bool DisjointSet::unionSets(int rep1, int rep2){

	if (rep1 == rep2) {
		return true;
	}
	else if (disjointSet_[rep1]->front_->data_ != rep1 || disjointSet_[rep2]->front_->data_ != rep2) {
		return false;
	}
	else {
		//Check which set is smaller and attach the smaller set to the bigger set
		if (disjointSet_[rep1]->size_ >= disjointSet_[rep2]->size_) {
			//Rewiring the nodes to connect the sets
			disjointSet_[rep2]->front_->prev_ = disjointSet_[rep1]->back_;
			disjointSet_[rep1]->back_->next_ = disjointSet_[rep2]->front_;

			disjointSet_[rep1]->back_ = disjointSet_[rep2]->back_;

			Set::Member* tempMember = disjointSet_[rep2]->front_;
			disjointSet_[rep1]->size_ = disjointSet_[rep2]->size_ + disjointSet_[rep1]->size_;
			disjointSet_[rep2] = disjointSet_[rep1];

			//Assigning each index of the set to the new representative
			while (tempMember->next_) {
				disjointSet_[tempMember->next_->data_] = disjointSet_[rep1];
				tempMember = tempMember->next_;
			}
			return true;
		}
		else {
			//Rewiring the nodes to connect the sets
			disjointSet_[rep1]->front_->prev_ = disjointSet_[rep2]->back_;
			disjointSet_[rep2]->back_->next_ = disjointSet_[rep1]->front_;

			disjointSet_[rep2]->back_ = disjointSet_[rep1]->back_;

			Set::Member* tempMember = disjointSet_[rep1]->front_;
			disjointSet_[rep2]->size_ = disjointSet_[rep2]->size_ + disjointSet_[rep1]->size_;
			disjointSet_[rep1] = disjointSet_[rep2];

			//Assigning each index of the set to the new representative
			while (tempMember->next_) {
				disjointSet_[tempMember->next_->data_] = disjointSet_[rep2];
				tempMember = tempMember->next_;
			}
			return true;
		}
	}
}

DisjointSet::~DisjointSet(){

	if (disjointSet_) {
		bool check = false;
		for (int i = 0; i < size_; i++) {
			if (i > 0) {
				for (int j = 0; j < i; j++) {
					if (disjointSet_[i] != disjointSet_[j]) {
						check = true;
						continue;
					}
					else {
						check = false;
						break;
					}
				}
				if (check)
					delete disjointSet_[i];
			}
			else {
				delete disjointSet_[i];
			}
		}
		delete[] disjointSet_;
	}
}

//Copy constructor calls copy assignment
DisjointSet::DisjointSet(const DisjointSet& other) {		

	this->size_ = other.size_;
	this->disjointSet_ = new Set* [size_]();

	//Loop through the disjointSet
	for (int i = 0; i < size_; i++) {
		//Any case with index above 0
		if (i > 0) {
			for (int j = 0; j < i; j++) {
				if (other.disjointSet_[j]) {
					if (other.disjointSet_[j] == other.disjointSet_[i]) {
						this->disjointSet_[i] = this->disjointSet_[j];
					}
					else {
						this->disjointSet_[i] = new Set;
						this->disjointSet_[i]->push_front(other.disjointSet_[i]->front_->data_);

						if (other.disjointSet_[i]->front_->next_) {
							Set::Member* tempMember = new Set::Member(
								other.disjointSet_[i]->front_->data_,
								other.disjointSet_[i]->front_->next_,
								other.disjointSet_[i]->front_->prev_
							);
							while (tempMember) {
								if (tempMember->next_) {
									tempMember = tempMember->next_;
									this->disjointSet_[i]->front_->next_ = tempMember->next_;
								}
								else {
									tempMember = nullptr;
								}
							}
							delete tempMember;
						}
					}
				}
			}
		}
		//Copy for the case index 0
		else {
			this->disjointSet_[i] = new Set();
			this->disjointSet_[i]->push_front(other.disjointSet_[i]->front_->data_);

			if (other.disjointSet_[i]->front_->next_) {
				Set::Member* tempMember = new Set::Member(
					other.disjointSet_[i]->front_->data_,
					other.disjointSet_[i]->front_->next_,
					other.disjointSet_[i]->front_->prev_
				);
				while (tempMember) {
					if (tempMember->next_) {
						tempMember = tempMember->next_;
						this->disjointSet_[i]->front_->next_ = tempMember->next_;
					}
					else {
						tempMember = nullptr;
					}
				}
				delete tempMember;
			}
		}
	}
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other){

	if (this != &other) {
		this->size_ = other.size_;
		this->disjointSet_ = new Set * [size_]();

		//Loop through the disjointSet
		for (int i = 0; i < size_; i++) {
			//Any case with index above 0
			if (i > 0) {
				for (int j = 0; j < i; j++) {
					if (other.disjointSet_[j]) {
						if (other.disjointSet_[j] == other.disjointSet_[i]) {
							this->disjointSet_[i] = this->disjointSet_[j];
						}
						else {
							this->disjointSet_[i] = new Set;
							this->disjointSet_[i]->push_front(other.disjointSet_[i]->front_->data_);

							if (other.disjointSet_[i]->front_->next_) {
								Set::Member* tempMember = new Set::Member(
									other.disjointSet_[i]->front_->data_,
									other.disjointSet_[i]->front_->next_,
									other.disjointSet_[i]->front_->prev_
								);

								while (tempMember) {
									if (tempMember->next_) {
										tempMember = tempMember->next_;
										this->disjointSet_[i]->front_->next_ = tempMember->next_;
									}
									else {
										tempMember = nullptr;
									}
								}
								delete tempMember;
							}
						}
					}
				}
			}
			//Copy for the case index 0
			else {
				this->disjointSet_[i] = new Set();
				this->disjointSet_[i]->push_front(other.disjointSet_[i]->front_->data_);

				if (other.disjointSet_[i]->front_->next_) {
					Set::Member* tempMember = new Set::Member(
						other.disjointSet_[i]->front_->data_,
						other.disjointSet_[i]->front_->next_,
						other.disjointSet_[i]->front_->prev_
					);

					while (tempMember) {
						if (tempMember->next_) {
							tempMember = tempMember->next_;
							this->disjointSet_[i]->front_->next_ = tempMember->next_;
						}
						else {
							tempMember = nullptr;
						}
					}
					delete tempMember;
				}
			}
		}
	}
	return *this;
}

DisjointSet::DisjointSet(DisjointSet&& other){
	
	this->size_ = other.size_;
	this->disjointSet_ = other.disjointSet_;
	other.disjointSet_ = nullptr;
}

DisjointSet& DisjointSet::operator=(DisjointSet&& other){
	
	if (this != &other) {
		size_ = other.size_;
		delete[]disjointSet_;
		disjointSet_ = other.disjointSet_;
		other.disjointSet_ = nullptr;
	}
	return *this;
}

/********************
 Set class functions
*********************/

//Push one member into set
void DisjointSet::Set::push_front(const int& data) {
	
	Member* nn = new Member(data, front_, nullptr);
	
	if (front_) {
		front_->prev_ = nn;
	}
	else {
		back_ = nn;
	}
	front_ = nn;
}


DisjointSet::Set::Set() {
	
	front_ = nullptr;
	back_ = nullptr;
	size_ = 0;
}

DisjointSet::Set::~Set() {
	
	//Empty the set first
	Member* rm = front_;
	
	while (front_) {
		rm = front_;
		
		if(front_->next_)
			front_ = front_->next_;
		else {
			front_ = nullptr;
		}

		delete rm;
	}
}
