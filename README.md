# CrossRoads

This project simulates a traffic light system for two roads, where cars with corresponding directions and passing times are managed by separate threads using std::jthread. 
The traffic light threads alternate between green states, allowing cars to pass based on their directions, until all cars have cleared the roads.

## trafficLight function

```
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
```

This function controls a traffic light on a road. It continuously checks for cars waiting to pass. When the light is green, it lets cars pass based on their direction and the road's conditions. It prints messages for passing cars and updates the lists of cars, directions, and arrival times accordingly. The loop continues until all cars have passed.
