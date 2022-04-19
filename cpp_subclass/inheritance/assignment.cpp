#include<iostream>

class ball {
protected:
	int volume;
public:
	void set_volume(int val) {
		volume = val;
	}
};

class basketball : public ball {
public:
	basketball() 
		:weight(0)
	{
		std::cout << "this is a basketball\n";
	}
	void set_weight(int val) {
		weight = val;
	}
	void show_both() {
		std::cout << "weight: " << weight << std::endl;
		std::cout << "volume: " << volume << std::endl;
	}
private:
	int weight;
};

int main() {
	basketball a;
	a.set_volume(100);
	a.set_weight(50);
	a.show_both();
}
