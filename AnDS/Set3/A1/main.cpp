#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

struct Circle {
    double x, y, r;

    Circle(double xp, double yp, double rp) : x(xp), y(yp), r(rp) {}

    friend std::istream& operator>>(std::istream& is, Circle& c);
    friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};

std::istream& operator>>(std::istream& is, Circle& c) {
    is >> c.x >> c.y >> c.r;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << c.x << ' ' << c.y << ' ' << c.r;
    return os;
}

class Annealing {
public:
    Annealing(double min_x, double max_x, double min_y, double max_y) : min_x(min_x), max_x(max_x), min_y(min_y), max_y(max_y), rnd(rd()), dist_x(min_x, max_x), dist_y(min_y, max_y) {}

    double solve(Circle a, Circle b, Circle c, int num_of_points) {
        double in = 0;
        for (int i = 0; i < num_of_points; i++) {
            double x = dist_x(rnd);
            double y = dist_y(rnd);
            if (is_in_circle(x, y, a) && is_in_circle(x, y, b) && is_in_circle(x, y, c)) {
                in++;
            }
        }
        return (max_x - min_x) * (max_y - min_y) * (in / num_of_points);
    }

private:
    bool is_in_circle(double x, double y, Circle c) {
        return (x - c.x) * (x - c.x) + (y - c.y) * (y -c.y) <= c.r * c.r;
    }

private:
    std::random_device rd;
    std::mt19937 rnd;
    std::uniform_real_distribution<double> dist_x;
    std::uniform_real_distribution<double> dist_y;

    double min_x, max_x, min_y, max_y;
};

int main() {
    std::ofstream csvAnnealing1("annealing_method_1.csv");
    std::ofstream csvAnnealing2("annealing_method_2.csv");
    csvAnnealing1 << "num_of_points,area" << std::endl;
    csvAnnealing2 << "num_of_points,area" << std::endl;

    Circle a(1, 1, 1);
    Circle b(1.5, 2, sqrt(5) / 2);
    Circle c(2, 1.5, sqrt(5) / 2);

    double min_x, max_x, min_y, max_y;

    // Annealing method 1 - big area
    min_x = std::min({a.x - a.r, b.x - b.r, c.x - c.r});
    max_x = std::max({a.x + a.r, b.x + b.r, c.x + c.r});
    min_y = std::min({a.y - a.r, b.y - b.r, c.y - c.r});
    max_y = std::max({a.y + a.r, b.y + b.r, c.y + c.r});
    for (int num_of_points = 100; num_of_points <= 100000; num_of_points += 500) {
        Annealing annealing(min_x, max_x, min_y, max_y);
        double area = annealing.solve(a, b, c, num_of_points);
        csvAnnealing1 << num_of_points << ',' << area << std::endl;
//        std::cout << num_of_points << ' ' << area << std::endl;
    }

    // Annealing method 2 - local area
    std::cout << a << ' ' << b << ' ' << c << std::endl;
    min_x = c.x - c.r;
    min_y = b.y - b.r;
    max_x = a.x + a.r;
    max_y = a.y + a.r;
    std::cout << min_x << ' ' << max_x << ' ' << min_y << ' ' << max_y << std::endl;
    for (int num_of_points = 100; num_of_points <= 1000000; num_of_points += 500) {
        Annealing annealing(min_x, max_x, min_y, max_y);
        double area = annealing.solve(a, b, c, num_of_points);
        csvAnnealing2 << num_of_points << ',' << area << std::endl;
    }

    csvAnnealing1.close();
    csvAnnealing2.close();
    return 0;
}
