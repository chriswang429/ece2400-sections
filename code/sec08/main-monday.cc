#include "vector-monday.h"
#include <cstdlib>
#include <iostream>

int main() {
  
  vector_t<float> vec;
  
  vec.resize(3);
  vec[0] = 1.5;
  vec[1] = 2.2;
  vec[2] = 42.4;
  
  vector_t<float> vec2;
  vec2.resize(2);
  vec2[0] = 0;
  vec2[1] = 11.11;
  
  vec + vec2;
  
  //std::cout << vec << std::endl;

  vector_t<foo> vec3;
  vec3.resize(1);
  foo f;
  
  vec3[0] = f;
  
  //std::cout << vec3;
  
  vector_t<vector_t<float>> vecv;
  
  vecv.resize(2);
  
  vecv[0] = vec;
  vecv[1] = vec2;
  
  std::cout << vecv << std::endl;
  
  /*vec.resize(5);
  vector_t<int> vec2 = vec;
  vec.at(4) = 5;
  printf("%d\n", vec[4]);
  vec2[4] = 1000;
  printf("%d\n", vec2.at(4));
  std::cout << vec[4] << std::endl;
  
  vector_t<int> vec3;
  vec3 = vec2;
  
  try{
    std::cout << vec.at(4) << std::endl;
    std::cout << vec2[4] << std::endl;
  } catch (std::out_of_range& e) {
    std::cout << "Out of range: " << e.what() << std::endl;
  } catch (std::bad_alloc& e) {
    std::cout << "Bad alloc: " << e.what() << std::endl;
  }
  return 0;*/
}
