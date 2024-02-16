# 42_philosophers
Project that seeks to understand the basic concepts of threading a process, how to create threads and work with mutexes.

![philosophers problem diagram](https://raw.githubusercontent.com/xilen0x/xilen0x/master/images_x_repos/philosophers_diagram.png)

## What is the project about?
The dining philosophers problem is a well-known challenge in computer science where programmers must devise a solution for multiple philosophers operating concurrently without causing a deadlock, with each philosopher represented by a separate thread.

## What have I learned from the project?
Working with multiple threads I gained proficiency in managing threads that share memory and execute concurrently. This experience underscored the significance of employing mutexes to safeguard shared variables from data races.

## Instructions
1. cd to philo
2. make
3. For philo: ./philo 5 800 200 200 7 (for example)
	* 5 - number of philos
	* 800 - time to die
	* 200 - time to eat
	* 200 - time to sleep
	* 7 - number of meals until finishing. Optional argument

## Used Functions

### Mandatory Part:

- `pthread_create()`: Creates a new thread.
- `pthread_join()`: Waits until a specific thread finishes to avoid having zombie threads.
- `pthread_mutex_init()`: Creates a mutex.
- `pthread_mutex_destroy()`: Destroys a mutex.
- `pthread_mutex_lock()`: Locks a mutex.
- `pthread_mutex_unlock()`: Unlocks a mutex.
- `usleep()`: Makes a thread sleep for a specified number of microseconds.
- `gettimeofday()`: Returns the number of microseconds passed since January 1, 1970.
- `malloc()`: Allocates memory on the heap.
- `free()`: Frees memory from the heap.
- `printf()`: Prints messages.
