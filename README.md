# CoreRandom

**Made with <3 by [Amazing Cow](http://www.amazingcow.com).**


<!-- ----------------------------------------------------------------------- -->
<!-- Contents                                                                -->
--------------------------------------------------------------------------------
* [Description](#description)
* [Motivation](#motivation)
* [Examples](#examples)
    * [Notes](#notes)
* [Documentation](#documentation)
* [Dependencies](#dependencies)
* [License](#license)
* [TODO](#todo)
* [Others](#others)


<!-- ----------------------------------------------------------------------- -->
<!-- Description                                                             -->
--------------------------------------------------------------------------------
## Description:

```CoreRandom``` is a easy to use random number generator inspired in C#
[System.Random](https://msdn.microsoft.com/en-us/library/system.random(v=vs.110).aspx)
class.

<br>

As usual, you are **very welcomed** to **share** and **hack** it.



<!-- ----------------------------------------------------------------------- -->
<!-- Motivation                                                              -->
--------------------------------------------------------------------------------
## Motivation:

Often in games we need a random generator. While this can be easily used using
the c++11 ```<random>``` facilities, we think that must have a cleaner/easier way.

This core is basically a glue between the ```std::mt19937``` generator and
```std::uniform_int_distribution``` distribution - Nothing fancy, but yet
very nice to use.

We tried to add an interface for ```CoreRandom::Random``` much alike of C#
```System.Random``` - So is very easy to use the same ```CoreRandom::Random```
object to generate random values from arbitrary ranges each time :D


<!-- ----------------------------------------------------------------------- -->
<!-- Examples                                                                -->
--------------------------------------------------------------------------------
## Examples:

```CoreRandom``` is very easy to use.

```c++
CoreRandom::Random random;

random.next(10);       //   0 to  10 - Inclusive.
random.next(100, 200); // 100 to 200 - Inclusive.

// Play nice with other std algorithms...
std::shuffle(container.begin(),
             container.end(),
             random.getNumberGenerator());
```

<!-- ----------------------------------------------------------------------- -->
<!-- Notes -->
### Notes:

The ```CoreRandom::Random::next()``` and it's overloads will reset the
underlying ```std::uniform_int_distribution::param_type``` value if the them are
called with different ranges from the previous call.

For example:

```c++
CoreRandom::Random r;

r.next();         // No modify - We start with range of [0, std::limits<int>::max()];
r.next(10);       // Modify    - Now the range will be [0, 10];
r.next(10);       // No modify - Same range [0, 10];
r.next();         // Modify    - Now range is [0, std::limits<int>max()];
r.next(100, 200); // Modify    - Now the range will be [100, 200];
r.next(100, 200); // No modify - Same range [100, 200];

// And so on...
```

We don't expect that this could be a performance bottleneck - After all the
```std::uniform_int_distribution``` and ```std::uniform_int_distribution::param_type```
are very lightweight objects.

But this way could not be the optimal way of achieve the desired results if
we are changing ranges **very**, **very** often. Instead one could prefer create
manually a generator and a myriad of distributions and keep them separated from
each other.

For example:

```c++
// Doing this is likely to perform better...
std::mt19937 gen(time(nullptr));
std::uniform_int_distribution<int> a( 1,  5);
std::uniform_int_distribution<int> b(10, 15);
std::uniform_int_distribution<int> c(20, 25);

for(;;)
{
    cout << a(gen) << endl;
    cout << b(gen) << endl;
    cout << c(gen) << endl;
}

// Compared of doing this...
Core::Random r;
for(;;)
{
    cout << r.next( 1,  5) << endl;
    cout << r.next(10, 15) << endl;
    cout << r.next(20, 25) << endl;
}
```

Notice that the example above is the **worst-case** possible for
```CoreRandom::Random``` since each call of next(x, y) it will reset the
underlying ```std::uniform_int_distribution::param_type```.

We **DID NOT** any type of measurement to check how bad is this type of use -
So use the ```CoreRandom::Random``` in this way by your own risk.


<!-- ----------------------------------------------------------------------- -->
<!-- Documentation                                                           -->
--------------------------------------------------------------------------------
## Documentation:

We strive to make our source code fully documented.
While there are a myriad of comments, one might find useful take a look at:

* [Doxygen Docs](http://www.amazingcow.com/projects/CoreRandom/docs/).

Anyway if you didn't understand something let us know sending a mail to
<a href="mailto:help_floss@amazingcow.com?subject=CoreRandom">help_floss@amazingcow.com</a>
with the subject filled with the name of this repo (**CoreRandom**).


<!-- ----------------------------------------------------------------------- -->
<!-- Dependencies                                                            -->
--------------------------------------------------------------------------------
## Dependencies:

**Usage:**

```CoreRandom``` does not depends upon anything else to be used. <br>
This means that to use the library is just clone it and have fun.


**Development:**

```CoreRandom``` depends on the following things to development:

* Amazing Cow's [acow_shellscript_utils](http://github.com/AmazingCow-Libs/acow_shellscript_utils)
to provide facilities for the shell scritpts.

* Amazing Cow's [update_version](http://github.com/AmazingCow-Tools/update_version)
to update the library version correctly.


<!-- ----------------------------------------------------------------------- -->
<!-- License                                                                 -->
--------------------------------------------------------------------------------
## License:

This software is **proudly** released under
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).



<!-- ----------------------------------------------------------------------- -->
<!-- TODO                                                                    -->
--------------------------------------------------------------------------------
## TODO:

Check the TODO file for general things.

This projects uses the COWTODO tags.
So install [cowtodo](http://www.github.com/AmazingCow-Tools/COWTODO) and run:

``` bash
$ cd path/to/the/project
$ cowtodo
```

That's gonna give you all things to do :D.


<!-- ----------------------------------------------------------------------- -->
<!-- Others                                                                  -->
--------------------------------------------------------------------------------
## Others:

Check our repos and take a look at our [floss site](http://floss.amazingcow.com).
