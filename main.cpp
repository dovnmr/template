//
//  main.cpp
//  tmp
//
//  Created by Dov Nimratz on 10.10.2020.
//

#include <iostream>
#include <vector>
#include <list>

template <int P>
struct foo{
    static const int value = P * foo<P-1>::value;
};
template<>
struct foo<0>{
    static const int value = 1;
};

template<class T>
std::enable_if_t<std::is_integral<T>::value, void>
print(const T &t){
    for(char index = sizeof(T); index >0; --index){
        unsigned char p = (index-1)*8;
        unsigned char sh = (t>>(p));
        std::cout<<static_cast<int>(sh);
        if (index > 1) std::cout<<".";
    }
    std::cout<<std::endl;
};
template<typename T, typename...Args>
struct is_equal : std::false_type{};

template<typename T>
struct is_equal<T> : std::false_type {};

template<typename T, typename...Args>
struct is_equal<T, T, Args...> : std::true_type{};

template <typename T, typename U, typename...Args>
struct is_equal<T, U, Args...> : is_equal<T, Args...> {};

template<typename T>
struct is_string : is_equal<T, std::string>{};

template<typename T>
struct is_vector : is_equal<T, std::vector<typename T::value_type>, std::list<typename T::value_type>>{};

template<typename T>
struct is_list : is_equal<T, std::list<typename T::value_type>>{};

template<class T>
std::enable_if_t<is_string<T>::value, void>
print(const T &t){
    std::cout<<t<<std::endl;
}
template<class T>
std::enable_if_t<is_vector<T>::value, void>
print(const T &t){
    auto last = t.end();
    --last;
    for(auto it = t.begin(); it !=t.end(); ++it){
        std::cout<<*it;
        if(it != last) std::cout<<".";
    }
    std::cout<<std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    std::cout << foo<10>::value << std::endl;
//    long x = 8875824491850138409;
//    std::string x = "1234567.11";
//    std::vector<short> x = {1,2,3,4,5};
    std::list<int> x = {1,2,3,4,5};
    print(x);
    
    return 0;
}
