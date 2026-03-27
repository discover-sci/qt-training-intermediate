#include <iostream>

int main () {

  int a = 4;
  int b = 2;

  auto func1 = [a, b](){
    std::cout << "func1() -> a: " << a << " " << "b: " << b << "\n";
  };

  auto func2 = [&a, b](){
    std::cout << "func2() -> a: " << a << " " << "b: " << b << "\n";
  };

  auto func3 = [=](){
    std::cout << "func3() -> a: " << a << " " << "b: " << b << "\n";
  };

  auto func4 = [&](){
    std::cout << "func4() -> a: " << a << " " << "b: " << b << "\n";
  };


  for (int i = 0; i<5;++i) {
    func1();
    func2();
    func3();
    func4();
    a+=1;
    std::cout << "\n";
  }

  // direct call for lambda
  std::cout << [&](int c, int d) {
    std::cout << c << " " << d << "\n";
    return 404;
  } (10, 505) << "\n";

  // ****************************************************************
  // take param a from the outside into a func param
  // it always changes - simple. Capture block works differently, there you need to specify a call func5() only, no argument
  a = 1;
  auto func5 = [](int &a) {
    std::cout << a << "\n";

  };

  for (int i = 0; i<5;++i) {
    func5(a);
    a+=1;
  }



  return 0;
}
