#include <future>
#include <iostream>
/*
    A       B        C


    option 1: one after the other.Always complete one
              thing before starting the next task.

              name: single thread technique
/////////////////////////////////////////////////////////////////////
    option 2: I will complete all tasks in such a way that I
              "practically start all of them at the same time"
              but keep juggling them based on some criteria.

              name: Multi-threaded approach
//////////////////////////////////////////////////////////////////////////
    option 3: map number of tasks amongst number of available "workers"

            name: Parallel execution
////////////////////////////////////////////////////////////////////////////////
    option 4: Start a task. Either delegate it to another worker OR do it
            yourself after some time.

    If someone else is doing a task, monitor it, wait for their work to be
    done, task follow-up actions accordingly

                 name: Asynchronous execution
///////////////////////////////////////////////////////////////////////////////




*/

/*
     2 tasks
     calculate factorial of 5
     calculate square of a number given by the user

*/

int square(std::future<int> &ft)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\n Hello from square. I have started my work \n";
    int number = ft.get();
    return number * number;
}

int factorial(int number)
{
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if (number < 0)
    {
        throw std::runtime_error("negative number error!");
    }

    else if (number == 0 || number == 1)
    {
        return 1;
    }

    else
    {
        return number * factorial(number - 1);
    }
}

int main()
{
    //Step 1 : Make a promise
    std::promise<int> pr;
    //step 2: A future linked to the promise
    std::future<int> ft = pr.get_future();
/*
       OS : Launch square (if possible as a new thread)
*/
    std::future<int> result_ft = std::async(std::launch::async, &square, std::ref(ft));
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    int val = 0;
    std::cout << "\n Enter the value to calculate square :";
    std::cin >> val;
    pr.set_value(val);
    std::cout << "Result of factorial is : " << factorial(5)<<std::endl;
    std::cout << " Result of Square is: " << result_ft.get()<<std::endl;
}

/*
     client-server architecture





     future-promise model




     square calculation:

     Mains needs to delegate the task of square calculation

     ----> A new thread for square will be registred with OS
     ----> 





*/