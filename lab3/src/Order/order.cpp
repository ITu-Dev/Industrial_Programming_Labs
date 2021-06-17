#include <string>
#include <list>

#include "order.hpp"
#include "../utilies.hpp"
#include "../Transport/transport.hpp"
#include "../Track/track.hpp"

using std::string;
using std::list;

Order::Order() {
	cost = 0;
	volume = 0;
	start_point = "";
	finish_point = "";
	track = Track();
	type = Type::Economy;
}

Order::Order(Type deliv, string start_p, string finish_p, int vol) {
	start_point = start_p;
	finish_point = finish_p;
	type = deliv;
	track = best(start_p, finish_p, deliv, vol);
	cost = track.get_cost();
	volume = vol;
}

int Order::decr(string str)
{
	for (auto it = Utilies::towns.begin(); it != Utilies::towns.end(); it++)
	{
		if (str._Equal((*it).first))
			return (*it).second;
	}
	return -1;
}

int** Order::matrix_upd(Type type)
{
	int** matrix = new int* [16];
	for (int i = 0; i < 16; i++)
	{
		matrix[i] = new int[16];
		for (int j = 0; j < 16; j++)
		{
			matrix[i][j] = Utilies::matrix_dist(i, j);
		}
	}
	switch (type)
	{
	case Economy:
		for (int i = 0; i < 16; i++)
		{
			if (Utilies::points[i].find("TS"))
				for (int j = 0; j < 16; j++)
					matrix[i][j] = 99999;
		}
	case Standart:
		for (int i = 0; i < 16; i++)
		{
			if (Utilies::points[i].find("AP"))
				for (int j = 0; j < 16; j++)
					matrix[i][j] = 99999;
		}
	case Turbo:
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
				if (matrix[i][j] == 0)
					matrix[i][j] = 99999;
		}
	}
	return matrix;
}

int* Order::optim(int** arr, int begin_point, int end_point)
{
	int* d = new int[16];
	int* v = new int[16];
	int temp, min_index, min;
	int begin_index = begin_point;

	for (int i = 0; i < 16; i++)
	{
		d[i] = 99999;
		v[i] = 1;
	}
	d[begin_index] = 0;

	do {
		min_index = 99999;
		min = 99999;
		for (int i = 0; i < 16; i++)
		{
			if ((v[i] == 1) && (d[i] < min))
			{
				min = d[i];
				min_index = i;
			}
		}

		if (min_index != 99999)
		{
			for (int i = 0; i < 16; i++)
			{
				if (arr[min_index][i] > 0)
				{
					temp = min + arr[min_index][i];
					if (temp < d[i])
					{
						d[i] = temp;
					}
				}
			}
			v[min_index] = 0;
		}
	} while (min_index < 99999);

	int* ver = new int[16];
	int end = end_point;
	ver[0] = end;
	int k = 1;
	int weight = d[end];

	while (end != begin_index)
	{
		for (int i = 0; i < 16; i++)
			if (arr[end][i] != 0)
			{
				int temp = weight - arr[end][i];
				if (temp == d[i])
				{
					weight = temp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
	}
	for (int i = 0; i < k / 2; i++)
		std::swap(ver[i], ver[k - 1 - i]);
	delete[] d, v;
	return ver;
}

Track Order::best(string start_p, string finish_p, Type deliv, int volume) {
	int start = decr(start_p);
	int finish = decr(finish_p);
	int** mat = new int* [16];
	for (int i = 0; i < 16; i++)
		mat[i] = new int[16];
	mat = matrix_upd(deliv);

	int* path = new int[16];
	for (int i = 0; i < 16; i++)
		path[i] = -1;
	path = optim(mat, start, finish);

	int count = 0;
	for (int i = 0; i < 16; i++) {
		if (path[i] != -1)
			count++;
		else
			break;
	}

	switch (count) {
	case 1: {
		Car car1 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[0]]))
				car1 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[0], path[1]]);
		}

		list<Transport> c = { car1 };
		Track track = Track(c, volume);
		return track;
	}

	case 3: {
		Car car1 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[0]]))
				car1 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[0], path[1]]);
		}

		Car car2 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[2]]))
				car2 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[2]][path[3]]);
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		Track track = Track();

		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[1]]) && (Utilies::points[path[1]]).find("TS")) {
				train1 = Train(Utilies::table_cost[(*it).second * 3 + 1], Utilies::matrix_dist[path[1]][path[2]]);

				list<Transport> v = { car1, car2, train1 };
				track = Track(v, volume);
			}

			if ((*it).first.find(Utilies::points[path[1]]) && (Utilies::points[path[1]]).find("AP")) {
				plane1 = Plane(Utilies::table_cost[(*it).second * 3], Utilies::matrix_dist[path[1]][path[2]]);

				list<Transport> v = { car1, car2, plane1 };
				track = Track(v, volume);
			}
		}
		return track;
	}

	case 5: {
		Car car1 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[0]]))
				car1 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[0]][path[1]]);
		}

		Train train1 = Train();
		Plane plane1 = Plane();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[1]]) && (Utilies::points[path[1]]).find("TS")) {
				train1 = Train(Utilies::table_cost[(*it).second * 3 + 1], Utilies::matrix_dist[path[1]][path[2]]);
			}
			if ((*it).first.find(Utilies::points[path[1]]) && (Utilies::points[path[1]]).find("AP")) {
				plane1 = Plane(Utilies::table_cost[(*it).second * 3], Utilies::matrix_dist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++) {
			if ((*it).first.find(Utilies::points[path[2]])) {
				car2 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[2]][path[3]]);
			}
		}

		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[3]]) && (Utilies::points[path[3]]).find("AP"))
			{
				plane1 = Plane(Utilies::table_cost[(*it).second * 3], Utilies::matrix_dist[path[3]][path[4]]);
			}
			if ((*it).first.find(Utilies::points[path[3]]) && (Utilies::points[path[3]]).find("TS"))
			{
				train1 = Train(Utilies::table_cost[(*it).second * 3 + 1], Utilies::matrix_dist[path[3]][path[4]));
			}
		}

		Car car3 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[4]]))
			{
				car3 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[4]][path[5]]);
			}
		}

		list<Transport> v = { car1, car2, car3, train1, plane1 };
		Track track = Track(v, volume);
		return track;
	}

	case 7:
	{
		Car car1 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[0]]))
			{
				car1 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[0]][path[1]]);
			}
		}

		Train train1 = Train();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[1]]))
			{
				train1 = Train(Utilies::table_cost[(*it).second * 3 + 1], Utilies::matrix_dist[path[1]][path[2]]);
			}
		}

		Car car2 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[2]]))
			{
				car2 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[2]][path[3]]);
			}
		}

		Plane plane1 = Plane();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[3]]))
			{
				plane1 = Plane(Utilies::table_cost[(*it).second * 3], Utilies::matrix_dist[path[3]][path[4]]);
			}
		}

		Car car3 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[4]]))
			{
				car3 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[4]][path[5]]);
			}
		}

		Train train2 = Train();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[5]]))
			{
				train2 = Train(Utilies::table_cost[(*it).second * 3 + 1], Utilies::matrix_dist[path[5]][path[6]]);
			}
		}

		Car car4 = Car();
		for (auto it = Utilies::table.begin(); it != Utilies::table.end(); it++)
		{
			if ((*it).first.find(Utilies::points[path[6]]))
			{
				car4 = Car(Utilies::table_cost[(*it).second * 3 + 2], Utilies::matrix_dist[path[6]][path[7]]);
			}
		}

		list<Transport> v = { car1, car2, car3, car4, train1, train2, plane1 };
		Track track = Track(v, volume);
		return track;
	}
	}
}
