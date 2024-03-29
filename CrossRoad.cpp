#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <windows.h>

std::mutex tlm;

void trafficLight(std::vector<int>& cars, std::vector<int>& directions, std::vector<int>& time, const std::string& road_name)
{
	while (true)
	{
		Sleep(1000);
		std::lock_guard<std::mutex> guard(tlm);
		if (cars.empty())
			break;
		
		std::cout << "Traffic light on " << road_name << " is green" << std::endl;
		while (!cars.empty())
		{
			if ((road_name == "road A" && directions.front() <= 2) || (road_name == "road B" && directions.front() > 2))
			{
				std::cout << "Car " << cars.front() << " passed in direction " << directions.front()
						  << " at time " << time.front() << std::endl;
				cars.erase(cars.begin());
				directions.erase(directions.begin());
				time.erase(time.begin());
			}
			else
			{
				break;
			}
		}
	}
}

int main()
{
	std::vector<int> cars = {1, 3, 5, 2, 4};
	std::vector<int> directions = {2, 1, 2, 4, 3};
	std::vector<int> time = {10, 20, 30, 40, 40};
	
	std::jthread thread_A(trafficLight, std::ref(cars), std::ref(directions), std::ref(time), "road A");
	std::jthread thread_B(trafficLight, std::ref(cars), std::ref(directions), std::ref(time), "road B");
	
	return 0;
}
