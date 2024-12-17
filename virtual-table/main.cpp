#include <iostream>

class CA {
public:
	virtual void F1() {
		std::cout << "CA F1\n";
	}

	virtual void F2() {
		std::cout << "CA F2\n";
	}

	virtual void F3() {
		std::cout << "CA F3\n";
	}
	
	void F4() {
		std::cout << "CA F4\n";
	}

};

class CB : public CA {
public:
	virtual void F1() override {
		std::cout << "CBF1\n";
	}

	virtual void F2() override final {
		std::cout << "CB F2\n";
	}

	void F4() {
		std::cout << "CB F4\n";
	}

};

class CC : public CB {
public:
	virtual void F1() override final {
		std::cout << "CC F1\n";
	}

	void F4() {
		std::cout << "CC F4\n";
	}

};

int main() {
	CC c;
	CA* p = &c;

	p->F1();
	p->F2();
	p->F3();
	p->F4();

	return 0;
}