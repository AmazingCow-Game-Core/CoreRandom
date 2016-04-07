Core Random 
====
Made with <3 by [Amazing Cow](http://www.amazingcow.com).

<!-- ####################################################################### -->

## Intro:

Often in the Amazing Cow's board games we need a random generator. While this
can be easily used using the c++11 ```<random>``` facilities, we think that 
must have a cleaner way.

This core is basically a glue between the ```std::mt19937``` generator and 
```std::uniform_int_distribution``` distribution - Nothing fancy, but yet 
very nice to use.

We tried to add an interface for ```CoreRandom::Random``` much alike of C# 
```System.Random``` - So is very easy to use the same ```CoreRandom::Random``` 
object to generate random values from arbitrary ranges each time :D


You are welcome to use, hack and share it :)


<!-- ####################################################################### -->

## Notes:

The ```CoreRandom::Random::next()``` and it's overloads will reset the 
underlying ```std::uniform_int_distribution::param_type``` value if the them are
called with different ranges from the previous call.

For example:

```c++
    CoreRandom::Random r;

    r.next();         //No modify - We start with range of [0, std::limits<int>::max()];
    r.next(10);       //Modify - Now the range will be [0, 10];
    r.next(10);       //No modify - Same range [0, 10];
    r.next();         //Modify - Now range is [0, std::limits<int>max()];
    r.next(100, 200); //Modify - Now the range will be [100, 200];
    r.next(100, 200); //No modify - Same range [100, 200];

    //And so on...
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
    //Doing this will perform better...
    std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<int> a(1, 5);
    std::uniform_int_distribution<int> b(10, 15);
    std::uniform_int_distribution<int> c(20, 25);

    for(;;)
    {
        cout << a(gen) << endl;
        cout << b(gen) << endl;
        cout << c(gen) << endl;
    }

    //Compared of doing this...
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

<!-- ####################################################################### -->

## Files:

We tried to separated the files in a very organized form.   
Here is a list of them:

* ```CoreRandom.h```
* ```CoreRandom_Utils.h```
* ```Random.h```


<!-- ####################################################################### -->

## More info:

We tried to document the Core extensively, so we think that is pretty ease to 
get what the Core is doing, the API calls and stuff.   
Anyway if you didn't understand something let us know sending a mail to 
***help_opensource@amazingcow.com***  with the subject filled with the
name of this repo.


<!-- ####################################################################### -->

## License:
This software is released under GPLv3.


<!-- ####################################################################### -->

## TODO:
Check the TODO file.


<!-- ####################################################################### -->

## Others:
Check our repos and take a look at our [open source site](http://opensource.amazingcow.com).
