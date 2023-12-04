# Workshop 3: Templates

In this workshop, you design and code several class templates and test them on different instantiations.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code a class template
- template a class variable
- specialize a templated class variable for a particular type
- instantiate a template class
- specialize a member function of a templated class to process a particular type
- derive a templated class from another templated class



## Submission Policy

The workshop is divided into two coding parts and one non-coding part:

- *Part 1*: worth 0% of the workshop's total mark, is optional and designed to assist you in completing the second part.
- *Part 2*: worth 100% of the workshop's total mark, is due on **Sunday at 23:59:59** of the week of your scheduled lab.  Submissions of *Part 2* that do not contain the *reflection* are not considered valid submissions and are ignored.
- *reflection*: non-coding part, to be submitted together with *Part 2*. The reflection does not have marks associated to it, but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

The workshop should contain ***only work done by you this term*** or provided by your professor.  Work done in another term (by you or somebody else), or work done by somebody else and not **clearly identified/cited** is considered plagiarism, in violation of the Academic Integrity Policy.

Every file that you submit must contain (as a comment) at the top **your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

- If the file contains only your work, or work provided to you by your professor, add the following message as a comment at the top of the file:

    > I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

- If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which parts of the assignment are given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be clear of any wrong doing.



## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
/usr/local/gcc/10.2.0/bin/g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: compiler will report all warnings
- `-std=c++17`: the code will be compiled using the C++17 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ws`: the compiled application will be named `ws`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ws`):

```bash
valgrind ws
```

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.



## Part 1 (0%)

This workshop consists of the following modules:
- `w3` (supplied)
- `Book` (partially supplied)
- `Collection`
- `OrderedCollection`

The solution to Part 1 invokes the first three modules. 

Enclose all your source code within the `sdds` namespace and include the necessary guards in each header file.

Both class definitions and implementations of the `Collection` and `OrderedCollection` modules must be included on in header file, not in `.cpp` file. *🗎 In reflection explain: Why the definitions and implementations in this case should be included in header file? Are there ways to work around and include implementation in `.cpp` files?*

In all classes that you create, you are allowed to add any **private** or **protected** members that your design requires (without changing the specs)!

### `w3` Module (supplied)

**Do not modify this module!**  Look at the code and make sure you understand how to instantiate a templated class.



### `Book` Module

This module contains a `Book` class to manage book information. 

```cpp
class Book
{
	std::string m_title{};
	unsigned m_numChapters{};
	unsigned m_numPaes{};
public:
    Book();
    Book(const std::string& title, unsigned nChapters, unsigned nPages);
    
	// TODO: In completing Part 1, add here the missing 
	// member prototypes that would be necessary for the 
	// Collection module code and tester module w3_p1.cpp 
	// to manage Book-type objects. 
	// 
	// In completing Part 2, add here the missing 
	// member prototypes that would be necessary for 
	// OrderedCollection module code and tester module 
	// w3_p2.cpp to manage Book-type object. 
	//
	// Write the implementations of these functions 
	// in Book.cpp file

    std::ostream& print(std::ostream& os) const;
    
}
std::ostream& operator<<(std::ostream& os, const Book& bk);

```
An object of `Book` type is valid or usable only when the title is not empty (has at least one character), it has at least one chapter, and it has at least one page. 

*🗎 In reflection, **explain** why it was necessary for you to add the members that you added into the `Book` class.*

### `Collection` Module

This module is to represent a family of collections of elements of any type, such as, collection of `int`-type data, collection of `double`-type data, collection of `Book`-type data, etc.

You create a templated class called `Collection`, which manages a static array of elements of any data type with the following type and non-type template parameters:

- `T`: the type of an element of the managed array, called `m_items`
- `C`: the capacity of the collection or size of the managed array; unsigned whole number non-type parameter. It represents the maximum number of items that can be included in the collection. 

Your design keeps track of (a) maximum possible number of elements and (b) currently stored number of elements, called as, capacity and size, respectively. The class is to be always instantiated through default constructor, and the size of the container should increase as items are added into it. 

Your design also keeps track of the smallest item and largest item across all the class objects through **class members** as per the following instructions.

***Class Members***

- `m_smallestItem`: an object of type `T` to store smallest item. This object will be returned by corresponding public static member function.

- `m_largestItem`: An object of Type `T` to store largest item. This object will be returned by corresponding public static member function.

***Non-Class Private Members***
- `setSmallestItem()`: a modifier to receive an object of type `T`, as unmodifiable reference. It sets `m_smallestItem` to the received object if received object is smaller than it.  

- `setLargestItem()`: a modifier to receive an object of type `T`, as unmodifiable reference. It sets `m_largestItem` to the received object if received object is smaller than it.


***Public Members***

- `size()`: a query to return current number of items
- `capacity()`: a query to return capacity of the collection
- `bool operator+=()`: a mutator to receive an object of type `T` as unmodifiable reference and add it to the collection. It does not do anything if space is not available in the array `m_items`; if available, it performs following: 
  - It updates class members `m_largestItem` and `m_smallestItem` by calling the respective private member functions.
  - adds the received object as a new item of the collection
  - updates the count of the current items.


- `print()`: a query to receive an `ostream` object, such as, `std::cout`, and to insert into it all items-data in the collection; take a hint from sample output for formatting the output data.  

***Class members (public)***
- `T getSmallestItem()`: returns the current smallest item stored in the class attribute. 
- `T getLargestItem()`: return the current largest item stored in the class attribute. 

Add any other **private** members that your design requires (without changing the specs above)!

**Define and Initialize**
- the `m_smallestItem` object to the value `9999` casted to type `T`.  
- the `m_largestItem` object to the value `-9999` casted to type `T`.

**Specialize** 
- Specialize the definition of `m_smallestItem` object for `T = Book` and `C = 10` so that it stores empty string (`""`) as title, `1` as number of chapters, and `10000` as number of pages. 
- Specialize the definition of `m_largestItem` object for `T = Book` and `C = 10` so that it stores empty string (`""`) as title, `10000` as number of chapters, and `1` as number of pages.


### Sample Output

When the program is started with the command:
```
ws
```
the output should look like the one from the `sample_output.txt` file.




### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w3_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***



## Part 2 (100%)

The second part of this workshop upgrades your Part 1 solution by adding another module named `OrderedCollection` that keeps the items arranged in ascending order. 

### `Collection` Module

**Protected Members**
Following members are to be used by derived class to query/mutate the private attributes:
- `setSmallestItem()`: a setter function to receive an object of type `T` as unmodifiable reference, and to set `m_smallestItem` to the received object.
- `setLargestItem()`: a setter function to receive an object of type `T` as unmodifiable reference, and to set `m_largestItem` to the received object.
- `operator[]()`: operator to receive an array index and return corresponding element of `m_items`; The return type should allow the user to modify the array element.
- `incrSize()`: a mutator to increase the size of the container.

**Specialization** 
- Include specializations of the initializations of `m_smallestItem` and `m_largestItem` objects for `T = Book` and `C = 72`; As in the previous case, the intialized `m_smallestItem` and `m_largestItem` objects should hold the book data `{"", 1, 10000}` and `{"",10000,1}`, respectively. 

- Specialize the `print()` function for template parameter values `Book` and `10` to print `Book` object's data differently, in multiple rows; see sample output for a hint on exact formatting of output. 

- Also, specialize the `print()` function for template parameter values `Book` and `72`.

No other changes are necessary to this module.





### `OrderedCollection` Module

Add new module called `OrderedCollection` to your project, which keeps the items in increasing order.

Create a class `OrderedCollection` as a derived class by inheriting the `Collection` structure. The `OrderedCollection` class will always have a capacity of `72` items. Your design of `OrderedCollection` is to have only one template parameter `T`.

***Public Members***

- **override** the inherited operator function `operator+=` to place or insert the received item into the array `m_items` at an appropriate index to ensure that the elements are in ascending order after insertion.

No other members need to be added to this class.



### Sample Output

When the program is started with the command:
```
ws
```
the output should look like the one from the `sample_output.txt` file.




### 🗎 Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation and answer—**but do not limit it to**—the following questions:
- What is the reason for defining the class objects outside the class definition?
- What is the reason for specializing the definition of `m_smallestItem` and `m_largestItem` objects for `Book` and `10`.
- `m_smallestItem` and `m_largestItem` objects are also initialized for `Book` and `72`. Is this initilization necessary? Why?
- answers to the other questions in these specifications.

To avoid deductions, refer to code in your solution as examples to support your explanations.





### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w3_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.
