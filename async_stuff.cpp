/**
    @author [mst]
    @brief  cpp multithreading basics and experiments


    gains:
    -basic futures/promises


    @version 0.1 2023.05
*/

////////////////// LIBS
#include <iostream> // usage of console prints
#include <vector>
#include <future>   // usage of futures, promises
// #include <thread>

using namespace std;

////////////////// DECL_IMPL

void product(std::promise<int> &&intPromise, int a, int b) {
    intPromise.set_value(a * b);
}

struct Div {

    void operator()(std::promise<int> &&intPromise, int a, int b) const
    {
        intPromise.set_value(a / b);
    }
};

////////////////// DRIVER
int main() {

    int a = 20;
    int b = 10;

    std::cout << std::endl;

    // define the promises
    std::promise<int> prodPromise;
    std::promise<int> divPromise;

    // get the futures
    std::future<int> prodResult = prodPromise.get_future();
    std::future<int> divResult = divPromise.get_future();

    // calculate the result in a separate thread
    std::thread prodThread(product, std::move(prodPromise), a, b);
    Div div;
    std::thread divThread(div, std::move(divPromise), a, b);

    // get the result
    std::cout << "20*10= " << prodResult.get() << std::endl;
    std::cout << "20/10= " << divResult.get() << std::endl;

    prodThread.join();
    divThread.join();

    std::cout << std::endl;
    return 0;
}
