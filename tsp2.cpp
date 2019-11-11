#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <list>
#include <iterator>
#include <sstream>


using namespace std;

double total_distance = 0;
class Point {
private:
	double x;
	double y;
public:
	Point(double x1, double y1) {
		x = x1;
		y = y1;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
};


double calculate_distance(Point point1, Point point2) {
	double distance;
	double x_difference;
	double y_difference;
	x_difference = point2.getX() - point1.getX();
	y_difference = point2.getY() - point1.getY();
	distance = sqrt(pow(x_difference, 2) + pow(y_difference, 2));
	return distance;
}

bool compare_points(Point p1, Point p2) {
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY()) {
		return true;
	}
	else {
		return false;
	}
}


void show_list(list<Point> g) {
	list <Point>::iterator it;
	double x, y;
	Point* pt;
	for (it = g.begin(); it != g.end(); ++it) {
		pt = &(*it);
		x = pt->getX();
		y = pt->getY();
		cout << " " << x << "-" << y << " \n";
	}
	cout << "\n";
}
void show_point(Point p) {
	cout << "\t" << p.getX() << ":" << p.getY() << '\n';
}

Point choose_closest(Point current, list <Point> all, list <Point> visited) {
	double min = 1000000;
	double tmp;
	Point* pt = &current;
	Point* pt0 = &current;
	Point* pt1 = &current;
	Point* ptc = &current;
	list <Point>::iterator it;
	list <Point>::iterator it1;
	bool a = true;
	int i = 0;
	for (it = all.begin(); it != all.end(); ++it) {
		a = true;
		tmp = calculate_distance(current, *it);
		//cout << '\n' << "distance: " << tmp << " POINTER curr: "; //comparing to current
		pt = &(*it);
		//show_point(*pt);
		//cout << '\n';
		if (&current == pt) {
			cout << " continue ";
			continue;
		}
		if (tmp < min && tmp != 0) { //potential min distance
			//cout << '\n' << " POINTER potential: ";
			//show_point(*pt);
			cout << '\n';
			for (it1 = visited.begin(); it1 != visited.end(); ++it1) { //checking if potential pointer was visited
				pt1 = &(*it1);
				//cout << '\n' << "comparing if v-ted ";
				//show_point(*pt1);
				//cout << "with";
				//show_point(*pt);
				if (compare_points(*pt, *pt1)) {
					//cout << " THE SAME ";
					a = false;
					break;
				}
			}
			if (a) {
				min = tmp;
				ptc = &(*it);
				//cout << " changing min to: " << min;
			}
			
		}
		i++;
	}
	total_distance = total_distance + min;
	//cout << "no of loops: " << i << " ended choosing will ret: ";
	//show_point(*ptc);
	return *ptc; //chosen pointer
}


list <Point> point_inserter() {
	list <Point> g;
	fstream myfile("test.txt");
	if (!myfile) {
		cout << "Failed to open the file.\n";
		exit(1);
	}
	string num;
	string str;
	getline(myfile, num);
	double dnum = atof(num.c_str());
	double x;
	double y;
	while (getline(myfile, str)) {

		string s1 = "";
		string s2 = "";
		int  l = str.length();
		int i = 0;
		while (i < l) {
			if (str[i] == ' ') {
				break;
			}
			i++;
		}
		i++;
		bool a = true;
		while (i < l) {
			if (str[i] == ' ') {
				a = false;
				i++;
				continue;
			}
			if (a) {
				s1 = s1 + str[i];
			}
			else {
				s2 = s2 + str[i];
			}
			i++;
		}
		istringstream iss1(s1);
		iss1 >> x;
		istringstream iss2(s2);
		iss2 >> y;
		Point point(x, y);
		g.push_back(point);
	}
	return g;
}


int main() {
	list <Point> d; //visited
	list <Point> g = point_inserter();
	int size_all = g.size();
	Point* current = &g.front();
	Point* pt;
	while (d.size() < (size_all)) {
		//cout << "\nnew loop\n";
		//cout << " main loop current at begin: ";
		//show_point(*current);
		d.push_back(*current);
		current = &choose_closest(*current, g, d);
	}
	double remain = calculate_distance(d.back(), g.front());
	total_distance += remain;
	total_distance -= 1000000;
	show_list(d);
	cout << "Total distance - " << total_distance << "\n";
	cout << "\nended";
	return 0;
}
