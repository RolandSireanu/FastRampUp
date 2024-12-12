
// =========================== Views in C++ =================================
//  Why to use views?
//      Lazy Evaluation: Views provide a mechanism for lazy evaluation, meaning that elements are only processed when they are accessed. This can lead to significant performance improvements, 
//      especially when dealing with large datasets or complex transformations where not all elements need to be processed upfront.
//      Memory Efficiency: Since views do not own the data but instead provide a "window" or "view" into the data, they avoid unnecessary copying or allocation, making operations more memory efficient.
//      Efficient Composition: Views allow you to compose multiple operations (like filtering, transforming, etc.) in a declarative form without creating intermediate containers.
//      Readability and Expressiveness: By using views, you can chain operations in a fluid and expressive way, improving code readability and making the intention of the code more apparent.
//      Separation of Data and Algorithms: Views help separate concerns by allowing algorithms to be applied seamlessly on views without being tied to specific data structures, fostering greater code reusability and flexibility.