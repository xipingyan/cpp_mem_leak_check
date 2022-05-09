#include <iostream>
#include <memory>

struct Pod
{
	int x;
};

class MYCLS
{
public:
	MYCLS(/* args */) {

	}
	~MYCLS() {

	}
	std::shared_ptr<int> _x_ptr = std::make_shared<int>(0);
};

class MYCLS2
{
public:
	MYCLS2(std::shared_ptr<MYCLS> c) {
		_c = c;
	}
	std::shared_ptr<MYCLS> _c;
};

void fun1()
{
	Pod *pPod = new Pod;
	pPod = new Pod; // Oops, leaked the original pPod!
					// delete pPod;
	delete pPod;
}

void fun2()
{
	int *arr = new int[20];
	delete arr;
}

void fun3()
{
	MYCLS *myc = new MYCLS();
}

void fun4()
{
	MYCLS *myc = new MYCLS();
	std::shared_ptr<MYCLS> myc_sptr = std::shared_ptr<MYCLS>(myc);
	MYCLS2 *myc2 = new MYCLS2(myc_sptr);
	delete myc2;
}

void fun5()
{
	static MYCLS *myc = new MYCLS();
	// std::shared_ptr<MYCLS> myc_sptr = std::shared_ptr<MYCLS>(myc);
}

int main(int argc, char **argv)
{
	// fun1();
	// fun2();
	// fun3();
	// fun4();
	fun5();
	return 0;
}